#include "CryIf_Cfg.h"

CryIf_ChannelConfig CryIf_Channel[NUMBER_OF_CRYIF_CHANNEL] = {
    {
        .CryIfChannelId = 0,
        .CryIfObjectId = 0,
    }};

CryIf_ConfigType CryIf_Config = {
    .CryIfChannel = CryIf_Channel};
