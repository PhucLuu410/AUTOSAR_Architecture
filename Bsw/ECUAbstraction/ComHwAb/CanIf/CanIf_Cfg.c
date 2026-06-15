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
        .CanIfTxPduBufferRef = CAN_1_CONTROLLER,
        .CanIfTxPduRef = 0,
    },
    {
        .CanIfTxPduId = 0,
        .CanIfTxPduReadNotifyStatus = TRUE,
        .CanIfTxPduTruncation = FALSE,
        .CanIfTxPduTypeCfg = CAN_ID_STATIC,
        .CanIfTxCanId = 0x7E0,
        .CanIfTxPduBufferRef = CAN_1_CONTROLLER,
        .CanIfTxPduRef = 1,
    },
    {
        .CanIfTxPduId = 2,
        .CanIfTxPduReadNotifyStatus = TRUE,
        .CanIfTxPduTruncation = FALSE,
        .CanIfTxPduTypeCfg = CAN_ID_STATIC,
        .CanIfTxCanId = 0x7E0,
        .CanIfTxPduBufferRef = CAN_1_CONTROLLER,
        .CanIfTxPduRef = 2,
    },
};

const CanIfInitCfg CanIfInitConfig = {
    .CanIfInitCfgSet = 0,
    .CanIfMaxBufferSize = 8,
    .CanIfMaxRxPduCfg = NUMBER_OF_CAN_IF_RX_PDU,
    .CanIfMaxTxPduCfg = NUMBER_OF_CAN_IF_TX_PDU,
    .CanIfRxPduCfgRef = CanIfRxPduCfgs,
    .CanIfTxPduCfgRef = CanIfTxPduCfgs,
};

const CanIf_ConfigType CanIf_Config = {
    .CanIfInitConfig = CanIfInitConfig,
};