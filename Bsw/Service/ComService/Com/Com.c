#include "Com.h"
#include "Com_Cfg.h"

uint32 count = 0;
Std_ReturnType Com_SendSignal(PduIdType PduId)
{
    for (int i = 0; i < NUMBER_OF_COM_TX_SIGNAL; i++)
    {
        if (PduId == ComTxSignalConfig[i].GlobalPduId)
        {
            PduInfoType PduInfo;
            PduInfo.SduLength = ComTxSignalConfig[i].DataLength;
            PduInfo.SduDataPtr = ComTxSignalConfig[i].SduDataPtr;
            // return PduR_Transmit(ComTxSignalConfig[i].GlobalPduId, &PduInfo);
        }
    }
    return E_NOT_OK;
}

void Com_RxIndication(PduIdType PduId, const PduInfoType *PduInfoPtr)
{
    for (int i = 0; i < NUMBER_OF_COM_RX_SIGNAL; i++)
    {
        if (PduId == ComRxSignalConfig[i].GlobalPduId)
        {
            for (int j = 0; j < PduInfoPtr->SduLength; j++)
            {
                ComRxSignalConfig[i].SduDataPtr[j] = PduInfoPtr->SduDataPtr[j];
            }
            ComRxSignalConfig[i].DataLength = PduInfoPtr->SduLength;
            break;
        }
    }
}