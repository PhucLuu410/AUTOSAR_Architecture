#include "Lin_Cfg.h"

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

uint8 Channel_1_Buffer[10] = {0};
uint8 Channel_2_Buffer[10] = {0};

uint8 *Lin_RxData[] = {[LIN_CHANNEL_1] = Channel_1_Buffer,
                       [LIN_CHANNEL_2] = Channel_2_Buffer};