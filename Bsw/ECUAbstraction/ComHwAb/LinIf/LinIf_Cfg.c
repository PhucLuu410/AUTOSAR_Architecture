#include "LinIf.h"
#include "LinIf_Cfg.h"
#include "Lin.h"
#include "Lin_Cfg.h"

LinIfFrame LinIfFrameConfig[NUMBER_OF_LINIF_FRAME] = {
    [0] = {.LinIfChecksum = CLASSIC, .LinIfFrameId = 0x10, .LinIfFrameIndex = 0, .LinIfFrame = ASSIGN},
    [1] = {.LinIfChecksum = CLASSIC, .LinIfFrameId = 0x11, .LinIfFrameIndex = 1, .LinIfFrame = ASSIGN},
    [2] = {.LinIfChecksum = CLASSIC, .LinIfFrameId = 0x12, .LinIfFrameIndex = 2, .LinIfFrame = ASSIGN},
    [3] = {.LinIfChecksum = CLASSIC, .LinIfFrameId = 0x13, .LinIfFrameIndex = 3, .LinIfFrame = ASSIGN},
};

LinIfChannel LinIfChannelConfig[NUMBER_OF_LIN_CHANNEL] = {
    [0] = {
        .LinIfBusIdleTimeoutPeriod = 100,
        .LinIfGotoSleepConfirmationUL = GOTO_SLEEP_LIN_SM,
        .LinIfMainFunctionPeriod = 10,
        .LinIfWakeupConfirmationUL = WAKE_UP_LIN_SM,
        .LinIfChannelRef = LIN_CHANNEL_1,
        .LinIfComMNetworkHandleRef = 0,
        .LinIfFrameCfg = LinIfFrameConfig,
    },
    [1] = {
        .LinIfBusIdleTimeoutPeriod = 200,
        .LinIfGotoSleepConfirmationUL = GOTO_SLEEP_CDD,
        .LinIfMainFunctionPeriod = 20,
        .LinIfWakeupConfirmationUL = WAKE_UP_CDD,
        .LinIfChannelRef = LIN_CHANNEL_2,
        .LinIfComMNetworkHandleRef = 1,
        .LinIfFrameCfg = LinIfFrameConfig,
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