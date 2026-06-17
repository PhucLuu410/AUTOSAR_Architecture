#ifndef CANTP_H
#define CANTP_H

#include "ComStack_Types.h"
#include "Std_Types.h"

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
    uint16 CanTpTxPduId;
    uint16 CanIfTxPduId;
} CanTpTxPduCfg;

typedef struct
{
    uint16 CanIfTxRespondPduId;
    uint16 CanTpRxPduId;
    uint16 PduRRxPduId;
} CanTpRxPduCfg;

typedef struct
{
    CanTpTxPduCfg *CanTpTxPduCfg;
    CanTpRxPduCfg *CanTpRxPduCfg;
} CanTp_ConfigType;

void CanTp_Init(const CanTp_ConfigType *CfgPtr);
void CanTp_Shutdown(void);
Std_ReturnType CanTp_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr);
void CanTp_RxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr);

#endif