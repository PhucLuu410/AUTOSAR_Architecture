#include "Can.h"
#include "Can_Cfg.h"
#include "Can_GeneralTypes.h"
#include "stm32f103xb.h"

void Can_Init(const Can_ConfigType *ConfigPtr)
{
    CAN1->MCR &= ~(1 << 1);
    CAN1->MCR |= (1 << 0);

    CAN1->BTR |= (ConfigPtr->mode << 30);
    CAN1->BTR |= (((8000000 / ConfigPtr->baudRate) - 1) << 0);

    CAN1->MCR &= ~(1 << 0);
}

void Can_DeInit(void)
{
    CAN1->MCR = 0x00010002;
    CAN1->BTR = 0x01230002;
}

Std_ReturnType Can_SetBaudrate(uint8 Controller, uint16 BaudRateConfigID)
{
    CAN_Controllers[Controller]->MCR |= (1 << 0);
    CAN_Controllers[Controller]->BTR |= (((8000000 / BaudRateConfigID) - 1) << 0);
    CAN_Controllers[Controller]->MCR &= ~(1 << 0);
    return E_OK;
}

Std_ReturnType Can_SetControllerMode(uint8 Controller, Can_ControllerStateType Transition)
{
    
    return E_OK;
}