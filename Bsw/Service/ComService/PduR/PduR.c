#include "PduR.h"
#include "PduR_Cfg.h"
#include "Com.h"
static const PduR_PBConfigType *PduR_ConfigPtr = NULL_PTR;

uint8 PduR_Buffer[8] = {0};
uint8 PduR_BufferLength = 0;
uint32 id = 0;

void PduR_Init(const PduR_PBConfigType *ConfigPtr)
{
    PduR_ConfigPtr = ConfigPtr;
}

void PduR_RxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
    for (int i = 0; i < NUMBER_OF_COM_RX_SIGNAL; i++)
    {
        if (PduR_ConfigPtr->RxRoutingTable[i].LocalPduId == RxPduId)
        {
            PduR_ConfigPtr->RxRoutingTable[i].Rx_Func(PduR_ConfigPtr->RxRoutingTable[i].GlobalPduId, PduInfoPtr);
            break;
        }
    }
}

Std_ReturnType PduR_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr)
{
    for (int i = 0; i < NUMBER_OF_COM_TX_SIGNAL; i++)
    {
        if (PduR_ConfigPtr->TxRoutingTable[i].GlobalPduId == TxPduId)
        {
            return PduR_ConfigPtr->TxRoutingTable[i].Transmit_Func(PduR_ConfigPtr->TxRoutingTable[i].LocalPduId, PduInfoPtr);
        }
    }
    return E_NOT_OK;
}

void PduR_CanIfTxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
    if (TxPduId == 0 && result == E_OK)
    {
    }
    if (TxPduId == 1 && result == E_OK)
    {
    }
}