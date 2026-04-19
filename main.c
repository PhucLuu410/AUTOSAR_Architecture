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

Pwm_ConfigType Pwm_Configuration[4] = {
    {0, 50, 0, 0,PWM_IDLE_STATE_HIGH, 1},
    {1, 50, 60, 0, PWM_IDLE_STATE_LOW, 1},
    {2, 50, 0, 0, PWM_IDLE_STATE_LOW, 1},
    {3, 50, 40, 0, PWM_IDLE_STATE_LOW, 1}
};

int main(void)
{
    RCC->CR |= (1 << 0); // Enable HSI
    RCC->APB2ENR |= (1 << 2);
    RCC->APB2ENR |= (1 << 4);
    RCC->APB2ENR |= (1 << 0);
    RCC->APB1ENR |= (1 << 0); 

    Port_Init(Port_Configuration);
    Pwm_Init(Pwm_Configuration);
    Pwm_SetDutyCycle(PWM_CHANNEL_1, 50);
    while (1)
    {
        Count = TIM2->CNT;
    }
}