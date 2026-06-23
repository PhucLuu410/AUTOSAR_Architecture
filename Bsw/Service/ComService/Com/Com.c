#include "Com.h"
#include "Com_Cfg.h"
#include "PduR.h"

uint32 count = 0;

// Std_ReturnType Com_SendSignal(PduIdType PduId)
// {
//     for (int i = 0; i < NUMBER_OF_COM_TX_SIGNAL; i++)
//     {
//         if (PduId == ComTxSignalConfig[i].GlobalPduId)
//         {
//             PduInfoType PduInfo;
//             PduInfo.SduLength = ComTxSignalConfig[i].DataLength;
//             PduInfo.SduDataPtr = ComTxSignalConfig[i].SduDataPtr;
//             return PduR_ComTransmit(ComTxSignalConfig[i].GlobalPduId, &PduInfo);
//         }
//     }
//     return E_NOT_OK;
// }

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
    PduInfo.SduDataPtr = (uint8 *)SignalDataPtr;
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