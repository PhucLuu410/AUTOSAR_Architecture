#ifndef __CANIF_CFG_H
#define __CANIF_CFG_H

#include "CanIf.h"

#define SIZE_OF_CAN_IF_TABLE 3

extern CanIf_ConfigType CanIfConfig;

extern Can_PduType CanTxPduInfo[];

extern CanIf_PduTxTableConfig CanIf_TxTable[SIZE_OF_CAN_IF_TABLE];

extern CanIf_PduRxTableConfig CanIf_RxTable[SIZE_OF_CAN_IF_TABLE];

#endif