#include "Pwm.h"
#include "Pwm_Cfg.h"

#define TIM_Frequence 8000000UL

void Pwm_Init(const Pwm_ConfigType *ConfigPtr)
{
    for (int i = 0; i < 1; i++)
    {
        TIM2->CCMR1 &= ~(0x3 << 0);
        TIM2->CCMR1 |= (1 << 3);
        TIM2->CCMR1 |= (6 << 4);
        TIM2->CCER |= (1 << 0);
        TIM2->CCER &= ~(1 << 1);
        TIM2->CR1 |= (1 << 7);
        TIM2->CR1 &= ~(0x3 << 5);
        TIM2->EGR |= (1 << 0);

        TIM2->CCR1 |= ConfigPtr[i].Period;
    }
}