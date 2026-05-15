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
#include "PduR.h"
#include "PduR_Cfg.h"
#include "Com.h"
#include "Rte.h"
#include "Os.h"

Can_ControllerStateType ControllerMode;
PduInfoType CanIfRxDataSave[2] = {0};
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
    SysTick->CTRL = 0x07;
    CoreDebug->DEMCR |= (1 << 24);
    DWT->CYCCNT = 0;
    DWT->CTRL |= (1 << 0);
}

int main(void)
{
    Mcu_Init(&Mcu_Configuration[0]);
    Mcu_InitClock(Mcu_Configuration[0].ClockConfig->ClockSrc);
    Port_Init(Port_Configuration);

    SysTick_Init_8MHz();

    Can_Init(&CanConfig[0]);
    Can_DisableControllerInterrupts(CAN_1);
    Can_SetBaudrate(CAN_1, 0);
    CanIf_Init(&CanIfConfig);
    CanIf_SetControllerMode(CAN_1, CAN_CS_STARTED);
    PduR_Init(&PduR_PBConfig);
    Os_Init();
    while (1)
    {
        // Os_Start();
    }
}

void HardFault_Handler(void)
{
    while (1)
        ;
}
