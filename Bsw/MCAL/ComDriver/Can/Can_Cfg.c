#include "Can_Cfg.h"
#include "Can.h"

const Can_ControllerConfigType Can_ControllerConfig_Set0 =
    {
        .CanPropagationDelay = 0,
        .CanTseg1 = 8,
        .CanTseg2 = 1,
        .CanSjw = 1,
        .TxProcessing = 0,
        .RxProcessing = 0,
        .BusOffProcessing = 1,
        .ErrorProcessing = 1};

const Can_HardwareObjectConfigType Can_HardwareConfigs_Set0[] =
    {
        {.CanHohHandle = 0,
         .CanIdType = 0,
         .CanFilterId = 0x000,
         .CanFilterMask = 0x000, // accept all
         .CanMultiplexTransmission = 0,
         .CanObjectType = 1}};

const Can_ConfigType CanConfig = {.ControllerConfig = &Can_ControllerConfig_Set0,
                                  .HardwareConfig = Can_HardwareConfigs_Set0};