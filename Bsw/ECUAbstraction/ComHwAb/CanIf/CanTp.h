#ifndef CANTP_H
#define CANTP_H

#include "ComStack_Types.h"
#include "Std_Types.h"

typedef struct
{
    uint32 CanTpTxNPduConfirmationPduId;
    uint8 *CanTpTxNPduRef;
} CanTpTxNPdu;

typedef enum
{
    CANTP_TX_EXTENDED,
    CANTP_TX_MIXED,
    CANTP_TX_MIXED29BIT,
    CANTP_TX_NORMALFIXED,
    CANTP_TX_STANDARD,
} CanTpTxAddressingFormat;

typedef struct
{
    uint32 CanTpNas;
    boolean CanTpTc;
    CanTpTxAddressingFormat *CanTpTxAddressingFormatCfg;
    uint32 CanTpTxNSduIdCfg;
    uint8 *CanTpTxNSduRef;
    CanTpTxNPdu *CanTpTxNPduRefCfg;
} CanTpTxNSdu;

typedef enum
{
    CANTP_RX_EXTENDED,
    CANTP_RX_MIXED,
    CANTP_RX_MIXED29BIT,
    CANTP_RX_NORMALFIXED,
    CANTP_RX_STANDARD,
} CanTpRxAddressingFormat;

typedef struct
{
    uint32 CanTpRxNPduIdCfg;
    uint8 *CanTpRxNPduRef;
} CanTpRxNPdu;

typedef struct
{
    CanTpRxAddressingFormat *CanTpRxAddressingFormatCfg;
    uint32 CanTpRxNSduIdCfg;
    boolean CanTpRxPaddingActivationCfg;
    uint8 *CanTpRxNSduRef;
    CanTpRxNPdu *CanTpRxNPduRefCfg;
} CanTpRxNSdu;

typedef struct
{
    CanTpRxNSdu *CanTpRxNSduCfg;
    CanTpTxNSdu *CanTpTxNSduCfg;
} CanTpChannel;

typedef struct
{
    CanTpChannel *CanTpChannelCfg;
} CanTpConfig;

typedef enum
{
    CANTP_E_CANTPNAR_TIMEOUT_OCCURRED = 1,
    CANTP_E_CANTPNAS_TIMEOUT_OCCURRED,
    CANTP_E_CANTPNBR_TIMEOUT_OCCURRED,
    CANTP_E_CANTPNBS_TIMEOUT_OCCURRED,
    CANTP_E_CANTPNCR_TIMEOUT_OCCURRED,
    CANTP_E_CANTPNCS_TIMEOUT_OCCURRED,
    CANTP_E_DROPPED_CONSECUTIVE_FRAMES_DETECTED,
    CANTP_E_FC_OVERFLOW_RECEIVED,
    CANTP_E_FC_OVERFLOW_TRANSMITTED,
    CANTP_E_SWAPPED_CONSECUTIVE_FRAMES_RECEIVED,
} CanTpDemEventParameterRefs;

typedef struct
{
    boolean CanTpChangeParameterApi;
    boolean CanTpDevErrorDetect;
    boolean CanTpDynIdSupport;
    boolean CanTpEnableSecurityEventReporting;
    boolean CanTpFlexibleDataRateSupport;
    boolean CanTpGenericConnectionSupport;
    uint8 CanTpPaddingByte;
    boolean CanTpPendingTxNSduSupport;
    boolean CanTpReadParameterApi;
} CanTpGeneral;

typedef struct
{
    CanTpConfig *CanTpCfg;
    CanTpDemEventParameterRefs *CanTpDemEventParameterRefsCfg;
    CanTpGeneral *CanTpGeneralCfg;
} CanTp_ConfigType;

void CanTp_Init(const CanTp_ConfigType *CfgPtr);
void CanTp_Shutdown(void);
Std_ReturnType CanTp_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr);
Std_ReturnType CanTp_CancelTransmit(PduIdType TxPduId);
Std_ReturnType CanTp_CancelReceive(PduIdType RxPduId);
Std_ReturnType CanTp_ChangeParameter(PduIdType id, TPParameterType parameter, uint16 value);
Std_ReturnType CanTp_ReadParameter(PduIdType id, TPParameterType parameter, uint16 *value);
void CanTp_MainFunction(void);
void CanTp_RxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr);
void CanTp_TxConfirmation(PduIdType TxPduId, Std_ReturnType result);

#endif