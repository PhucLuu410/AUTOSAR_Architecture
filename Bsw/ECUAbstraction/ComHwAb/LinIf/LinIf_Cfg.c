#include "LinIf.h"
#include "LinIf_Cfg.h"

LinIfChannel LinIfChannel1 = {
    .LinIfChannelRef_0 = LIN_CHANNEL_1,
    .LinIfComMNetworkHandleRef_0 = 2,
    .LinIfNodeType_0 = LINIF_MASTER,
    .LinIfBusIdleTimeoutPeriod_0 = 10,
    .LinIfGotoSleepConfirmationUL_0 = GOTO_SLEEP_LIN_SM,
    .LinIfWakeupConfirmationUL_0 = WAKEUP_LIN_SM,
    .LinIfMainFunctionPeriod = 20,
    .LinIfFrame_0.LinIfFrameType_0 = CONDITIONAL,
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