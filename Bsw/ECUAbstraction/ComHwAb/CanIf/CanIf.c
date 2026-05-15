#include "CanIf.h"
#include "CanIf_Cfg.h"
#include "Can.h"
#include "Can_Cfg.h"
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

Std_ReturnType CanIf_SetControllerMode(uint8 ControllerId, Can_ControllerStateType ControllerMode)
{
    return Can_SetControllerMode(ControllerId, ControllerMode);
}

Std_ReturnType CanIf_GetControllerMode(uint8 ControllerId, Can_ControllerStateType *ControllerModePtr)
{
    if (ControllerModePtr == NULL_PTR)
    {
        return E_NOT_OK;
    }
    *ControllerModePtr = Can_ControllerState;
    return E_OK;
}

Std_ReturnType CanIf_GetControllerErrorState(uint8 ControllerId, Can_ErrorStateType *ErrorStatePtr)
{
    return Can_GetControllerErrorState(ControllerId, ErrorStatePtr);
}

void CanIf_SetDynamicTxId(PduIdType CanIfTxSduId, Can_IdType CanId)
{
    for (int i = 0; i < CAN_SERSOR_DATA_LENGTH; i++)
    {
        if (CanIfTxSduId == CanIfGlobalConfigPtr->TxTableConfig[i].TxPduId)
        {
            CanIfGlobalConfigPtr->TxTableConfig[i].TxPduTable->id = CanId;
            break;
        }
    }
}

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
            break;
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
            for (int j = 0; j < PduInfPtr->SduLength; j++)
            {
                CanIfGlobalConfigPtr->RxTableConfig[i].data[j] = PduInfPtr->SduDataPtr[j];
            }
            CanIfGlobalConfigPtr->RxTableConfig[i].Length = PduInfPtr->SduLength;
            PduR_RxIndication(CanIfGlobalConfigPtr->RxTableConfig[i].RxPduId, PduInfPtr);
            break;
        }
    }
}

Std_ReturnType CanIf_ReadRxPduData(PduIdType CanIfRxPduId, PduInfoType *PduInfoPtr)
{
    return 0;
}