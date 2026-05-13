#ifndef __PDUR_H
#define __PDUR_H

#include "ComStack_Types.h"
#include "Std_Types.h"

typedef uint16 PduR_PBConfigIdType;
typedef uint16 PduR_RoutingPathGroupIdType;

typedef struct
{
    PduIdType TxPduId;
    Std_ReturnType (*Transmit_Func)(PduIdType TxPduId, const PduInfoType *PduInfoPtr);
} PduR_TxRoutingPathType;
typedef struct
{
    PduIdType RxPduId;
    void (*Rx_Func)(PduIdType PduId, const PduInfoType *PduInfoPtr);
} PduR_RxRoutingPathType;

typedef struct
{
    PduR_TxRoutingPathType *TxRoutingTable;
    PduR_RxRoutingPathType *RxRoutingTable;
} PduR_PBConfigType;

void PduR_Init(const PduR_PBConfigType *ConfigPtr);
void PduR_RxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr);
Std_ReturnType PduR_ComTransmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr);
void PduR_CanIfTxConfirmation(PduIdType TxPduId, Std_ReturnType result);

// void PduR_Init(const PduR_PBConfigType *ConfigPtr);
// PduR_PBConfigIdType PduR_GetConfigurationId(void);
// void PduR_EnableRouting(PduR_RoutingPathGroupIdType id);
// void PduR_DisableRouting(PduR_RoutingPathGroupIdType id,boolean initialize);
// Std_ReturnType PduR_<User : Up> Transmit(PduIdType TxPduId,const PduInfoType *PduInfoPtr);
// Std_ReturnType PduR_<User : Up> CancelTransmit(PduIdType TxPduId);
// Std_ReturnType PduR_<User : Up> CancelReceive(PduIdType RxPduId);
// void PduR_<User : Up> ReleaseRxBuffer(PduIdType RxPduId);
// void PduR_<User : Lo> RxIndication(PduIdType RxPduId,const PduInfoType *PduInfoPtr);
// void PduR_<User : Lo> TxConfirmation(PduIdType TxPduId,Std_ReturnType result);
// Std_ReturnType PduR_<User : Lo> TriggerTransmit(PduIdType TxPduId,PduInfoType *PduInfoPtr);
// BufReq_ReturnType PduR_<User : LoTp> CopyRxData(PduIdType id,const PduInfoType *info,PduLengthType *bufferSizePtr);
// void PduR_<User : LoTp> RxIndication(PduIdType id,Std_ReturnType result);
// BufReq_ReturnType PduR_<User : LoTp> StartOfReception(PduIdType id,const PduInfoType *info,PduLengthType TpSduLength,PduLengthType *bufferSizePtr);
// BufReq_ReturnType PduR_<User : LoTp> CopyTxData(PduIdType id,const PduInfoType *info,const RetryInfoType *retry,PduLengthType *availableDataPtr);
// void PduR_<User : LoTp> TxConfirmation(PduIdType id,Std_ReturnType result);

#endif