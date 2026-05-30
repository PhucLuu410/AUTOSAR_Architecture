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
    for (int i = 0; i < SIZE_OF_CAN_IF_TABLE; i++)
    {
        if (CanIfGlobalConfigPtr->TxTableConfig[i].CanIf_LocalId == CanTxPduId)
        {
            PduR_CanIfTxConfirmation(CanTxPduId, E_OK);
            break;
        }
    }
}

// Std_ReturnType CanIf_SetControllerMode(uint8 ControllerId, Can_ControllerStateType ControllerMode)
// {
//     return Can_SetControllerMode(ControllerId, ControllerMode);
// }

Std_ReturnType CanIf_GetControllerMode(uint8 ControllerId, Can_ControllerStateType *ControllerModePtr)
{
    if (ControllerModePtr == NULL_PTR)
    {
        return E_NOT_OK;
    }
    *ControllerModePtr = Can_ControllerState[ControllerId];
    return E_OK;
}

Std_ReturnType CanIf_GetControllerErrorState(uint8 ControllerId, Can_ErrorStateType *ErrorStatePtr)
{
    // return Can_GetControllerErrorState(ControllerId, ErrorStatePtr);
    return 0;
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
            CanPdu.swPduHandle = TxPduId;
            CanPdu.id = CanIfGlobalConfigPtr->TxTableConfig[i].CanIf_CanId;
            CanPdu.length = PduInfoType->SduLength;
            CanPdu.sdu = PduInfoType->SduDataPtr;
            return Can_Write(CanIf_TxTable[i].Hoh, &CanPdu);
        }
    }
    return E_NOT_OK;
}

void CanIf_RxIndication(const Can_HwType *Mailbox, const PduInfoType *PduInfoPtr)
{
    for (int i = 0; i < SIZE_OF_CAN_IF_TABLE; i++)
    {
        if (Mailbox->CanId == CanIfGlobalConfigPtr->RxTableConfig[i].CanIf_CanId)
        {
            PduR_RxIndication(CanIfGlobalConfigPtr->RxTableConfig[i].CanIf_LocalId, PduInfoPtr);
            break;
        }
    }
}

Std_ReturnType CanIf_ReadRxPduData(PduIdType CanIfRxPduId, PduInfoType *PduInfoPtr)
{
    for (int i = 0; i < SIZE_OF_CAN_IF_TABLE; i++)
    {
        if (CanIfGlobalConfigPtr->RxTableConfig[i].CanIf_LocalId == CanIfRxPduId)
        {
            PduInfoPtr->SduLength = CanIfGlobalConfigPtr->RxTableConfig[i].Length;
            PduInfoPtr->SduDataPtr = CanIfGlobalConfigPtr->RxTableConfig[i].data;
            return E_OK;
        }
    }
    return E_NOT_OK;
}