#include "Com.h"
#include "Com_Cfg.h"
#include "PduR.h"

uint32 count = 0;

uint8 Com_ReceiveSignal(Com_SignalIdType SignalId, void *SignalDataPtr)
{
    for (int i = 0; i < NUMBER_OF_COM_RX_SIGNAL; i++)
    {
        if (SignalId == ComRxSignalConfig[i].GlobalPduId)
        {
            for (int j = 0; j < ComRxSignalConfig[i].DataLength; j++)
            {
                ((uint8 *)SignalDataPtr)[j] = ComRxSignalConfig[i].SduDataPtr[j];
            }
            return SignalId;
        }
    }
    return SignalId;
}

uint8 Com_SendSignal(Com_SignalIdType SignalId, const void *SignalDataPtr)
{
    PduInfoType PduInfo;
    PduInfo.SduLength = 8;
    for (int i = 0; i < 8; i++)
    {
        if (SignalDataPtr == NULL_PTR)
        {
            break;
        }
        ComTxSignalConfig[SignalId].SduDataPtr[i] = ((uint8 *)SignalDataPtr)[i];
    }
    PduInfo.SduDataPtr = ComTxSignalConfig[SignalId].SduDataPtr;
    PduR_ComTransmit(SignalId, &PduInfo);
    return SignalId;
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

void Dcm_RxIndication(PduIdType PduId, const PduInfoType *PduInfoPtr)
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