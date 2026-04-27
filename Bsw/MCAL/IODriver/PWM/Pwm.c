#include "Pwm.h"
#include "Pwm_Cfg.h"
#include "stm32f103xb.h"
#include "stdint.h"

static CCRx_Type get_CCRx(Pwm_ChannelType ChannelNumber)
{
    switch (ChannelNumber)
    {
    case 0:
        return CCR1;
    case 1:
        return CCR2;
    case 2:
        return CCR3;
    case 3:
        return CCR4;
    default:
        return CCR1;
    }
}

void Pwm_Init(const Pwm_ConfigType *ConfigPtr)
{

    TIM2->CR1 |= (1 << 7);
    TIM2->PSC = 7 + 1;
    TIM2->ARR = (TIM_Frequence / PWM_Frequence) - 1;
    for (int i = 0; i < 4; i++)
    {
        CCRx_Type ccr = get_CCRx(ConfigPtr[i].ChannelNumber);
        switch (ccr)
        {
        case CCR1:
            TIM2->CCMR1 |= (8 << 0);
            TIM2->CCMR1 |= (6 << 4);
            TIM2->CCR1 = (TIM2->ARR + 1) * ConfigPtr[i].DutyCycle / 100;
            TIM2->CCER |= (1 << 0);
            switch (ConfigPtr[i].Polarity)
            {
            case 0:
                switch (ConfigPtr[i].IdleState)
                {
                case 0:
                    TIM2->CCER &= ~(1 << 1);
                    break;
                case 1:
                    TIM2->CCER |= (1 << 1);
                    break;
                }
            case 1:
                switch (ConfigPtr[i].IdleState)
                {
                case 0:
                    TIM2->CCER &= ~(1 << 1);
                    break;
                case 1:
                    TIM2->CCER |= (1 << 1);
                    break;
                }
            }
            break;
        case CCR2:
            TIM2->CCMR1 |= (8 << 8);
            TIM2->CCMR1 |= (6 << 12);
            TIM2->CCR2 = (TIM2->ARR + 1) * ConfigPtr[i].DutyCycle / 100;
            TIM2->CCER |= (1 << 4);
            switch (ConfigPtr[i].Polarity)
            {
            case 0:
                switch (ConfigPtr[i].IdleState)
                {
                case 0:
                    TIM2->CCER &= ~(1 << 5);
                    break;
                case 1:
                    TIM2->CCER |= (1 << 5);
                    break;
                }
            case 1:
                switch (ConfigPtr[i].IdleState)
                {
                case 0:
                    TIM2->CCER &= ~(1 << 5);
                    break;
                case 1:
                    TIM2->CCER |= (1 << 5);
                    break;
                }
            }
            break;
        case CCR3:
            TIM2->CCMR2 |= (8 << 0);
            TIM2->CCMR2 |= (6 << 4);
            TIM2->CCR3 = (TIM2->ARR + 1) * ConfigPtr[i].DutyCycle / 100;
            TIM2->CCER |= (1 << 8);
            switch (ConfigPtr[i].Polarity)
            {
            case 0:
                switch (ConfigPtr[i].IdleState)
                {
                case 0:
                    TIM2->CCER &= ~(1 << 9);
                    break;
                case 1:
                    TIM2->CCER |= (1 << 9);
                    break;
                }
            case 1:
                switch (ConfigPtr[i].IdleState)
                {
                case 0:
                    TIM2->CCER &= ~(1 << 9);
                    break;
                case 1:
                    TIM2->CCER |= (1 << 9);
                    break;
                }
            }
        case CCR4:
            TIM2->CCMR2 |= (8 << 8);
            TIM2->CCMR2 |= (6 << 12);
            TIM2->CCR4 = (TIM2->ARR + 1) * ConfigPtr[i].DutyCycle / 100;
            TIM2->CCER |= (1 << 12);
            switch (ConfigPtr[i].Polarity)
            {
            case 0:
                switch (ConfigPtr[i].IdleState)
                {
                case 0:
                    TIM2->CCER &= ~(1 << 13);
                    break;
                case 1:
                    TIM2->CCER |= (1 << 13);
                    break;
                }
            case 1:
                switch (ConfigPtr[i].IdleState)
                {
                case 0:
                    TIM2->CCER &= ~(1 << 13);
                    break;
                case 1:
                    TIM2->CCER |= (1 << 13);
                    break;
                }
            }
        }
    }
    TIM2->CR1 |= (1 << 0);
}
void Pwm_DeInit(void)
{
    TIM2->CR1 &= ~(1 << 0);
}

void Pwm_SetDutyCycle(Pwm_ChannelType ChannelNumber, uint16 DutyCycle)
{
    CCRx_Type ccr = get_CCRx(ChannelNumber);
    switch (ccr)
    {
    case CCR1:
        TIM2->CCR1 = (TIM2->ARR + 1) * DutyCycle / 100;
        break;
    case CCR2:
        TIM2->CCR2 = (TIM2->ARR + 1) * DutyCycle / 100;
        break;
    case CCR3:
        TIM2->CCR3 = (TIM2->ARR + 1) * DutyCycle / 100;
        break;
    case CCR4:
        TIM2->CCR4 = (TIM2->ARR + 1) * DutyCycle / 100;
        break;
    }
}
void Pwm_SetPeriodAndDuty(Pwm_ChannelType ChannelNumber, Pwm_PeriodType Period, uint16 DutyCycle)
{
    CCRx_Type ccr = get_CCRx(ChannelNumber);
    TIM2->ARR = Period - 1;
    switch (ccr)
    {
    case CCR1:
        TIM2->CCR1 = (TIM2->ARR + 1) * DutyCycle / 100;
        break;
    case CCR2:
        TIM2->CCR2 = (TIM2->ARR + 1) * DutyCycle / 100;
        break;
    case CCR3:
        TIM2->CCR3 = (TIM2->ARR + 1) * DutyCycle / 100;
        break;
    case CCR4:
        TIM2->CCR4 = (TIM2->ARR + 1) * DutyCycle / 100;
        break;
    }
}
void Pwm_SetOutputToIdle(Pwm_ChannelType ChannelNumber)
{
    CCRx_Type ccr = get_CCRx(ChannelNumber);
    switch (ccr)
    {
    case CCR1:
        TIM2->CCR1 = 0;
        break;
    case CCR2:
        TIM2->CCR2 = 0;
        break;
    case CCR3:
        TIM2->CCR3 = 0;
        break;
    case CCR4:
        TIM2->CCR4 = 0;
        break;
    }
}

Pwm_OutputStateType Pwm_GetOutputState(Pwm_ChannelType ChannelNumber)
{
    CCRx_Type ccr = get_CCRx(ChannelNumber);
    switch (ccr)
    {
    case CCR1:
        return (Pwm_OutputStateType)(TIM2->CCR1);
    case CCR2:
        return (Pwm_OutputStateType)(TIM2->CCR2);
    case CCR3:
        return (Pwm_OutputStateType)(TIM2->CCR3);
    case CCR4:
        return (Pwm_OutputStateType)(TIM2->CCR4);
    }
    return PWM_LOW;
}
