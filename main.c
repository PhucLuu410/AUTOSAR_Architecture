#include "Dio.h"
#include "Dio_Cfg.h"
#include "Port.h"
#include "Port_Cfg.h"
#include "Pwm.h"
#include "Pwm_Cfg.h"
#include "ADC/Adc.h"

uint32_t Count = 0;
uint16_t adcValue[3] = {0};
void delay(volatile uint32_t t)
{
    while (t--)
        ;
}

const Port_ConfigType Port_Configuration[NUMBER_OF_CHANNEL] = {
    [0] = {.port = PORT_A
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
           .cfg = PORT_CNF_ANALOG_INPUT}};

Pwm_ConfigType Pwm_Configuration[4] = {
    {0, 50, 0, 0, PWM_IDLE_STATE_HIGH, 1},
    {1, 50, 60, 0, PWM_IDLE_STATE_LOW, 1},
    {2, 50, 0, 0, PWM_IDLE_STATE_LOW, 1},
    {3, 50, 40, 0, PWM_IDLE_STATE_LOW, 1}};

Adc_ConfigType Adc_Channel[] =
    {
        {0, 0, 0, 0, 0},
        {1, 0, 0, 1, 0},
        {2, 0, 0, 2, 0}};
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

    Adc_Init(Adc_Channel);

    Adc_SetupResultBuffer(0, adcValue);
    while (1)
    {
    }
}