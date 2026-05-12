#ifndef __COMHWAB_CFG_H
#define __CANIF_CFG_H

#include "CanIf.h"

#define SENSOR_0_ID 0x127
#define SENSOR_1_ID 0x123
#define SENSOR_2_ID 0x321

extern Can_PduType CanTxPduInfo[];
extern PduInfoType CanIfRxPduInfo[];
extern CanIf_ConfigType CanIfConfig;
extern PduInfoType CanIfTxPduInfo[];

#endif