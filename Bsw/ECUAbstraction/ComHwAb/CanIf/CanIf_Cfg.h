#ifndef __CANIF_CFG_H
#define __CANIF_CFG_H

#include "CanIf.h"

#define SIZE_OF_CAN_IF_TABLE 3

extern CanIf_ConfigType CanIfConfig;

extern Can_PduType CanTxPduInfo[];

extern CanIf_PduTableConfig CanIf_PduTable[SIZE_OF_CAN_IF_TABLE];

extern CanIfPduRxTableType CanIfRxTable[];

#endif