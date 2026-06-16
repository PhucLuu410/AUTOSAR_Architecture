#include "CanTp.h"
#include "CanTp_Cfg.h"
#include "CanIf.h"
#include "Det.h"

static const CanTp_ConfigType *CanTpLocalConfig = NULL_PTR;

static uint16 CanTpDataLength = 0;
static uint16 CanTpIndex = 0;
static uint8 CanTpBuffer[64] = {0};
static uint8 CanTpCurrentTx = 0;

void CanTp_Init(const CanTp_ConfigType *CfgPtr)
{
    if (CfgPtr == NULL_PTR)
    {
        Det_ReportError(0, 0, 0, 0);
    }
    CanTpLocalConfig = CfgPtr;
    for (int i = 0; i < NUMBER_OF_CANTP_TX; i++)
    {
        CanTp_State.TxState[i] = TX_IDLE;
    }
    for (int i = 0; i < NUMBER_OF_CANTP_RX; i++)
    {
        CanTp_State.RxState[i] = RX_IDLE;
    }
}

void CanTp_Shutdown(void)
{
    CanTpLocalConfig = NULL_PTR;
}

Std_ReturnType CanTp_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr)
{
    for (int i = 0; i < NUMBER_OF_CANTP_TX; i++)
    {
        if (CanTpLocalConfig->CanTpTxPduCfg[i].CanTpTxPduId == TxPduId && CanTp_State.TxState[i] == TX_IDLE)
        {
            CanTpDataLength = PduInfoPtr->SduLength;
            if (CanTpDataLength < 7)
            {
                CanTp_State.TxState[i] = TX_SEND_SF;
                uint8 Data2CanIf[8] = {0};
                Data2CanIf[0] = (0x00 | (CanTpDataLength & 0x0F));
                PduInfoType PduInfo;
                PduInfo.SduLength = 8;
                for (int Data = 0; Data < CanTpDataLength; Data++)
                {
                    Data2CanIf[Data + 1] = PduInfoPtr->SduDataPtr[Data];
                }
                PduInfo.SduDataPtr = Data2CanIf;
                CanTp_State.TxState[i] = TX_IDLE;
                CanTpCurrentTx = i;
                return CanIf_Transmit(CanTpLocalConfig->CanTpTxPduCfg[i].CanIfTxPduId, &PduInfo);
            }
        }
    }
    Det_ReportError(0, 0, 0, 0);
    return E_NOT_OK;
}

void CanTp_RxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
    for (int i = 0; i < NUMBER_OF_CANTP_TX; i++)
    {
        if (CanTpLocalConfig->CanTpRxPduCfg[i].CanTpRxPduId == RxPduId && (PduInfoPtr->SduDataPtr[0] & 0xF0) == 0x00 && CanTp_State.RxState[i] == RX_IDLE)
        {
            CanTpDataLength = PduInfoPtr->SduDataPtr[0] & 0x0F;
            uint8 Data2PduR[CanTpDataLength];
            PduInfoType PduInfo;
            PduInfo.SduLength = CanTpDataLength;
            for (int Data = 0; Data < CanTpDataLength; Data++)
            {
                Data2PduR[Data] = PduInfoPtr->SduDataPtr[Data + 1];
            }
            PduInfo.SduDataPtr = Data2PduR;
            CanTp_State.TxState[i] = TX_IDLE;
            CanTp_State.RxState[i] = RX_IDLE;
            PduR_CanTpRxIndication(CanTpLocalConfig->CanTpRxPduCfg[i].PduRRxPduId, &PduInfo);
        }

        if (CanTpLocalConfig->CanTpRxPduCfg[i].CanTpRxPduId == RxPduId && (PduInfoPtr->SduDataPtr[0] & 0xF0) == 0x10 && CanTp_State.RxState[i] == RX_IDLE)
        {
            CanTp_State.RxState[i] = RX_SEND_FC;
            CanTpDataLength = (((PduInfoPtr->SduDataPtr[0] & 0x0F) << 8) | (PduInfoPtr->SduDataPtr[1]));
            for (int Data = 2; Data < 8; Data++)
            {
                CanTpBuffer[CanTpIndex++] = PduInfoPtr->SduDataPtr[Data];
            }
        }

        if (CanTpLocalConfig->CanTpRxPduCfg[i].CanTpRxPduId == RxPduId && (PduInfoPtr->SduDataPtr[0] & 0xF0) == 0x20 && CanTp_State.RxState[i] == RX_RECEIVE_CF)
        {
            for (int Data = 1; Data < 8; Data++)
            {
                CanTpBuffer[CanTpIndex++] = PduInfoPtr->SduDataPtr[Data];
                if (CanTpIndex >= CanTpDataLength)
                {
                    CanTp_State.TxState[i] = TX_IDLE;
                    CanTp_State.RxState[i] = RX_IDLE;
                    CanTpIndex = 0;
                    PduInfoType PduInfo;
                    PduInfo.SduLength = CanTpDataLength;
                    PduInfo.SduDataPtr = CanTpBuffer;
                    PduR_CanTpRxIndication(CanTpLocalConfig->CanTpRxPduCfg[i].PduRRxPduId, &PduInfo);
                }
            }
        }

        if (CanTp_State.RxState[i] == RX_SEND_FC)
        {
            uint8 Data2CanIf[8] = {0};
            Data2CanIf[0] = 0x30;
            PduInfoType PduInfo;
            PduInfo.SduLength = 8;
            PduInfo.SduDataPtr = Data2CanIf;
            CanTp_State.RxState[i] = RX_RECEIVE_CF;
            CanIf_Transmit(CanTpLocalConfig->CanTpRxPduCfg[i].CanIfTxPduId, &PduInfo);
        }
    }
}
