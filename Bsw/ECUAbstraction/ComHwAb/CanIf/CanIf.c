#include "CanIf.h"
#include "CanIf_Cfg.h"
#include "Can.h"
#include "Can_GeneralTypes.h"

static const CanIf_ConfigType *CanIf_GlobalConfigPtr = NULL_PTR;

void CanIf_Init(const CanIf_ConfigType *ConfigPtr)
{
    CanIf_GlobalConfigPtr = ConfigPtr;
}

Std_ReturnType CanIf_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr)
{
    CanIf_GlobalConfigPtr->TxPduConfig->TxPduType[TxPduId].sdu = PduInfoPtr->SduDataPtr;
    CanIf_GlobalConfigPtr->TxPduConfig->TxPduType[TxPduId].length = PduInfoPtr->SduLength;
    return Can_Write(0, &CanIf_GlobalConfigPtr->TxPduConfig->TxPduType[TxPduId]);
}

void CanIf_RxIndication(const Can_HwType *Mailbox, const PduInfoType *PduInfPtr)
{
    for (uint8 i = 0; i < 3; i++)
    {
        if (Mailbox->CanId == CanIf_GlobalConfigPtr->RxPduConfig->RxPduType[i].id)
        {
            for (uint8 byteIdx = 0; byteIdx < PduInfPtr->SduLength; byteIdx++)
            {
                CanIf_GlobalConfigPtr->RxPduConfig->RxPduType[i].sdu[byteIdx] = PduInfPtr->SduDataPtr[byteIdx];
            }
            break;
        }
    }
}

Std_ReturnType CanIf_ReadRxPduData(PduIdType CanIfRxPduId, PduInfoType *PduInfoPtr)
{
}