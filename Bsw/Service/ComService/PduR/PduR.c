#include "PduR.h"
#include "PduR_Cfg.h"
#include "CanIf.h"
#include "LinIf.h"
#include "Dcm.h"
#include "EcuM.h"
#include "Com.h"
#include "Det.h"
static const PduR_PBConfigType *PduR_LocalCfg = NULL_PTR;
void PduR_Init(const PduR_PBConfigType *ConfigPtr)
{
    if (ConfigPtr == NULL_PTR)
        return;

    PduR_LocalCfg = ConfigPtr;
}

Std_ReturnType PduR_ComTransmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr)
{
    for (int i = 0; i < SIZE_OF_TX_PDUR_TABLE; i++)
    {
        if (TxPduId == PduR_RoutingTableTransmitConfig[i].GlobalId)
        {
            return PduR_RoutingTableTransmitConfig[i].TargetFuncPtr(PduR_RoutingTableTransmitConfig[i].LocalId, PduInfoPtr);
        }
    }
    return 0;
}

void PduR_CanIfRxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
    for (int i = 0; i < SIZE_OF_RX_PDUR_TABLE; i++)
    {
        if (RxPduId == PduR_RoutingTableReceiveConfig[i].GlobalId)
        {
            return PduR_RoutingTableReceiveConfig[i].TargetFuncPtr(PduR_RoutingTableReceiveConfig[i].LocalId, PduInfoPtr);
        }
    }
}

void PduR_LinIfRxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
    for (int i = 0; i < SIZE_OF_RX_PDUR_TABLE; i++)
    {
        if (RxPduId == PduR_RoutingTableReceiveConfig[i].GlobalId)
        {
            PduR_RoutingTableReceiveConfig[i].TargetFuncPtr(PduR_RoutingTableReceiveConfig[i].LocalId, PduInfoPtr);
        }
    }
}

void PduR_CanTpRxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
    for (int i = 0; i < SIZE_OF_RX_PDUR_TABLE; i++)
    {
        if (RxPduId == PduR_RoutingTableReceiveConfig[i].GlobalId)
        {
            PduR_RoutingTableReceiveConfig[i].TargetFuncPtr(PduR_RoutingTableReceiveConfig[i].LocalId, PduInfoPtr);
        }
    }
}