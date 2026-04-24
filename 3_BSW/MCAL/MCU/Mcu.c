#include <stdint.h>
#include "Mcu.h"
#include "Mcu_Cfg.h"
#include "stm32f103xb.h"

void Mcu_Init(const Mcu_ConfigType *ConfigPtr)
{
    switch (ConfigPtr->HSEClockType->ClockType)
    {
    case MCU_HSI_CLOCK:
        RCC->CR |= (1 << 0);
        break;
    case MCU_HSE_CLOCK:
        RCC->CR |= (1 << 16);

        if (ConfigPtr->HSEClockType->HSESource == HSE_Crystal_External_Clock)
        {
            RCC->CR &= ~(1 << 18);
        }
        else if (ConfigPtr->HSEClockType->HSESource == HSE_User_External_Clock)
        {
            RCC->CR |= (1 << 18);
        }

        if (ConfigPtr->HSEClockType->CSSType == MCU_CSS_ENABLE)
        {
            RCC->CR |= (1 << 19);
        }
        else if (ConfigPtr->HSEClockType->CSSType == MCU_CSS_DISABLE)
        {
            RCC->CR &= ~(1 << 19);
        }
    default:
        break;
    }
    RCC->CFGR &= ~(0x3 << 16);
    RCC->CFGR |= (ConfigPtr->PLLSrc << 16);

    RCC->CFGR &= ~(0xF << 18);
    RCC->CFGR |= (ConfigPtr->PLLMulti << 18);

    RCC->CR &= ~(0x1 << 24);
    RCC->CR |= (ConfigPtr->PLLChoose << 24);

    RCC->CFGR &= ~(0xF << 24);
    RCC->CFGR |= (ConfigPtr->McuMCO << 24);

    RCC->CFGR &= ~(0x3 << 0);
    RCC->CFGR |= (ConfigPtr->SystemClock << 0);

    RCC->CFGR &= ~(0xF << 4);
    RCC->CFGR |= (ConfigPtr->McuAHBPrescale << 4);

    RCC->CFGR &= ~(0x7 << 8);
    RCC->CFGR |= (ConfigPtr->McuAPB2Prescale << 8);

    RCC->CFGR &= ~(0x7 << 11);
    RCC->CFGR |= (ConfigPtr->McuAPB1Prescale << 11);

    RCC->APB2ENR |= (1 << 2);
    RCC->APB2ENR |= (1 << 4);
    RCC->APB2ENR |= (1 << 0);
    RCC->APB2ENR |= (1 << 9);
    RCC->APB1ENR |= (1 << 0);
    RCC->AHBENR |= (1 << 0);
}