#include "PduR_Cfg.h"
#include "CanIf.h"
#include "CanTp.h"
#include "LinIf.h"
#include "Dcm.h"
#include "EcuM.h"
#include "Com.h"
#include "Det.h"

PduRGeneral PduGeneralCfg = {
    .PduRDevErrorDetect = FALSE,
    .PduRMetaDataSupport = FALSE,
    .PduRZeroCostOperation = FALSE,
};
PduRRoutingPaths PduRRoutingPathsCfg = {
    .PduRConfigurationId = 0,
};

PduR_PBConfigType PduR_Cfg = {
    .PduRGeneralConfig = &PduGeneralCfg,
    .PduRRoutingPathsConfig = &PduRRoutingPathsCfg,
};

PduR_RoutingTableTransmit PduR_RoutingTableTransmitConfig[SIZE_OF_TX_PDUR_TABLE] = {
    [0] = {
        .TargetFuncPtr = CanIf_Transmit,
        .LocalId = 0,
    },
    [1] = {
        .TargetFuncPtr = CanTp_Transmit,
        .LocalId = 0,
    },
};