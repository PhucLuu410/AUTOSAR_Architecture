#include "LinIf_Cfg.h"
#include "Lin.h"
#include "Lin_Cfg.h"
#include "LinIf.h"

uint8 LinRxData[SIZE_OF_LIN_IF_RX_TABLE][16] = {0};

LinIf_TxTableConfig LinIf_TxTable[SIZE_OF_LIN_IF_TX_TABLE] = {[0] = {.LinChannel = LIN_CHANNEL_1,
                                                                     .LinIf_LocalId = 0,
                                                                     .LinIf_LinId = 0x12},
                                                              [1] = {.LinChannel = LIN_CHANNEL_1,
                                                                     .LinIf_LocalId = 1,
                                                                     .LinIf_LinId = 0x34}};

LinIf_RxTableConfig LinIf_RxTable[SIZE_OF_LIN_IF_RX_TABLE] = {[0] = {.LinIf_LocalId = 0,
                                                                     .LinIf_LinId = 0x12,
                                                                     .LinIf_DataLength = 8},
                                                              [1] = {.LinIf_LocalId = 1,
                                                                     .LinIf_LinId = 0x34,
                                                                     .LinIf_DataLength = 8}};

LinIf_ConfigType LinIfConfig = {.LinIf_TxTable = LinIf_TxTable,
                                .LinIf_RxTable = LinIf_RxTable};