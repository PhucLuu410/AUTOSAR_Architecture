#ifndef __LINIF_CFG_H__
#define __LINIF_CFG_H__

#include "LinIf.h"
#include "LinIf_Cfg.h"

#define SIZE_OF_LIN_IF_TX_TABLE 2
#define SIZE_OF_LIN_IF_RX_TABLE 2

extern LinIf_TxTableConfig LinIf_TxTable[SIZE_OF_LIN_IF_TX_TABLE];
extern LinIf_RxTableConfig LinIf_RxTable[SIZE_OF_LIN_IF_RX_TABLE];
extern LinIf_ConfigType LinIfConfig;
#endif