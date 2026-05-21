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

// void CanIf_SetDynamicTxId(PduIdType CanIfTxSduId, Can_IdType CanId)
// {
//     for (int i = 0; i < CAN_SERSOR_DATA_LENGTH; i++)
//     {
//         if (CanIfTxSduId == CanIfGlobalConfigPtr->TxTableConfig[i].CanIf_LocalId)
//         {
//             CanIfGlobalConfigPtr->TxTableConfig[i].TxPduTable->id = CanId;
//             break;
//         }
//     }
// }

Std_ReturnType CanIf_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoType)
{
    for (int i = 0; i < SIZE_OF_CAN_IF_TABLE; i++)
    {
        if (CanIfGlobalConfigPtr->TxTableConfig[i].CanIf_LocalId == TxPduId)
        {
            Can_PduType CanPdu;
            CanPdu.swPduHandle = CanIfGlobalConfigPtr->TxTableConfig[i].CanChannel;
            CanPdu.id = CanIfGlobalConfigPtr->TxTableConfig[i].CanIf_CanId;
            CanPdu.length = PduInfoType->SduLength;
            CanPdu.sdu = PduInfoType->SduDataPtr;
            return Can_Write(CanPdu.swPduHandle, &CanPdu);
        }
    }
    return E_NOT_OK;
}

void CanIf_RxIndication(const Can_HwType *Mailbox, const PduInfoType *PduInfPtr)
{
    for (int i = 0; i < SIZE_OF_CAN_IF_TABLE; i++)
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