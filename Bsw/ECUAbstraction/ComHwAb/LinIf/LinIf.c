#include "LinIf.h"
#include "LinIf_Cfg.h"
#include "stm32f103xb.h"
#include "Std_Types.h"

static const LinIf_ConfigType *LinIf_LocalConfig;
static const LinTp_ConfigType *LinTp_LocalConfig;

void LinIf_Init(const LinIf_ConfigType *ConfigPtr)
{
    LinIf_LocalConfig = ConfigPtr;
}

void LinTp_Init(const LinTp_ConfigType *ConfigPtr)
{
    LinTp_LocalConfig = ConfigPtr;
}

Std_ReturnType LinIf_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr)
{
    if (TxPduId == 2)
    {
        Lin_PduType PduInfo;
        PduInfo.Pid = 0x20;
        PduInfo.Dl = PduInfoPtr->SduLength;
        PduInfo.CsModel = LIN_CLASSIC_CS;
        PduInfo.Response = LIN_FRAMERESPONSE_TX;
        PduInfo.SduDataPtr = PduInfoPtr->SduDataPtr;
        Lin_SendFrame(LIN_CHANNEL_1, &PduInfo);
        return E_OK;
    }
    else if (TxPduId == 3)
    {
        Lin_PduType PduInfo;
        PduInfo.Pid = 0x21;
        PduInfo.Dl = PduInfoPtr->SduLength;
        PduInfo.CsModel = LIN_CLASSIC_CS;
        PduInfo.Response = LIN_FRAMERESPONSE_TX;
        PduInfo.SduDataPtr = PduInfoPtr->SduDataPtr;
        Lin_SendFrame(LIN_CHANNEL_1, &PduInfo);
        return E_OK;
    }
    else
    {
        return E_NOT_OK;
    }
    return E_NOT_OK;
}