#include "CanIf_Cfg.h"
#include "Can_Cfg.h"
#include "Can_Cfg.h"
CanIfRxPduCfg CanIfRxPduCfgs[NUMBER_OF_CAN_IF_RX_PDU] = {
    {
        .CanIfRxPduDataLength = 8,
        .CanIfRxPduDataLengthCheck = FALSE,
        .CanIfRxPduId = 1,
        .CanIfRxPduReadData = TRUE,
        .CanIfRxPduReadNotifyStatus = TRUE,
        .CanIfRxCanId = 0x180,
        .CanIfRxPduHrhIdRef = CAN_1_CONTROLLER,
        .CanIfRxPduRef = 0,
        .TargetPduIdDestination = 1,
    },
    {
        .CanIfRxPduDataLength = 8,
        .CanIfRxPduDataLengthCheck = FALSE,
        .CanIfRxPduId = 0,
        .CanIfRxPduReadData = TRUE,
        .CanIfRxPduReadNotifyStatus = TRUE,
        .CanIfRxCanId = 0x7E8,
        .CanIfRxPduHrhIdRef = CAN_1_CONTROLLER,
        .CanIfRxPduRef = 0,
        .TargetPduIdDestination = 0,
    },
};

CanIfTxPduCfg CanIfTxPduCfgs[NUMBER_OF_CAN_IF_TX_PDU] = {
    {
        .CanIfTxPduId = 1,
        .CanIfTxPduReadNotifyStatus = TRUE,
        .CanIfTxPduTruncation = FALSE,
        .CanIfTxPduTypeCfg = CAN_ID_STATIC,
        .CanIfTxCanId = 0x181,
        .CanIfCanHoh = 0,
    },
    {
        .CanIfTxPduId = 0,
        .CanIfTxPduReadNotifyStatus = TRUE,
        .CanIfTxPduTruncation = FALSE,
        .CanIfTxPduTypeCfg = CAN_ID_STATIC,
        .CanIfTxCanId = 0x7E0,
        .CanIfCanHoh = 0,
    }};

CanIfRxPduCfg CanIfRxPduTable[] = {
    [0] = {
        .CanIfRxPduId = 0,
        .CanIfRxCanId = 0x180,
        .DestinationFuncPtr = PduR_CanIfRxIndication,
    },
    [1] = {
        .CanIfRxPduId = 0,
        .CanIfRxCanId = 0x7E8,
        .DestinationFuncPtr = CanTp_RxIndication,
    }};

const CanIf_ConfigType CanIf_Config = {
    .CanIfRxPduCfgRef = CanIfRxPduTable,
    .CanIfTxPduCfgRef = CanIfTxPduTable,
};