#include "Dio.h"
#include "Dio_Cfg.h"
#include "Port.h"
#include "Port_Cfg.h"
#include "Pwm.h"
#include "Pwm_Cfg.h"
#include "Adc/Adc.h"
#include "Adc/Adc_Cfg.h"
#include "Mcu.h"
#include "Mcu_Cfg.h"
#include "IoHwAb.h"
#include "IoHwAb_Cfg.h"
#include "Can.h"
#include "Can_Cfg.h"
#include "CanIf.h"
#include "CanIf_Cfg.h"
#include "CanTp.h"
#include "CanTp_Cfg.h"
#include "PduR.h"
#include "PduR_Cfg.h"
#include "Com.h"
#include "Lin.h"
#include "Lin_Cfg.h"
#include "LinIf.h"
#include "LinIf_Cfg.h"
#include "Crypto.h"
#include "Crypto_Cfg.h"
#include "CryIf.h"
#include "Csm.h"
#include "stm32f103xb.h"
#include "Swc_EngineStatus.h"

void delay(volatile uint32_t t)
{
    while (t--)
        ;
}

void SysTick_Init_8MHz(void)
{
    SysTick->CTRL = 0;
    SysTick->LOAD = 7999;
    SysTick->VAL = 0;
    CoreDebug->DEMCR |= (1 << 24);
    DWT->CYCCNT = 0;
    DWT->CTRL |= (1 << 0);
    NVIC_SetPriority(SysTick_IRQn, 0xF0);
    NVIC_SetPriority(PendSV_IRQn, 0xFF);
}

int main(void)
{
    Mcu_Init(&Mcu_Configuration[0]);
    Mcu_InitClock(Mcu_Configuration[0].ClockConfig->ClockSrc);

    Port_Init(Port_Configuration);

    Can_Init(&CanConfig);
    Can_EnableControllerInterrupts(CAN_1_CONTROLLER);
    Can_SetBaudrate(CAN_1_CONTROLLER, 0);
    Can_SetControllerMode(CAN_1_CONTROLLER, CAN_CS_STARTED);

    CanIf_Init(&CanIf_Config);
    CanTp_Init(&CanTp_Config);
    // CanIf_SetControllerMode(0, CAN_CS_STARTED);

    Lin_Init(&Lin_Config);
    Lin_GoToSleepInternal(LIN_CHANNEL_1);
    Lin_WakeupInternal(LIN_CHANNEL_1);

    LinIf_Init(&LinIf_Config);
    LinTp_Init(&LinTp_Config);

    Crypto_Init(&Crypto_Config);

    // PduR_Init(&PduR_PBConfig);
    // SysTick_Init_8MHz();
    // Os_Init();
    // Os_Start();
    // Com_SendSignal(1);
    while (1)
    {
        // Swc_EngineStatus_MainFunction();
        // delay(10000);
    }
}

void HardFault_Handler(void)
{
    while (1)
        ;
}
