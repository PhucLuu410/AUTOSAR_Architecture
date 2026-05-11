#ifndef __COMHWAB_CFG_H
#define __CANIF_CFG_H

#include "CanIf.h"

#define CAN_SENSOR_0 0
#define CAN_SENSOR_1 1
#define CAN_SENSOR_2 2

extern Can_PduType Can_TxPduInfo[];
extern CanIf_ConfigType CanIf_Config;
extern PduInfoType CanIfPduInfo;

#endif