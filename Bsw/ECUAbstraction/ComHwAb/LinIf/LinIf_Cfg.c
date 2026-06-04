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

uint8 Pdu1Data[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
uint8 Pdu2Data[] = {0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x06, 0x07};
uint8 Pdu3Data[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

Lin_PduType HeaderPdu1 = {.CsModel = LIN_CLASSIC_CS,
                          .Dl = 0,
                          .Pid = 0x20,
                          .Response = LIN_FRAMERESPONSE_TX,
                          .SduDataPtr = NULL_PTR};

Lin_PduType HeaderPdu2 = {.CsModel = LIN_CLASSIC_CS,
                          .Dl = 0,
                          .Pid = 0x21,
                          .Response = LIN_FRAMERESPONSE_TX,
                          .SduDataPtr = NULL_PTR};

Lin_PduType HeaderPdu3 = {.CsModel = LIN_CLASSIC_CS,
                          .Dl = 0,
                          .Pid = 0x22,
                          .Response = LIN_FRAMERESPONSE_TX,
                          .SduDataPtr = NULL_PTR};

Lin_PduType DataPdu1 = {.CsModel = LIN_CLASSIC_CS,
                        .Dl = 8,
                        .Pid = 0x20,
                        .Response = LIN_FRAMERESPONSE_TX,
                        .SduDataPtr = Pdu1Data};

Lin_PduType DataPdu2 = {.CsModel = LIN_CLASSIC_CS,
                        .Dl = 8,
                        .Pid = 0x21,
                        .Response = LIN_FRAMERESPONSE_TX,
                        .SduDataPtr = Pdu2Data};

Lin_PduType DataPdu3 = {.CsModel = LIN_CLASSIC_CS,
                        .Dl = 8,
                        .Pid = 0x22,
                        .Response = LIN_FRAMERESPONSE_TX,
                        .SduDataPtr = Pdu3Data};
