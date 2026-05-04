#ifndef __CAN_CFG_H__
#define __CAN_CFG_H__

#include "Can.h"
#include "stm32f103xb.h"

#define CAN_CONTROLLER_0 0
#define CAN_CONTROLLER_1 1

#define CAN_MODE_NORMAL 0x00
#define CAN_MODE_LOOPBACK 0x01
#define CAN_MODE_SILENT 0x02
#define CAN_MODE_SILENT_LOOPBACK 0x03

extern CAN_TypeDef *const CAN_Controllers[2];
extern const Can_ConfigType CanConfig;

#endif