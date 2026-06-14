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
        .Id = 0,
        .TargetFuncPtr = CanIf_Transmit,
        .TargetPduId = 0,
    },
    {
        .Id = 1,
        .TargetFuncPtr = LinIf_Transmit,
        .TargetPduId = 1,
    },
    {
        .Id = 2,
        .TargetFuncPtr = CanTp_Transmit,
        .TargetPduId = 2,
    },
    {
        .Id = 3,
        .TargetFuncPtr = LinIf_Transmit,
        .TargetPduId = 3,
    },
};

PduR_RoutingTableReceive PduR_RoutingTableReceiveConfig[SIZE_OF_RX_PDUR_TABLE] = {
    {
        .Id = 0,
        .TargetFuncPtr = Com_RxIndication,
        .TargetPduId = 0,
    },
    {
        .Id = 1,
        .TargetFuncPtr = Com_RxIndication,
        .TargetPduId = 1,
    },
    {
        .Id = 2,
        .TargetFuncPtr = Com_RxIndication,
        .TargetPduId = 2,
    },
    {
        .Id = 3,
        .TargetFuncPtr = Com_RxIndication,
        .TargetPduId = 3,
    },
};