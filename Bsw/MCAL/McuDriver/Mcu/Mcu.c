#include <stdint.h>
#include "Mcu.h"
#include "Mcu_Cfg.h"
#include "stm32f103xb.h"

void Mcu_Init(const Mcu_ConfigType *ConfigPtr)
{
    RCC->CR |= (1 << ConfigPtr->ClockConfig->ClockSrc);
    RCC->AHBENR = ConfigPtr->ClockConfig->PrehiralConfig->AhbEnable;
    RCC->APB2ENR = ConfigPtr->ClockConfig->PrehiralConfig->Apb2Enable;
    RCC->APB1ENR = ConfigPtr->ClockConfig->PrehiralConfig->Apb1Enable;
    RCC->CFGR |= (ConfigPtr->ClockConfig->AhbPrescale << 4);
    RCC->CFGR |= (ConfigPtr->ClockConfig->Apb2Prescale << 11);
    RCC->CFGR |= (ConfigPtr->ClockConfig->Apb1Prescale << 8);
}
Std_ReturnType Mcu_InitClock(Mcu_ClockType ClockSetting)
{
    switch (ClockSetting)
    {
    case MCU_HSI_CLOCK:
        RCC->CFGR |= (MCU_MCO_OUTPUT_SRC_HSI << 24);
        RCC->CFGR |= (MCU_HSI_SYSTEM_CLOCK << 0);
        RCC->CR |= (1 << 0);
        break;
    case MCU_HSE_CLOCK_CRYSTAL:
        RCC->CR |= (1 << 18);
        RCC->CR |= (1 << 19);
        RCC->CR |= (MCU_MCO_OUTPUT_SRC_HSE << 24);
        RCC->CFGR |= (MCU_HSE_SYSTEM_CLOCK << 0);
        RCC->CR |= (1 << 16);
        break;
    case MCU_HSE_CLOCK_EXTERNAL:
        RCC->CR &= ~(1 << 18);
        RCC->CR |= (1 << 19);
        RCC->CFGR |= (MCU_MCO_OUTPUT_SRC_HSE << 24);
        RCC->CFGR |= (MCU_HSE_SYSTEM_CLOCK << 0);
        RCC->CR |= (1 << 16);
        break;
    case MCU_PLL_CLOCK_HSI:
        RCC->CFGR |= (MCU_PLL_SRC_HSI_DIV_2 << 16);
        RCC->CFGR |= (MCU_PLL_MULTIPLIER_9 << 18);
        RCC->CR |= (1 << 19);
        RCC->CFGR |= (1 << 16);
        RCC->CFGR |= (MCU_MCO_OUTPUT_SRC_PLL_DIV_2 << 24);
        RCC->CFGR |= (MCU_PLL_SYSTEM_CLOCK << 0);
        RCC->CR |= (1 << 24);
        break;
    case MCU_PLL_CLOCK_HSE:
        RCC->CFGR |= (MCU_PLL_SRC_HSE << 16);
        RCC->CFGR |= (MCU_PLL_MULTIPLIER_9 << 18);
        RCC->CFGR |= (MCU_PLL_HSE_ENTRY_DIV_2 << 17);
        RCC->CR |= (1 << 19);
        RCC->CR |= (1 << 16);
        RCC->CFGR |= (MCU_MCO_OUTPUT_SRC_PLL_DIV_2 << 24);
        RCC->CFGR |= (MCU_PLL_SYSTEM_CLOCK << 0);
        RCC->CR |= (1 << 24);
        break;
    default:
        return E_NOT_OK;
    }
    return E_OK;
}

Std_ReturnType Mcu_InitRamSection(Mcu_RamSectionType RamSection)
{
    return E_OK;
}

void Mcu_SetMode(Mcu_ModeType McuMode)
{
    switch (McuMode)
    {
    case MCU_POWER_ON_MODE:
        SCB->SCR &= ~(1 << 1);
        SCB->SCR &= ~(1 << 2);
        break;
    case MCU_SLEEP_MODE:
        SCB->SCR &= ~(1 << 1);
        SCB->SCR &= ~(1 << 2);
        __WFI();
        break;
    case MCU_DEEP_SLEEP_MODE:
        SCB->SCR &= ~(1 << 1);
        SCB->SCR |= (1 << 2);
        __WFI();
        break;
    case MCU_STOP_MODE:
        PWR->CR |= (1 << 0);
        PWR->CR &= ~(1 << 1);
        SCB->SCR &= ~(1 << 1);
        SCB->SCR |= (1 << 2);
        __WFI();
        break;
    }
}