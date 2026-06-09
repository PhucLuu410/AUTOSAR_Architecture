#include "CanIf_Cfg.h"
#include "Can_Cfg.h"
#include "Can_Cfg.h"
CanIfRxPduCfg CanIfRxPduCfgs[NUMBER_OF_CAN_IF_RX_PDU] = {
    {
        .CanIfRxPduDataLength = 8,
        .CanIfRxPduDataLengthCheck = FALSE,
        .CanIfRxPduId = 0,
        .CanIfRxPduReadData = TRUE,
        .CanIfRxPduReadNotifyStatus = TRUE,
        .CanIfRxCanId = 0x123,
        .CanIfRxPduHrhIdRef = CAN_1_CONTROLLER,
        .CanIfRxPduRef = 0,
    },
    {
        .CanIfRxPduDataLength = 8,
        .CanIfRxPduDataLengthCheck = FALSE,
        .CanIfRxPduId = 1,
        .CanIfRxPduReadData = TRUE,
        .CanIfRxPduReadNotifyStatus = TRUE,
        .CanIfRxCanId = 0x456,
        .CanIfRxPduHrhIdRef = CAN_1_CONTROLLER,
        .CanIfRxPduRef = 1,
    },
};

CanIfTxPduCfg CanIfTxPduCfgs[NUMBER_OF_CAN_IF_TX_PDU] = {
    {
        .CanIfTxPduId = 0,
        .CanIfTxPduReadNotifyStatus = TRUE,
        .CanIfTxPduTruncation = FALSE,
        .CanIfTxPduTypeCfg = CAN_ID_STATIC,
        .CanIfTxCanId = 0x123,
        .CanIfTxPduBufferRef = CAN_1_CONTROLLER,
        .CanIfTxPduRef = 0,
    },
    {
        .CanIfTxPduId = 1,
        .CanIfTxPduReadNotifyStatus = TRUE,
        .CanIfTxPduTruncation = FALSE,
        .CanIfTxPduTypeCfg = CAN_ID_STATIC,
        .CanIfTxCanId = 0x456,
        .CanIfTxPduBufferRef = CAN_1_CONTROLLER,
        .CanIfTxPduRef = 1,
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