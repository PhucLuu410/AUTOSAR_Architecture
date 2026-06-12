#ifndef __PDUR_H
#define __PDUR_H

#include "ComStack_Types.h"
#include "Std_Types.h"

typedef uint16 PduR_PBConfigIdType;
typedef uint16 PduR_RoutingPathGroupIdType;

typedef struct
{
    PduIdType GlobalPduId;
    PduIdType LocalPduId;
    Std_ReturnType (*Transmit_Func)(PduIdType TxPduId, const PduInfoType *PduInfoPtr);
} PduR_TxRoutingPathType;
typedef struct
{
    PduIdType GlobalPduId;
    PduIdType LocalPduId;
    void (*Rx_Func)(PduIdType PduId, const PduInfoType *PduInfoPtr);
} PduR_RxRoutingPathType;

typedef struct
{
    PduR_TxRoutingPathType *TxRoutingTable;
    PduR_RxRoutingPathType *RxRoutingTable;
} PduR_PBConfigType;

// void PduR_Init(const PduR_PBConfigType *ConfigPtr);
void PduR_RxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr);
Std_ReturnType PduR_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr);
void PduR_CanIfTxConfirmation(PduIdType TxPduId, Std_ReturnType result);
#endif