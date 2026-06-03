#include "LinIf.h"

const LinIf_FrameConfigType NormalFrames[] = {
    {0x20, 8, LINIF_UNCONDITIONAL, 0, 0, 0},
    {0x21, 20, LINIF_MRF, 1, 1, 10},
};

const LinIf_FrameConfigType DiagFrames[] = {{0x3C, 8, LINIF_MRF, 2, 0, 0}, {0x3D, 8, LINIF_SRF, 3, 1, 0}};

const LinIf_ScheduleTableType MyScheduleTables[] = {
    {0, LINIF_RUN_CONTINUOUS, NormalFrames, 2, 50},
    {1, LINIF_RUN_ONCE, DiagFrames, 2, 50},
};

const LinIf_ChannelConfigType MyLinChannels[] = {
    {0, MyScheduleTables, 2, TRUE}};

const LinTp_ChannelConfigType MyTpChannels[] = {
    {0x01, 150, 10, 64}};

const LinTp_ConfigType LinTp_Config = {
    MyTpChannels, 1 // 1 TP Channel
};

const LinIf_ConfigType LinIf_Config = {
    MyLinChannels, 1 // 1 Channel
};