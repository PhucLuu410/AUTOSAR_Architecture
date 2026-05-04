#include "Can.h"
#include "Can_Cfg.h"
#include "stm32f103xb.h"

static Can_ControllerStateType Can_ControllerState[CAN_MAX_CONTROLLER];
static CAN_TypeDef *const Can_Controllers[CAN_MAX_CONTROLLER] = {CAN1};

void Can_Init(const Can_ConfigType *ConfigPtr)
{
    Can_Controllers[CAN_1]->MCR &= ~(1 << 1);
    Can_Controllers[CAN_1]->MCR |= (1 << 0);
    Can_Controllers[CAN_1]->BTR = (((ConfigPtr->ControllerConfig->CanSjw) & 0x3) << 24) |
                                  ((((ConfigPtr->ControllerConfig->CanTseg1) + (ConfigPtr->ControllerConfig->CanPropagationDelay)) & 0xF) << 16) |
                                  (((ConfigPtr->ControllerConfig->CanTseg2) & 0x7) << 20) |
                                  (8 << 0);
}