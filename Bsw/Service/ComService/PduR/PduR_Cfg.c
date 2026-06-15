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
    {
        .GlobalId = 0,
        .TargetFuncPtr = CanIf_Transmit,
        .InterfaceId = 0,
    },
    {
        .GlobalId = 1,
        .TargetFuncPtr = CanIf_Transmit,
        .InterfaceId = 1,
    },
    {
        .GlobalId = 2,
        .TargetFuncPtr = CanIf_Transmit,
        .InterfaceId = 2,
    },
    {
        .GlobalId = 3,
        .TargetFuncPtr = LinIf_Transmit,
        .InterfaceId = 3,
    },
};

PduR_RoutingTableReceive PduR_RoutingTableReceiveConfig[SIZE_OF_RX_PDUR_TABLE] = {
    {
        .GlobalId = 0,
        .TargetFuncPtr = Com_RxIndication,
        .InterfaceId = 0,
    },
    {
        .GlobalId = 1,
        .TargetFuncPtr = Com_RxIndication,
        .InterfaceId = 1,
    },
    {
        .GlobalId = 2,
        .TargetFuncPtr = Com_RxIndication,
        .InterfaceId = 2,
    },
    {
        .GlobalId = 3,
        .TargetFuncPtr = Com_RxIndication,
        .InterfaceId = 3,
    },
};