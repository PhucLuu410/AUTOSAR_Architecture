#include "CanTp_Cfg.h"
#include "CanTp.h"
#include "Std_Types.h"

CanTpTxPduCfg CanTpTx_DiagCfg[NUMBER_OF_CANTP_TX] = {
    [0] = {
        .CanTpTxPduId = 0,
        .CanIfTxPduId = 1,
    },
};

CanTpRxPduCfg CanTpRx_DiagCfg[NUMBER_OF_CANTP_RX] = {
    [0] = {
        .CanTpRxPduId = 1,
        .CanIfTxPduId = 1,
        .PduRRxPduId = 3,
    },
};

const CanTp_ConfigType CanTp_Config = {
    .CanTpRxPduCfg = CanTpRx_DiagCfg,
    .CanTpTxPduCfg = CanTpTx_DiagCfg,
};

TxStateType CanTpTxState_Diag[NUMBER_OF_CANTP_TX];
RxStateType CanTpRxState_Diag[NUMBER_OF_CANTP_RX];

CanTp_StateType CanTp_State = {
    .TxState = CanTpTxState_Diag,
    .RxState = CanTpRxState_Diag,
};