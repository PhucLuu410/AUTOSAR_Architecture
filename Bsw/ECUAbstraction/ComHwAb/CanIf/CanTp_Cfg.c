#include "CanTp_Cfg.h"
#include "CanTp.h"
#include "Std_Types.h"

//----------------------------------------------------------------------

uint8 RxDataBuffer[20] = {0};
uint8 TxDataBuffer[20] = {0};

CanTpRxNPdu CanTpRxNPduCfg = {
    .CanTpRxNPduIdCfg = 1,
    .CanTpRxNPduRef = RxDataBuffer,
};

CanTpTxNPdu CanTpTxNPduCfg = {
    .CanTpTxNPduConfirmationPduId = 0,
    .CanTpTxNPduRef = TxDataBuffer,
};
//----------------------------------------------------------------------

CanTpRxAddressingFormat CanTpRxAddressingFormatCfg = CANTP_RX_STANDARD;

CanTpRxNSdu CanTpRxNsduConfig = {
    .CanTpRxAddressingFormatCfg = &CanTpRxAddressingFormatCfg,
    .CanTpRxNSduIdCfg = 3,
    .CanTpRxPaddingActivationCfg = FALSE,
    .CanTpRxNSduRef = NULL_PTR,
    .CanTpRxNPduRefCfg = &CanTpRxNPduCfg,
};

CanTpTxAddressingFormat CanTpTxAddressingFormatCfg = CANTP_TX_STANDARD;

//----------------------------------------------------------------------

CanTpTxNSdu CanTpTxNsduConfig = {
    .CanTpNas = 0,
    .CanTpTc = FALSE,
    .CanTpTxAddressingFormatCfg = &CanTpTxAddressingFormatCfg,
    .CanTpTxNSduIdCfg = 3,
    .CanTpTxNSduRef = NULL_PTR,
    .CanTpTxNPduRefCfg = &CanTpTxNPduCfg,
};

CanTpChannel CanTpChannelConfig = {
    .CanTpRxNSduCfg = &CanTpRxNsduConfig,
    .CanTpTxNSduCfg = &CanTpTxNsduConfig,
};

//----------------------------------------------------------------------

CanTpDemEventParameterRefs CanTpDemEventParameterRefsCfg = 1;

CanTpGeneral CanTpGeneralConfig = {
    .CanTpChangeParameterApi = FALSE,
    .CanTpDevErrorDetect = FALSE,
    .CanTpDynIdSupport = FALSE,
    .CanTpEnableSecurityEventReporting = FALSE,
    .CanTpFlexibleDataRateSupport = FALSE,
    .CanTpGenericConnectionSupport = FALSE,
    .CanTpPaddingByte = 8,
    .CanTpPendingTxNSduSupport = FALSE,
    .CanTpReadParameterApi = FALSE,
};

CanTpConfig CanTpCfg = {
    .CanTpChannelCfg = &CanTpChannelConfig,
};

const CanTp_ConfigType CanTp_Config = {
    .CanTpCfg = &CanTpCfg,
    .CanTpDemEventParameterRefsCfg = &CanTpDemEventParameterRefsCfg,
    .CanTpGeneralCfg = &CanTpGeneralConfig,
};
