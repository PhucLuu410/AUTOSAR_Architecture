#include "Csm_Cfg.h"

Csm_JobConfigType JobConfig[NUMBER_OF_CSM_JOB] = {
    {
        .KeyId = 0,
        .JobId = 0,
        .ChannelId = 0,
    },
    {
        .KeyId = 0,
        .JobId = 1,
        .ChannelId = 0,
    },
};

Csm_ConfigType Csm_Config = {
    .Csm_JobConfig = JobConfig};