#include "Can.h"
#include "Can_Cfg.h"
#include "stm32f103xb.h"
#include "CanIf.h"

void Can_Init(const Can_ConfigType *Config)
{
}

Std_ReturnType Can_SetControllerMode(uint8 Controller, Can_ControllerStateType Transition)
{
    return 0;
}

void Can_DisableControllerInterrupts(uint8 Controller)
{
}
void Can_EnableControllerInterrupts(uint8 Controller)
{
}
Std_ReturnType Can_SetBaudrate(uint8 Controller, uint16 BaudRateConfigID)
{
    return 0;
}
Std_ReturnType Can_Write(Can_HwHandleType Hth, const Can_PduType *PduInfo)
{
    return 0;
}