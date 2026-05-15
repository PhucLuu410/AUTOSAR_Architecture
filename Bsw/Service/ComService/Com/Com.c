#include "Com.h"
#include "Com_Cfg.h"

Std_ReturnType Com_SendSignal(PduIdType PduId)
{
    for (int i = 0; i < 3; i++)
    {
        if (PduId == ComTxSignalConfig[i].PduId)
        {
            PduInfoType PduInfo;
            PduInfo.SduLength = ComTxSignalConfig[i].DataLength;
            PduInfo.SduDataPtr = ComTxSignalConfig[i].SduDataPtr;
            return PduR_ComTransmit(PduId, &PduInfo);
        }
    }
    return E_NOT_OK;
}

void Com_RxIndication(PduIdType PduId, const PduInfoType *PduInfoPtr)
{
    for (int i = 0; i < 4; i++)
    {
        if (PduId == ComRxSignalConfig[i].PduId)
        {
            for (int j = 0; j < PduInfoPtr->SduLength; j++)
            {
                ComRxSignalConfig[i].SduDataPtr[j] = PduInfoPtr->SduDataPtr[j];
            }
            ComRxSignalConfig[i].DataLength = PduInfoPtr->SduLength;
        }
    }
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