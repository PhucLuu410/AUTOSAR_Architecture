#include "CanIf.h"
#include "CanIf_Cfg.h"
#include "CanTp.h"
#include "CanTp_Cfg.h"
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

Std_ReturnType CanIf_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr)
{
    for (int i = 0; i < NUMBER_OF_CAN_IF_TX_PDU; i++)
    {
        if (CanIfGlobalConfigPtr->CanIfTxPduCfgRef[i].CanIfTxPduId == TxPduId)
        {
            Can_HwHandleType Hoh = CanIfGlobalConfigPtr->CanIfTxPduCfgRef[i].CanIfCanHoh;
            Can_PduType PduInfo;
            PduInfo.id = CanIfGlobalConfigPtr->CanIfTxPduCfgRef[i].CanIfTxCanId;
            PduInfo.length = PduInfoPtr->SduLength;
            PduInfo.sdu = PduInfoPtr->SduDataPtr;
            PduInfo.swPduHandle = 0;
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
        if (Mailbox->CanId == CanIfGlobalConfigPtr->CanIfRxPduCfgRef[i].CanIfRxCanId)
        {
            CanIfGlobalConfigPtr->CanIfRxPduCfgRef[i].DestinationFuncPtr(CanIfGlobalConfigPtr->CanIfRxPduCfgRef[i].CanIfRxPduId, PduInfoPtr);
        }
    }
    Det_ReportError(0, 0, 0, 1);
}