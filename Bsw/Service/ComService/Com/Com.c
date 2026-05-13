#include "Com.h"

uint8 Com_Buffer[4][20] = {0};

void Com_RxIndication(PduIdType PduId, const PduInfoType *PduInfoPtr)
{
    uint8 length = PduInfoPtr->SduLength;
    for (int i = 0; i < length; i++)
    {
        Com_Buffer[PduId][i] = PduInfoPtr->SduDataPtr[i];
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