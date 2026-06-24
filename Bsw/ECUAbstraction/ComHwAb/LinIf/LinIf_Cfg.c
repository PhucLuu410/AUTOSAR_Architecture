#include "LinIf.h"
#include "LinIf_Cfg.h"
#include "Lin.h"
#include "Lin_Cfg.h"

LinIfFrame LinIfFrameConfigTx[NUMBER_OF_LINIF_FRAME_TX] = {
    [0] = {.LinIfChecksum = CLASSIC, .LinIfFrameId = 0x10, .LinIfFrameIndex = 0, .LinIfFrame = ASSIGN},
    [1] = {.LinIfChecksum = CLASSIC, .LinIfFrameId = 0x11, .LinIfFrameIndex = 1, .LinIfFrame = ASSIGN},
    [2] = {.LinIfChecksum = CLASSIC, .LinIfFrameId = 0x12, .LinIfFrameIndex = 2, .LinIfFrame = ASSIGN},
    [3] = {.LinIfChecksum = CLASSIC, .LinIfFrameId = 0x13, .LinIfFrameIndex = 3, .LinIfFrame = ASSIGN},
};

LinIf_ReceivePduType LinIfFrameConfigRx[NUMBER_OF_LINIF_FRAME_RX] = {
    [0] = {.Channel = LIN_CHANNEL_1, .PduId = 1, .Pid = 0x10, .Length = 8, .CsModel = CLASSIC, .Direction = LIN_DIRECTION_RX, .Receive_Func = PduR_LinIfRxIndication},
    [1] = {.Channel = LIN_CHANNEL_1, .PduId = 1, .Pid = 0x3D, .Length = 8, .CsModel = CLASSIC, .Direction = LIN_DIRECTION_RX, .Receive_Func = LinTp_RxIndication},
    [2] = {.Channel = LIN_CHANNEL_1, .PduId = 2, .Pid = 0x10, .Length = 8, .CsModel = CLASSIC, .Direction = LIN_DIRECTION_RX, .Receive_Func = LinTp_RxIndication},
    [3] = {.Channel = LIN_CHANNEL_1, .PduId = 3, .Pid = 0x14, .Length = 8, .CsModel = CLASSIC, .Direction = LIN_DIRECTION_RX, .Receive_Func = LinTp_RxIndication},
};

LinIfChannel LinIfChannelConfig[NUMBER_OF_LIN_CHANNEL] = {
    [0] = {
        .LinIfBusIdleTimeoutPeriod = 100,
        .LinIfGotoSleepConfirmationUL = GOTO_SLEEP_LIN_SM,
        .LinIfMainFunctionPeriod = 10,
        .LinIfWakeupConfirmationUL = WAKE_UP_LIN_SM,
        .LinIfChannelRef = LIN_CHANNEL_1,
        .LinIfComMNetworkHandleRef = 0,
        .LinIfFrameCfg = LinIfFrameConfigTx,
    },
    [1] = {
        .LinIfBusIdleTimeoutPeriod = 200,
        .LinIfGotoSleepConfirmationUL = GOTO_SLEEP_CDD,
        .LinIfMainFunctionPeriod = 20,
        .LinIfWakeupConfirmationUL = WAKE_UP_CDD,
        .LinIfChannelRef = LIN_CHANNEL_2,
        .LinIfComMNetworkHandleRef = 1,
        .LinIfFrameCfg = LinIfFrameConfigTx,
    },
};

LinIf_ConfigType LinIf_Config = {
    .LinIfGeneralCfg = {
        .LinIfBusMirroringSupported = FALSE,
        .LinIfDevErrorDetect = TRUE,
        .LinIfMultipleDriversSupported = FALSE,
        .LinIfMultipleTrcvDriverSupported = FALSE,
        .LinIfNcOptionalRequestSupported = FALSE,
        .LinIfTpSupported = FALSE,
        .LinIfTrcvDriverSupported = FALSE,
    },
    .LinIfGlobalCfg = {
        .LinIfChannelCfg = LinIfChannelConfig,
    },
};

//-------------------------------------------------------------------------------------------------
const LinTpGeneral LinTpGeneralConfig = {
    .LinTpChangeParameterApi = FALSE,
};

LinTpChannelConfig LinTpChannelCfg = {
    .LinTpDropNotRequestedNad = FALSE,
    .LinTpMaxNumberOfRespPendingFrames = 0,
    .LinTpP2Max = 0,
    .LinTpP2Timing = 0,
    .LinTpScheduleChangeDiag = FALSE,
    .LinTpChannelRef = 0,
};

uint8 LinTpRxNSduPdu0[20] = {0};

LinTpRxNSdu LinTpRxNSduCfg[NUMBER_OF_LINTP_FRAME_RX] = {
    [0] = {.LinTpRxNSduId = 0,
           .LinTpRxNSduNad = 0x3C,
           .LinTpRxNSduChannelRef = LIN_CHANNEL_1,
           .LinTpRxNSduPduRef = LinTpRxNSduPdu0},
};

uint8 LinTpTxNSduPdu0[20] = {0};

LinTpTxNSdu LinTpTxNSduCfg[NUMBER_OF_LINTP_FRAME_TX] = {
    [0] = {.LinTpMaxBufReq = 3,
           .LinTpNas = 0,
           .LinTpTxNSduId = 0,
           .LinTpTxNSduNad = 0x3C,
           .LinTpTxNSduChannelRef = LIN_CHANNEL_1,
           .LinTpTxNSduPduRef = LinTpTxNSduPdu0},
};

const LinTpGlobalConfig LinTpGlobal = {
    .LinTpMaxRxNSduCnt = 0,
    .LinTpMaxTxNSduCnt = 0,
    .LinTpChannelCfg = &LinTpChannelCfg,
    .LinTpRxNSduCfg = LinTpRxNSduCfg,
    .LinTpTxNSduCfg = LinTpTxNSduCfg,
};

LinTp_ConfigType LinTp_Config = {
    .LinTpGlobalCfg = LinTpGlobal,
    .LinTpGeneralCfg = LinTpGeneralConfig,
};