#ifndef PDUR_CFG_H
#define PDUR_CFG_H

#include "PduR.h"
#include "ComStack_Types.h"
#include "Std_Types.h"

#define SIZE_OF_TX_PDUR_TABLE 3
#define SIZE_OF_RX_PDUR_TABLE 4

typedef struct
{
    uint16 GlobalId;
    void (*TargetFuncPtr)(PduIdType RxPduId, const PduInfoType *PduInfoPtr);
    uint16 LocalId;
} PduR_RoutingTableReceive;

typedef struct
{
    Std_ReturnType (*TargetFuncPtr)(PduIdType TxPduId, const PduInfoType *PduInfoPtr);
    uint16 LocalId;
} PduR_RoutingTableTransmit;

extern PduR_RoutingTableTransmit PduR_RoutingTableTransmitConfig[SIZE_OF_TX_PDUR_TABLE];
extern PduR_RoutingTableReceive PduR_RoutingTableReceiveConfig[SIZE_OF_RX_PDUR_TABLE];
extern PduR_PBConfigType PduR_Cfg;

#endif