#include "CanIf.h"
#include "CanIf_Cfg.h"
#include "Can.h"
#include "Can_Cfg.h"
#include "Can_GeneralTypes.h"
#include "PduR.h"
#include "PduR_Cfg.h"

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
    PduR_RxIndication(Mailbox->CanId, PduInfPtr);
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