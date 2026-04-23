#include "Dio.h"
#include "Dio_Cfg.h"
#include "Port.h"
#include "Port_Cfg.h"
#include "Pwm.h"
#include "Pwm_Cfg.h"
#include "ADC/Adc.h"

uint32_t Count = 0;
uint16_t adcValueGr0[16] = {0};
void delay(volatile uint32_t t)
{
    while (t--)
        ;
}

const Port_ConfigType Port_Configuration[NUMBER_OF_CHANNEL] = {
    [0] = {.port = PORT_A,
           .pin = 0,
           .mode = PORT_MODE_INPUT,
           .speed = PORT_OUTPUT_SPEED_50MHz,
           .cfg = PORT_CNF_ANALOG_INPUT},
    [1] = {.port = PORT_A,
           .pin = 1,
           .mode = PORT_MODE_INPUT,
           .speed = PORT_OUTPUT_SPEED_50MHz,
           .cfg = PORT_CNF_ANALOG_INPUT},
    [2] = {.port = PORT_A,
           .pin = 2,
           .mode = PORT_MODE_INPUT,
           .speed = PORT_OUTPUT_SPEED_50MHz,
           .cfg = PORT_CNF_ANALOG_INPUT},
    [3] = {.port = PORT_A,
           .pin = 3,
           .mode = PORT_MODE_INPUT,
           .speed = PORT_OUTPUT_SPEED_50MHz,
           .cfg = PORT_CNF_ANALOG_INPUT}};

Pwm_ConfigType Pwm_Configuration[4] = {
    {0, 50, 0, 0, PWM_IDLE_STATE_HIGH, 1},
    {1, 50, 60, 0, PWM_IDLE_STATE_LOW, 1},
    {2, 50, 0, 0, PWM_IDLE_STATE_LOW, 1},
    {3, 50, 40, 0, PWM_IDLE_STATE_LOW, 1}};

Adc_ConfigType Adc_Configuration[] =
    {
        {ADC_MODE_INDEPENDENT, ADC_GROUP_0, ADC_CONV_MODE_CONTINUOUS, ADC_CHANNEL_0, ADC_ALIGN_RIGHT, ADC_SAMPLING_TIME_239_5_CYCLES, ADC_RESOLUTION_12_BIT, ADC_REFERENCE_0, ADC_CLOCK_DIV_1},
        {ADC_MODE_INDEPENDENT, ADC_GROUP_0, ADC_CONV_MODE_CONTINUOUS, ADC_CHANNEL_1, ADC_ALIGN_RIGHT, ADC_SAMPLING_TIME_239_5_CYCLES, ADC_RESOLUTION_12_BIT, ADC_REFERENCE_0, ADC_CLOCK_DIV_1},
        {ADC_MODE_INDEPENDENT, ADC_GROUP_3, ADC_CONV_MODE_CONTINUOUS, ADC_CHANNEL_2, ADC_ALIGN_RIGHT, ADC_SAMPLING_TIME_239_5_CYCLES, ADC_RESOLUTION_12_BIT, ADC_REFERENCE_0, ADC_CLOCK_DIV_1},
        {ADC_MODE_INDEPENDENT, ADC_GROUP_3, ADC_CONV_MODE_CONTINUOUS, ADC_CHANNEL_3, ADC_ALIGN_RIGHT, ADC_SAMPLING_TIME_239_5_CYCLES, ADC_RESOLUTION_12_BIT, ADC_REFERENCE_0, ADC_CLOCK_DIV_1}};

int main(void)
{

    RCC->CR |= (1 << 0);      // Enable HSI
    RCC->APB2ENR |= (1 << 2); // Enable AFIO clock
    RCC->APB2ENR |= (1 << 4);
    RCC->APB2ENR |= (1 << 0);
    RCC->APB2ENR |= (1 << 9);
    RCC->APB1ENR |= (1 << 0);
    RCC->AHBENR |= (1 << 0);

    Port_Init(Port_Configuration);
    Adc_Init(Adc_Configuration);

    DMA1_Channel1->CCR = 0;
    DMA1_Channel1->CCR |= (1 << 5);
    DMA1_Channel1->CCR |= (1 << 7);
    DMA1_Channel1->CCR |= (1 << 8);
    DMA1_Channel1->CCR |= (1 << 10);
    DMA1_Channel1->CCR |= (1 << 12);
    DMA1_Channel1->CNDTR = 2;
    DMA1_Channel1->CPAR = (uint32_t)&ADC1->DR;
    Adc_SetupResultBuffer(ADC_GROUP_0, adcValueGr0);
    while (1)
    {
        Adc_StartGroupConversion(ADC_GROUP_0);
        delay(1000000);
        Adc_StopGroupConversion(ADC_GROUP_0);
        Adc_StartGroupConversion(ADC_GROUP_3);
        delay(1000000);
        Adc_StopGroupConversion(ADC_GROUP_3);
    }
}