#include "CanTp_Cfg.h"
#include "CanTp.h"
#include "Std_GeneralTypes.h"

CanTpTxPduCfg CanTpTx_DiagCfg[NUMBER_OF_CANTP] = {
    [0] = {
        .CanTpTxPduId = 0,
        .CanIfTxPduId = 1,
    },
};

CanTpRxPduCfg CanTpRx_DiagCfg[NUMBER_OF_CANTP] = {
    [0] = {
        .CanTpRxPduId = 0,
        .CanIfTxRespondPduId = 1,
        .PduRRxPduId = 3,
    },
};

const CanTp_ConfigType CanTp_Config = {
    .CanTpRxPduCfg = CanTpRx_DiagCfg,
    .CanTpTxPduCfg = CanTpTx_DiagCfg,
};

CanTp_TxStateType CanTp_TxState[NUMBER_OF_CANTP];
CanTp_RxStateType CanTp_RxState[NUMBER_OF_CANTP];