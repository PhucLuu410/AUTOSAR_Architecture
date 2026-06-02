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
    for (int i = 0; i < SIZE_OF_LIN_IF_RX_TABLE; i++)
    {
        if (LinIf_RxTable[i].LinIf_LinId == Lin_SduPtr[0] && LinIf_RxTable[i].Lin_Channel == Channel)
        {
            PduInfoType LinPdu;
            LinPdu.SduLength = Lin_SduPtr[1];
            uint8 DataBuffer[LinPdu.SduLength];
            for (int i = 0; i < LinPdu.SduLength; i++)
            {
                DataBuffer[i] = Lin_SduPtr[4 + i];
            }
            LinPdu.SduDataPtr = DataBuffer;
            PduR_RxIndication(LinIf_RxTable[i].LinIf_LocalId, &LinPdu);
            break;
        }
    }
}
