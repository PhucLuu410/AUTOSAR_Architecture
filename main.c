#include "Dio.h"
#include "Dio_Cfg.h"
#include "Port.h"
#include "Port_Cfg.h"
#include "Pwm.h"
#include "Pwm_Cfg.h"

uint32_t Count = 0;
void delay(volatile uint32_t t)
{
    while (t--)
        ;
}

Pwm_ConfigType Pwm_Configuration[1] = {
    {0, PWM_VARIABLE_PERIOD, 0, 50, 50}};

int main(void)
{
    RCC->CR |= (1 << 0); // Enable HSI
    RCC->APB2ENR |= (1 << 2);
    RCC->APB2ENR |= (1 << 4);
    RCC->APB2ENR |= (1 << 0);
    RCC->APB1ENR |= (1 << 0); // TIM2

    TIM2->PSC = 7;
    TIM2->ARR = 1000 - 1;
    TIM2->CR1 |= (1 << 0);

    Port_Init(Port_Configuration);
    Pwm_Init(Pwm_Configuration);
    while (1)
    {
        Count = TIM2->CNT;
    }
}