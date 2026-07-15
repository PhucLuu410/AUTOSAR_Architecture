#include "PduR.h"
#include "PduR_Cfg.h"
#include "CanIf.h"
#include "CanTp.h"
#include "LinIf.h"
#include "Dcm.h"
#include "EcuM.h"
#include "Com.h"
#include "Det.h"

#include "Csm.h"
#include "string.h"

static const PduR_PBConfigType *PduR_LocalCfg = NULL_PTR;
void PduR_Init(const PduR_PBConfigType *ConfigPtr)
{
    if (ConfigPtr == NULL_PTR)
        return;

    PduR_LocalCfg = ConfigPtr;
}

Std_ReturnType PduR_ComTransmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr)
{
    if (PduInfoPtr != NULL_PTR)
    {
        uint8 Mac[16] = {0};
        uint32 MacLength = sizeof(Mac);
        Csm_MacGenerate(0,
                        CRYPTO_OPERATIONMODE_START,
                        PduInfoPtr->SduDataPtr,
                        PduInfoPtr->SduLength,
                        Mac,
                        &MacLength);

        uint8 TransmitData[8] = {0};
        for (uint8 i = 0; i < PduInfoPtr->SduLength; i++)
        {
            TransmitData[i] = PduInfoPtr->SduDataPtr[i];
        }
        TransmitData[6] = Mac[0];
        TransmitData[7] = Mac[1];

        PduInfoType IPdu;
        IPdu.SduLength = 8;
        IPdu.SduDataPtr = TransmitData;
        return PduR_RoutingTableTransmitConfig[TxPduId].TargetFuncPtr(PduR_RoutingTableTransmitConfig[TxPduId].LocalId, &IPdu);
    }
    return E_NOT_OK;
}

Std_ReturnType PduR_DcmTransmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr)
{
    if (PduInfoPtr != NULL_PTR)
    {
        return PduR_RoutingTableTransmitConfig[TxPduId].TargetFuncPtr(PduR_RoutingTableTransmitConfig[TxPduId].LocalId, PduInfoPtr);
    }
    return E_NOT_OK;
}

void PduR_CanIfRxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
    uint8 MacData[2] = {0};
    uint32 MacLength = sizeof(MacData);
    MacData[0] = PduInfoPtr->SduDataPtr[6];
    MacData[1] = PduInfoPtr->SduDataPtr[7];
    uint8 DataInputToVerify[8] = {0};
    for (int i = 0; i < PduInfoPtr->SduLength - 2; i++)
    {
        DataInputToVerify[i] = PduInfoPtr->SduDataPtr[i];
    }
    Crypto_VerifyResultType MacVerifyResult;
    Csm_MacVerify(1, CRYPTO_OPERATIONMODE_UPDATE, DataInputToVerify, PduInfoPtr->SduLength, MacData, MacLength, &MacVerifyResult);
    if (MacVerifyResult == CRYPTO_E_VER_OK)
    {
        PduInfoType PduInfo;
        PduInfo.SduLength = PduInfoPtr->SduLength;
        PduInfo.SduDataPtr = DataInputToVerify;
        Com_RxIndication(RxPduId, &PduInfo);
    }
}

void PduR_LinIfRxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
    Com_RxIndication(RxPduId, PduInfoPtr);
}

void PduR_CanTpRxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
    switch (RxPduId)
    {
    case 3:
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