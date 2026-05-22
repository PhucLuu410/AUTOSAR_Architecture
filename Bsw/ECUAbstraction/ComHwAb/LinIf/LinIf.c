#include "LinIf.h"
#include "LinIf_Cfg.h"
#include "Lin.h"

static const LinIf_ConfigType *LocalLinIfConfig;

void LinIf_Init(const LinIf_ConfigType *ConfigPtr)
{
    LocalLinIfConfig = ConfigPtr;
}

Std_ReturnType LinIf_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr)
{
    for (int i = 0; i < SIZE_OF_LIN_IF_TABLE; i++)
    {
        if (LinIf_PduTable[i].LinIf_LocalId == TxPduId)
        {
            Lin_PduType LinPdu;
            LinPdu.Pid = LinIf_PduTable[i].LinIf_LinId;
            LinPdu.Dl = PduInfoPtr->SduLength;
            LinPdu.CsModel = LIN_ENHANCED_CS;
            LinPdu.Response = LIN_FRAMERESPONSE_TX;
            LinPdu.SduDataPtr = PduInfoPtr->SduDataPtr;
            return Lin_SendFrame(LinIf_PduTable[i].LinChannel, &LinPdu);
        }
    }
    return E_NOT_OK;
}