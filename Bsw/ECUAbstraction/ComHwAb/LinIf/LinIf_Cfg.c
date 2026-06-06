#include "LinIf.h"
#include "LinIf_Cfg.h"

LinIfFrame LinIfFrameConfig[2] = {
    {
        .LinIfChecksumType_0 = CLASSIC,
        .LinIfFrameId = 0x20,
        .LinIfFrameIndex = 0,
        .LinIfFrameType_0 = UNCONDITIONAL,
        .LinIfFixedFrameSdu = {0},
    },
    {
        .LinIfChecksumType_0 = CLASSIC,
        .LinIfFrameId = 0x21,
        .LinIfFrameIndex = 1,
        .LinIfFrameType_0 = UNCONDITIONAL,
        .LinIfFixedFrameSdu = {0},
    },
};

LinIfChannel LinIfChannel1 = {
    .LinIfChannelRef_0 = LIN_CHANNEL_1,
    .LinIfComMNetworkHandleRef_0 = 2,
    .LinIfNodeType_0 = LINIF_SLAVE,
    .LinIfBusIdleTimeoutPeriod_0 = 10,
    .LinIfGotoSleepConfirmationUL_0 = GOTO_SLEEP_LIN_SM,
    .LinIfWakeupConfirmationUL_0 = WAKEUP_LIN_SM,
    .LinIfMainFunctionPeriod = 20,
    .LinIfFrame_0 = LinIfFrameConfig,
};

LinIfGlobalConfig LinIfGlobalConfig1 = {
    .LinIfChannel_0 = &LinIfChannel1,
};

LinIfGeneral LinIfGeneral1 = {
    .LinIfBusMirroringSupported = FALSE,
    .LinIfDevErrorDetect = FALSE,
    .LinIfMultipleDriversSupported = FALSE,
    .LinIfMultipleTrcvDriverSupported = FALSE,
    .LinIfNcOptionalRequestSupported = FALSE,
    .LinIfTpSupported = TRUE,
    .LinIfTrcvDriverSupported = FALSE,
    .LinIfVersionInfoApi = FALSE,
};

const LinIf_ConfigType LinIf_Config = {
    .LinIfGlobalConfig_0 = &LinIfGlobalConfig1,
    .LinIfGeneral_0 = &LinIfGeneral1,
};

//---------------------------------------------------------------------------------------------------------
LinTpRxNSdu LinTpRxNSduConfig[1] = {
    {
        .LinTpNcr = 0,
        .LinTpRxNSduId = 0,
        .LinTpRxNSduNad = 0x12,
        .LinTpRxNSduChannelRef = LIN_CHANNEL_1,
        .LinTpRxNSduPduRef = NULL_PTR,
    },
};

uint8 Buffer_ID_0x12[20] = {0};

LinTpTxNSdu LinTpTxNSduConfig[1] = {
    {
        .LinTpMaxBufReq = 3,
        .LinTpNas = 0,
        .LinTpNcs = 0,
        .LinTpTxNSduId = 0,
        .LinTpTxNSduNad = 0x12,
        .LinTpTxNSduChannelRef = LIN_CHANNEL_1,
        .LinTpTxNSduPduRef = Buffer_ID_0x12,
    },
};

LinTpChannelConfig LinTpChannelConfig1[1] = {
    {
        .LinTpDropNotRequestedNad = FALSE,
        .LinTpMaxNumberOfRespPendingFrames = 0,
        .LinTpP2Max = 0,
        .LinTpP2Timing = 0,
        .LinTpScheduleChangeDiag = FALSE,
        .LinTpChannelRef = LIN_CHANNEL_1,
    },
};

LinTpGlobalConfig LinTpGlobalConfig_0 = {
    .LinTpMaxRxNSduCnt = 1,
    .LinTpMaxTxNSduCnt = 1,
    .LinTpChannelConfig_0 = LinTpChannelConfig1,
    .LinTpDemEventParameterRefs_0 = NULL_PTR,
    .LinTpRxNSdu_0 = LinTpRxNSduConfig,
    .LinTpTxNSdu_0 = LinTpTxNSduConfig,
};

LinTpGeneral LinTpGeneral_0 = {
    .LinTpChangeParameterApi = FALSE,
};

const LinTp_ConfigType LinTp_Config = {
    .LinTpGlobalConfig_0 = &LinTpGlobalConfig_0,
    .LinTpGeneral_0 = &LinTpGeneral_0,
};
