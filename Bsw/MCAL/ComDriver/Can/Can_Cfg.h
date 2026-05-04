#ifndef __CAN_CFG_H__
#define __CAN_CFG_H__

#include "Can.h"
#include "Can_GeneralTypes.h"

#define CAN_MAX_CONTROLLER 1

#define CAN_1 0
#define CAN_2 1

#define CAN_CLOCK 8000000

#define CAN_STANDARD_ID 0
#define CAN_EXTENDED_ID 1

#define CAN_MODE_NORMAL 0x00
#define CAN_MODE_LOOPBACK 0x01
#define CAN_MODE_SILENT 0x02
#define CAN_MODE_SILENT_LOOPBACK 0x03

extern const Can_ConfigType CanConfig;
#endif