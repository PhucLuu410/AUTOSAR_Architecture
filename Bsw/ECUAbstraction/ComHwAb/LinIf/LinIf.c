#include "LinIf.h"
#include "LinIf_Cfg.h"
#include "stm32f103xb.h"

const LinIf_ConfigType *LinIf_Local_Config;

void LinIf_Init(const LinIf_ConfigType *ConfigPtr)
{
    if (ConfigPtr == NULL_PTR)
    {
        return;
    }
    LinIf_Local_Config = ConfigPtr;
}

Std_ReturnType LinIf_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr)
{
    if (LinIf_Local_Config == NULL_PTR)
    {
        return E_NOT_OK;
    }
    if (TxPduId >= NUMBER_OF_LINIF_FRAME)
    {
        return E_NOT_OK;
    }
    if (PduInfoPtr == NULL_PTR)
    {
        return E_NOT_OK;
    }

    for (int ChannelNumber = 0; ChannelNumber < NUMBER_OF_LIN_CHANNEL; ChannelNumber++)
    {
        for (int FrameNumber = 0; FrameNumber < NUMBER_OF_LINIF_FRAME; FrameNumber++)
        {
            if (LinIf_Local_Config->LinIfGlobalCfg.LinIfChannelCfg[ChannelNumber].LinIfFrameCfg[FrameNumber].LinIfFrameIndex == TxPduId)
            {
                Lin_PduType LinPdu;
                LinPdu.Pid = LinIf_Local_Config->LinIfGlobalCfg.LinIfChannelCfg[ChannelNumber].LinIfFrameCfg[FrameNumber].LinIfFrameId;
                LinPdu.Dl = PduInfoPtr->SduLength;
                LinPdu.CsModel = LinIf_Local_Config->LinIfGlobalCfg.LinIfChannelCfg[ChannelNumber].LinIfFrameCfg[FrameNumber].LinIfChecksum;
                switch (LinIf_Local_Config->LinIfGlobalCfg.LinIfChannelCfg[ChannelNumber].LinIfFrameCfg[FrameNumber].LinIfFrame)
                {
                case UNCONDITIONAL:
                    LinPdu.Response = LIN_FRAMERESPONSE_RX;
                    break;
                case EVENT_TRIGGERED:
                    LinPdu.Response = LIN_FRAMERESPONSE_RX;
                    break;
                case MRF:
                    LinPdu.Response = LIN_FRAMERESPONSE_TX;
                    break;
                case SRF:
                    LinPdu.Response = LIN_FRAMERESPONSE_TX;
                    break;
                default:
                    LinPdu.Response = LIN_FRAMERESPONSE_IGNORE;
                    break;
                }
                LinPdu.SduDataPtr = PduInfoPtr->SduDataPtr;
                return Lin_SendFrame(LinIf_Local_Config->LinIfGlobalCfg.LinIfChannelCfg[ChannelNumber].LinIfChannelRef, &LinPdu);
            }
        }
    }
    return E_NOT_OK;
}

void LinIf_RxIndication(NetworkHandleType Channel, uint8 *Lin_SduPtr)
{
}