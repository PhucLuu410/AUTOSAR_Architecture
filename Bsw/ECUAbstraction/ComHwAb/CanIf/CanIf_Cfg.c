#include "CanIf_Cfg.h"
#include "Can_Cfg.h"
#include "CanTp.h"
#include "PduR.h"

CanIfTxPduCfg CanIfTxPduTable[] = {
    [0] = {
        .CanIfTxPduId = 0,
        .CanIfTxCanId = 0x181,
        .CanIfCanHoh = 0,
    },
    [1] = {
        .CanIfTxPduId = 1,
        .CanIfTxCanId = 0x7E0,
        .CanIfCanHoh = 0,
    },
    [2] = {
        .CanIfTxPduId = 2,
        .CanIfTxCanId = 0x7E0,
        .CanIfCanHoh = 0,
    },

};

CanIfRxPduCfg CanIfRxPduTable[] = {
    [0] = {
        .CanIfRxPduId = 0,
        .CanIfRxCanId = 0x180,
        .DestinationFuncPtr = PduR_CanIfRxIndication,
    },
    [1] = {
        .CanIfRxPduId = 0,
        .CanIfRxCanId = 0x7E8,
        .DestinationFuncPtr = CanTp_RxIndication,
    }};

const CanIf_ConfigType CanIf_Config = {
    .CanIfRxPduCfgRef = CanIfRxPduTable,
    .CanIfTxPduCfgRef = CanIfTxPduTable,
};