#include "Lin_Cfg.h"
#include "Lin_GeneralTypes.h"

LinGobalConfig LinGlobalConfig_0 = {
    .LinChannel_0 = &(LinChannel){
        .LinChannelBaudRate = 115200,
        .LinChannelId = LIN_CHANNEL_1,
        .LinChannelWakeupSupport = 1,
        .LinNodeType = LIN_SLAVE,
        .LinClockRef = 8000000,
    },
};

LinGeneral LinGeneral_0 = {
    .LinDevErrorDetect = 0,
    .LinIndex = 0,
    .LinTimeoutDuration = 100,
    .LinVersionInfoApi = 0,
};

Lin_ConfigType Lin_Config = {
    .LinGeneral_0 = &LinGeneral_0,
    .LinGlobalConfig_0 = &LinGlobalConfig_0};

uint8 Lin_RxData1[9];
uint8 Lin_RxData2[9];
uint8 Lin_RxData3[9];
uint8 Lin_RxData4[9];

Lin_PduType Lin_DataCfg[NUMBER_OF_LIN_PDU] = {
    [0] = {.Pid = 0x3C, .Dl = 8, .CsModel = LIN_CLASSIC_CS, .Response = LIN_FRAMERESPONSE_RX, .SduDataPtr = Lin_RxData1},
    [1] = {.Pid = 0x3D, .Dl = 8, .CsModel = LIN_CLASSIC_CS, .Response = LIN_FRAMERESPONSE_RX, .SduDataPtr = Lin_RxData2},
    [2] = {.Pid = 0x12, .Dl = 8, .CsModel = LIN_CLASSIC_CS, .Response = LIN_FRAMERESPONSE_RX, .SduDataPtr = Lin_RxData3},
    [3] = {.Pid = 0x14, .Dl = 8, .CsModel = LIN_CLASSIC_CS, .Response = LIN_FRAMERESPONSE_RX, .SduDataPtr = Lin_RxData4},
};