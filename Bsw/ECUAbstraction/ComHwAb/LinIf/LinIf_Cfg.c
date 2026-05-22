#include "LinIf_Cfg.h"
#include "Lin.h"
#include "Lin_Cfg.h"
#include "LinIf.h"

#define SIZE_OF_LIN_IF_TABLE 2

LinIf_PduTableConfig LinIf_PduTable[SIZE_OF_LIN_IF_TABLE] = {[0] = {.LinChannel = LIN_CHANNEL_1,
                                                                    .LinIf_LocalId = 0,
                                                                    .LinIf_LinId = 0x12},
                                                             [1] = {.LinChannel = LIN_CHANNEL_1,
                                                                    .LinIf_LocalId = 1,
                                                                    .LinIf_LinId = 0x34}};

LinIf_ConfigType LinIfConfig = {.LinIf_PduTable = LinIf_PduTable};