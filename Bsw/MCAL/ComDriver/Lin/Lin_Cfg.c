#include "Lin_Cfg.h"

LinGobalConfig LinGlobalConfig_0 = {
    .LinChannel_0 = &(LinChannel){
        .LinChannelBaudRate = 115200,
        .LinChannelId = LIN_CHANNEL_1,
        .LinChannelWakeupSupport = 1,
        .LinNodeType = LIN_MASTER,
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

uint8 Lin_ElectronicWindowBuffer[10] = {0};
uint8 Lin_ElectricWipersBuffer[10] = {0};

uint8 *Lin_RxData[] = {[Lin_ElectronicWindow] = Lin_ElectronicWindowBuffer,
                       [Lin_ElectricWipers] = Lin_ElectricWipersBuffer};