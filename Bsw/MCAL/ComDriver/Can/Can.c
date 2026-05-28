#include "Can.h"
#include "Can_Cfg.h"
#include "stm32f103xb.h"
#include "CanIf.h"

// Function Descriptions
// The Can module writes the L-PDU in an appropriate buffer inside the CAN controller hardware
// On L-PDU reception, the Can module calls the RX indication callback function with ID,Data Length and pointer to L-SDU as parameter.
// The Can module provides an interface that serves as periodical processing function,and
// which must be called by the Basic Software Scheduler module periodically
// The Can module provides services to control the state of the CAN controllers.
// Bus-off and Wake-up events are notified by means of callback functions.
// The Can module is a Basic Software Module that accesses hardware resources.

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