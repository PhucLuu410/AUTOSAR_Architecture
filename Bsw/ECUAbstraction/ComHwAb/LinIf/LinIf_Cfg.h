#ifndef __LINIF_CFG_H__
#define __LINIF_CFG_H__

#include "LinIf.h"
#include "LinIf_Cfg.h"

#define SIZE_OF_LIN_IF_TX_TABLE 1
#define SIZE_OF_LIN_IF_RX_TABLE 1

extern LinIf_TxTableConfig LinIf_TxTable[];
extern LinIf_RxTableConfig LinIf_RxTable[];
extern LinIf_ConfigType LinIfConfig;
#endif