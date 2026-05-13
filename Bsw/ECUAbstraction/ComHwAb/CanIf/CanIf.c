#include "CanIf.h"
#include "CanIf_Cfg.h"
#include "Can.h"
#include "PduR.h"

static const CanIf_ConfigType *CanIfGlobalConfigPtr = NULL_PTR;

void CanIf_Init(const CanIf_ConfigType *ConfigPtr)
{
    CanIfGlobalConfigPtr = ConfigPtr;
}

Std_ReturnType CanIf_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr)
{
    for (int i = 0; i < PduInfoPtr->SduLength; i++)
    {
        CanTxPduInfo[TxPduId].sdu[i] = PduInfoPtr->SduDataPtr[i];
    }
    CanTxPduInfo[TxPduId].length = PduInfoPtr->SduLength;

    return Can_Write(TxPduId, &CanTxPduInfo[TxPduId]);
}

void CanIf_RxIndication(const Can_HwType *Mailbox, const PduInfoType *PduInfPtr)
{
    for (int i = 0; i < SENSOR_USING_CAN; i++)
    {
        if (Mailbox->CanId == CanIfGlobalConfigPtr->RxTable[i].CanId)
        {
            PduR_RxIndication(i, PduInfPtr);
            break;
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