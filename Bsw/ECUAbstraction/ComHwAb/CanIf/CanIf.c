#include "CanIf.h"
#include "CanIf_Cfg.h"
#include "Can.h"
#include "Can_Cfg.h"
#include "PduR.h"
#include "Can_GeneralTypes.h"
#include "Det.h"
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
}

Std_ReturnType CanIf_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr)
{
    for (int i = 0; i < NUMBER_OF_CAN_IF_TX_PDU; i++)
    {
        if (CanIfGlobalConfigPtr->CanIfInitConfig.CanIfTxPduCfgRef[i].CanIfTxPduId == TxPduId)
        {
            Can_HwHandleType Hoh = CanIfGlobalConfigPtr->CanIfInitConfig.CanIfTxPduCfgRef[i].CanIfTxPduBufferRef;
            Can_PduType PduInfo;
            PduInfo.id = CanIfGlobalConfigPtr->CanIfInitConfig.CanIfTxPduCfgRef[i].CanIfTxCanId;
            PduInfo.length = PduInfoPtr->SduLength;
            PduInfo.sdu = PduInfoPtr->SduDataPtr;
            PduInfo.swPduHandle = CanIfGlobalConfigPtr->CanIfInitConfig.CanIfTxPduCfgRef[i].CanIfTxPduRef;
            return Can_Write(Hoh, &PduInfo);
        }
    }
    return E_NOT_OK;
}

void CanIf_RxIndication(const Can_HwType *Mailbox, const PduInfoType *PduInfoPtr)
{
    if (CanIfGlobalConfigPtr == NULL_PTR)
    {
        Det_ReportError(0, 0, 0, 1);
        return;
    }
    for (int i = 0; i < NUMBER_OF_CAN_IF_RX_PDU; i++)
    {
        if (CanIfGlobalConfigPtr->CanIfInitConfig.CanIfRxPduCfgRef[i].CanIfRxCanId == Mailbox->CanId &&
            CanIfGlobalConfigPtr->CanIfInitConfig.CanIfRxPduCfgRef[i].CanIfRxPduHrhIdRef == Mailbox->Hoh &&
            CanIfGlobalConfigPtr->CanIfInitConfig.CanIfRxPduCfgRef[i].CanIfRxPduRef == Mailbox->ControllerId)
        {
            PduIdType RxPduId = CanIfGlobalConfigPtr->CanIfInitConfig.CanIfRxPduCfgRef[i].CanIfRxPduId;
            if (CanIfGlobalConfigPtr->CanIfInitConfig.CanIfRxPduCfgRef[i].TargetPduIdDestination == 0)
            {
                CanTp_RxIndication(RxPduId, PduInfoPtr);
                return;
            }
            else if (CanIfGlobalConfigPtr->CanIfInitConfig.CanIfRxPduCfgRef[i].TargetPduIdDestination == 1)
            {
                PduR_RxIndication(RxPduId, PduInfoPtr);
            }
            return;
        }
    }
    Det_ReportError(0, 0, 0, 1);
}