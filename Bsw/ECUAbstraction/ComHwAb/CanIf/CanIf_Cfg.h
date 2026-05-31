#ifndef __CANIF_CFG_H
#define __CANIF_CFG_H

#include "CanIf.h"

#define SIZE_OF_CAN_IF_TX_TABLE 2
#define SIZE_OF_CAN_IF_RX_TABLE 2

extern CanIf_ConfigType CanIfConfig;

extern Can_PduType CanTxPduInfo[];

extern CanIf_PduTxTableConfig CanIf_TxTable[];

extern CanIf_PduRxTableConfig CanIf_RxTable[];

#endif