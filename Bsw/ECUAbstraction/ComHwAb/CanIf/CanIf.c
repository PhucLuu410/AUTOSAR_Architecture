#include "CanIf.h"
#include "CanIf_Cfg.h"
#include "Can.h"
#include "PduR.h"

static const CanIf_ConfigType *CanIfGlobalConfigPtr = NULL_PTR;

void CanIf_Init(const CanIf_ConfigType *ConfigPtr)
{
    CanIfGlobalConfigPtr = ConfigPtr;
}

void CanIf_DeInit(void)
{
    CanIfGlobalConfigPtr = NULL_PTR;
}

void CanIf_TxConfirmation(PduIdType CanTxPduId)
{
    PduR_CanIfTxConfirmation(CanTxPduId, E_OK);
}

// Std_ReturnType CanIf_SetControllerMode(uint8 ControllerId, Can_ControllerStateType ControllerMode)
// {
// }

Std_ReturnType CanIf_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoType)
{
    static uint8 MailBox_Round_Robin = 0;
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
    MailBox_Round_Robin = (MailBox_Round_Robin + 1) % 3;
    return Can_Write(MailBox_Round_Robin, &CanTxPduInfo[TxPduId]);
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