#include "PduR.h"
#include "PduR_Cfg.h"
#include "CanIf.h"
#include "CanTp.h"
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

Std_ReturnType PduR_DcmTransmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr)
{
    return CanTp_Transmit(0, PduInfoPtr);
}

void PduR_CanIfRxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
    switch (RxPduId)
    {
    case 1:
        Com_RxIndication(RxPduId, PduInfoPtr);
        break;
    case 2:
        Com_RxIndication(RxPduId, PduInfoPtr);
        break;
    case 3:
        Com_RxIndication(RxPduId, PduInfoPtr);
        break;
    case 4:
        Com_RxIndication(RxPduId, PduInfoPtr);
        break;
    default:
        break;
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
    switch (RxPduId)
    {
    case 3:
        // Com_RxIndication(RxPduId, PduInfoPtr);
        Dcm_TpRxIndication(RxPduId, E_OK);
        break;
    }
}

BufReq_ReturnType PduR_CanTpCopyRxData(PduIdType id, const PduInfoType *info, PduLengthType *bufferSizePtr)
{
    switch (id)
    {
    case 3:
        return Dcm_CopyRxData(id, info, bufferSizePtr);
    default:
        return BUFREQ_NOT_OK;
    }
}

BufReq_ReturnType PduR_CanTpStartOfReception(PduIdType id, const PduInfoType *info, PduLengthType TpSduLength, PduLengthType *bufferSizePtr)
{
    switch (id)
    {
    case 3:
        return Dcm_StartOfReception(id, info, TpSduLength, bufferSizePtr);
    default:
        return BUFREQ_NOT_OK;
    }
}