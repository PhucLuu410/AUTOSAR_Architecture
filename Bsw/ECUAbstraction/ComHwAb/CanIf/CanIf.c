#include "CanIf.h"
#include "CanIf_Cfg.h"
#include "Can.h"
#include "Can_Cfg.h"
#include "Can_GeneralTypes.h"

static const CanIf_ConfigType *CanIfGlobalConfigPtr = NULL_PTR;

void CanIf_Init(const CanIf_ConfigType *ConfigPtr)
{
    CanIfGlobalConfigPtr = ConfigPtr;
}

Std_ReturnType CanIf_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr)
{
    for (int i = 0; i < PduInfoPtr->SduLength; i++)
    {
        CanIfGlobalConfigPtr->TxPduConfig[TxPduId].sdu[i] = PduInfoPtr->SduDataPtr[i];
    }
    CanIfGlobalConfigPtr->TxPduConfig[TxPduId].length = PduInfoPtr->SduLength;

    return Can_Write(TxPduId, &CanIfGlobalConfigPtr->TxPduConfig[TxPduId]);
}

void CanIf_RxIndication(const Can_HwType *Mailbox, const PduInfoType *PduInfPtr)
{
    if (Mailbox->CanId == SENSOR_0_ID)
    {
        CanIfGlobalConfigPtr->RxPduConfig[SENSOR_0].SduLength = PduInfPtr->SduLength;
        for (int i = 0; i < PduInfPtr->SduLength; i++)
        {
            CanIfGlobalConfigPtr->RxPduConfig[SENSOR_0].SduDataPtr[i] = PduInfPtr->SduDataPtr[i];
        }
    }
    else if (Mailbox->CanId == SENSOR_1_ID)
    {
        CanIfGlobalConfigPtr->RxPduConfig[SENSOR_1].SduLength = PduInfPtr->SduLength;
        for (int i = 0; i < PduInfPtr->SduLength; i++)
        {
            CanIfGlobalConfigPtr->RxPduConfig[SENSOR_1].SduDataPtr[i] = PduInfPtr->SduDataPtr[i];
        }
    }
    else if (Mailbox->CanId == SENSOR_2_ID)
    {
        CanIfGlobalConfigPtr->RxPduConfig[SENSOR_2].SduLength = PduInfPtr->SduLength;
        for (int i = 0; i < PduInfPtr->SduLength; i++)
        {
            CanIfGlobalConfigPtr->RxPduConfig[SENSOR_2].SduDataPtr[i] = PduInfPtr->SduDataPtr[i];
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