#include "CanIf.h"
#include "CanIf_Cfg.h"
#include "Can.h"
#include "PduR.h"

static const CanIf_ConfigType *CanIfGlobalConfigPtr = NULL_PTR;

void CanIf_Init(const CanIf_ConfigType *ConfigPtr)
{
    CanIfGlobalConfigPtr = ConfigPtr;
}

Std_ReturnType CanIf_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoType)
{
    for (int i = 0; i < CAN_SERSOR_DATA_LENGTH; i++)
    {
        if (TxPduId == CanIfGlobalConfigPtr->TxTableConfig[i].TxPduId)
        {
            for (int j = 0; j < PduInfoType->SduLength; j++)
            {
                CanIfGlobalConfigPtr->TxTableConfig[i].TxPduTable->sdu[j] = PduInfoType->SduDataPtr[j];
            }
            CanIfGlobalConfigPtr->TxTableConfig[i].TxPduTable->length = PduInfoType->SduLength;
        }
    }
    return Can_Write(CAN_MAILBOX_0, &CanTxPduInfo[TxPduId]);
}

void CanIf_RxIndication(const Can_HwType *Mailbox, const PduInfoType *PduInfPtr)
{
    for (int i = 0; i < CAN_SERSOR_DATA_LENGTH; i++)
    {
        if (Mailbox->CanId == CanIfGlobalConfigPtr->RxTableConfig[i].CanId)
        {
            PduR_RxIndication(CanIfGlobalConfigPtr->RxTableConfig[i].RxPduId, PduInfPtr);
        }
    }
}

// Std_ReturnType CanIf_ReadRxPduData(PduIdType CanIfRxPduId, PduInfoType *PduInfoPtr)
// {
//     for (int i = 0; i < CanIfGlobalConfigPtr->RxPduConfig->RxPduType[CanIfRxPduId].length; i++)
//     {
//         PduInfoPtr->SduDataPtr[i] = CanIfGlobalConfigPtr->RxPduConfig->RxPduType[CanIfRxPduId].sdu[i];
//     }
//     PduInfoPtr->SduLength = CanIfGlobalConfigPtr->RxPduConfig->RxPduType[CanIfRxPduId].length;
//     return E_OK;
// }