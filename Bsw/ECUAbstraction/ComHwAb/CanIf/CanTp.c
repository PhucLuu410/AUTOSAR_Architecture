#include "CanTp.h"
#include "CanIf.h"
#include "CanIf_Cfg.h"
#include "Can.h"
#include "Can_Cfg.h"
#include "PduR.h"

Std_ReturnType CanTp_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr)
{
    uint8 CanTp_FF[8] = {0x10, PduInfoPtr->SduLength, *PduInfoPtr->SduDataPtr,
                         *(PduInfoPtr->SduDataPtr + 1),
                         *(PduInfoPtr->SduDataPtr + 2),
                         *(PduInfoPtr->SduDataPtr + 3),
                         *(PduInfoPtr->SduDataPtr + 4),
                         *(PduInfoPtr->SduDataPtr + 5)};

    PduInfoType FF = {.SduDataPtr = CanTp_FF, .SduLength = 8};
    CanIf_Transmit(TxPduId, &FF);
    return E_OK;
}

void CanTp_RxIndication(PduIdType PduId, const PduInfoType *PduInfoPtr)
{
    static uint8 data[20] = {0};
    static uint8 count = 0;
    uint8 *pduData = PduInfoPtr->SduDataPtr;
    uint8 frameType = pduData[0];
    switch (frameType)
    {
    case 0x01:
        if (count < 20)
        {
            for (int i = 0; i < 7; i++)
            {
                data[count++] = *(++pduData);
            }
        }
        if (count >= 20)
        {
            PduInfoType pduInfo;
            pduInfo.SduDataPtr = data;
            pduInfo.SduLength = 20;
            PduR_RxIndication(3, &pduInfo);
        }
        break;
    }
}