#include "LinIf.h"
#include "LinIf_Cfg.h"
#include "Lin.h"
#include "PduR.h"
#include "string.h"
static const LinIf_ConfigType *LocalLinIfConfig;

void LinIf_Init(const LinIf_ConfigType *ConfigPtr)
{
    LocalLinIfConfig = ConfigPtr;
}

Std_ReturnType LinIf_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr)
{
    for (int i = 0; i < SIZE_OF_LIN_IF_TX_TABLE; i++)
    {
        if (LinIf_TxTable[i].LinIf_LocalId == TxPduId)
        {
            Lin_PduType LinPdu;
            LinPdu.Pid = LinIf_TxTable[i].LinIf_LinId;
            LinPdu.Dl = PduInfoPtr->SduLength;
            LinPdu.CsModel = LIN_ENHANCED_CS;
            LinPdu.Response = LIN_FRAMERESPONSE_TX;
            LinPdu.SduDataPtr = PduInfoPtr->SduDataPtr;
            return Lin_SendFrame(LinIf_TxTable[i].LinChannel, &LinPdu);
        }
    }
    return E_NOT_OK;
}

void LinIf_RxIndication(NetworkHandleType Channel, uint8 *Lin_SduPtr)
{
    static uint8 SyncFlag = 0;
    static uint8 Index = 0;
    static uint8 CurrentLinLocalId = 0;
    static uint8 LinData[16] = {0};
    if (*Lin_SduPtr == 0x55 && SyncFlag == 0)
    {
        SyncFlag = 1;
        Index = 0;
        return;
    }
    for (int i = 0; i < SIZE_OF_LIN_IF_RX_TABLE; i++)
    {
        if (LinIf_RxTable[i].LinIf_LinId == *Lin_SduPtr)
        {
            CurrentLinLocalId = LinIf_RxTable[i].LinIf_LocalId;
            return;
        }
    }
    if (SyncFlag == 1 && Index <= LinIf_RxTable[CurrentLinLocalId].LinIf_DataLength)
    {
        LinData[Index++] = *Lin_SduPtr;
    }
    else
    {
        SyncFlag = 0;
        PduInfoType LinDataPdu;
        LinDataPdu.SduDataPtr = LinData;
        LinDataPdu.SduLength = LinIf_RxTable[CurrentLinLocalId].LinIf_DataLength;
        PduR_RxIndication(CurrentLinLocalId, &LinDataPdu);
    }
}
