#include "PduR.h"
#include "PduR_Cfg.h"
#include "Com.h"
static const PduR_PBConfigType *PduR_ConfigPtr = NULL_PTR;

uint8 PduR_Buffer[8] = {0};
uint8 PduR_BufferLength = 0;
uint32 id = 0;
uint8 TxResult = 10;

void PduR_Init(const PduR_PBConfigType *ConfigPtr)
{
    PduR_ConfigPtr = ConfigPtr;
}

void PduR_RxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
    PduR_ConfigPtr->RxRoutingTable[RxPduId].Rx_Func(RxPduId, PduInfoPtr);
}

Std_ReturnType PduR_ComTransmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr)
{
    return PduR_ConfigPtr->TxRoutingTable[TxPduId].Transmit_Func(TxPduId, PduInfoPtr);
}

void PduR_CanIfTxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
    if (TxResult == 10)
    {
        TxResult = result;
        TxResult = 10;
    }
}