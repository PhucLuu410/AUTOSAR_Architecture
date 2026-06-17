#include "CanTp.h"
#include "CanTp_Cfg.h"
#include "CanIf.h"
#include "Det.h"

static const CanTp_ConfigType *CanTpLocalConfig = NULL_PTR;

static uint16 CanTpRxDataLength = 0;
static uint16 CanTpIndex = 0;
static uint8 CanTpBuffer[64] = {0};

void CanTp_Init(const CanTp_ConfigType *CfgPtr)
{
    if (CfgPtr == NULL_PTR)
    {
        Det_ReportError(0, 0, 0, 0);
    }
    CanTpLocalConfig = CfgPtr;
    for (int i = 0; i < NUMBER_OF_CANTP; i++)
    {
        CanTp_TxState[i] = TX_IDLE;
        CanTp_RxState[i] = RX_IDLE;
    }
}

void CanTp_Shutdown(void)
{
    CanTpLocalConfig = NULL_PTR;
}

Std_ReturnType CanTp_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr)
{
    for (int i = 0; i < NUMBER_OF_CANTP; i++)
    {
        if (CanTpLocalConfig->CanTpTxPduCfg[i].CanTpTxPduId == TxPduId)
        {
            if (CanTp_TxState[i] == TX_IDLE)
            {
                if (PduInfoPtr->SduLength < 8)
                {
                    CanTp_TxState[i] = SEND_SF;
                    uint8 CanTpData[8] = {0};
                    CanTpData[0] = (0x00 | PduInfoPtr->SduLength);
                    PduInfoType CanTpPduInfo;
                    for (int DataIndex = 0; DataIndex < PduInfoPtr->SduLength; DataIndex++)
                    {
                        CanTpData[DataIndex + 1] = PduInfoPtr->SduDataPtr[DataIndex];
                    }
                    CanTpPduInfo.SduDataPtr = CanTpData;
                    CanTpPduInfo.SduLength = 8;
                    CanIf_Transmit(CanTpLocalConfig->CanTpTxPduCfg[i].CanIfTxPduId, &CanTpPduInfo);
                }
                else
                {
                    CanTp_TxState[i] = SEND_FF;

                    CanTp_TxState[i] = WAIT_FC;
                }
            }
        }
    }
    return E_OK;
}

void CanTp_RxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
    for (int i = 0; i < NUMBER_OF_CANTP; i++)
    {
        if (CanTpLocalConfig->CanTpRxPduCfg[i].CanTpRxPduId == RxPduId)
        {
            if ((PduInfoPtr->SduDataPtr[0] & 0xF0) == 0x00 && CanTp_RxState[i] == RX_IDLE)
            {
                CanTp_RxState[i] = RECEIVE_SF;
                PduInfoType CanTpPduInfo;
                uint8 CanTpData[8] = {0};
                for (int DataIndex = 0; DataIndex < (PduInfoPtr->SduDataPtr[0] & 0x0F); DataIndex++)
                {
                    CanTpData[DataIndex] = PduInfoPtr->SduDataPtr[DataIndex + 1];
                }
                CanTpPduInfo.SduDataPtr = CanTpData;
                CanTpPduInfo.SduLength = PduInfoPtr->SduDataPtr[0] & 0x0F;
                PduR_CanTpRxIndication(CanTpLocalConfig->CanTpRxPduCfg[i].PduRRxPduId, &CanTpPduInfo);
                CanTp_RxState[i] = RX_IDLE;
                CanTp_TxState[i] = TX_IDLE;
            }

            if ((PduInfoPtr->SduDataPtr[0] & 0xF0) == 0x10 && CanTp_RxState[i] == RX_IDLE)
            {
                CanTp_RxState[i] = RECEIVE_FF;
                CanTpRxDataLength = ((PduInfoPtr->SduDataPtr[0] & 0x0F) << 8 | PduInfoPtr->SduDataPtr[1]);
                for (int DataIndex = 0; DataIndex < 6; DataIndex++)
                {
                    CanTpBuffer[CanTpIndex++] = PduInfoPtr->SduDataPtr[DataIndex + 2];
                }
                CanTp_RxState[i] = SEND_FC;
            }

            if ((PduInfoPtr->SduDataPtr[0] & 0xF0) == 0x20 && CanTp_RxState[i] == RECEIVE_CF)
            {
                for (int DataIndex = 0; DataIndex < 7; DataIndex++)
                {
<<<<<<< HEAD
                    CanTpLocalConfig->CanTpCfg->CanTpChannelCfg->CanTpRxNSduCfg->CanTpRxNPduRefCfg->CanTpRxNPduRef[Index++] = PduInfoPtr->SduDataPtr[j + 1];
                }
                Bs--;
                if (Bs == 0)
                {
                    Bs = BS;
                    CanTp_RxState = CANTP_RX_SEND_FC;
                }
            }

            if (CanTp_RxState == CANTP_RX_SEND_FC)
            {
                if (Index >= Length)
                {
                    Index = 0;
                    Count = 1;
                    PduInfoType PduInfoToPduR;
                    PduInfoToPduR.SduLength = Length;
                    PduInfoToPduR.SduDataPtr = CanTpLocalConfig->CanTpCfg->CanTpChannelCfg->CanTpRxNSduCfg->CanTpRxNPduRefCfg->CanTpRxNPduRef;
                    (void)PduInfoToPduR;
                    PduR_CanTpRxIndication(CanTpLocalConfig->CanTpCfg->CanTpChannelCfg->CanTpRxNSduCfg->CanTpRxNSduIdCfg, &PduInfoToPduR);
                }
                uint8 TxBuffer[8] = {0};
                TxBuffer[0] = 0x30;
                TxBuffer[1] = BS;
                TxBuffer[2] = STmin;
                PduInfoType PduInfo;
                PduInfo.SduLength = 8;
                PduInfo.SduDataPtr = TxBuffer;
                CanTp_RxState = CANTP_RX_IDLE;
                CanTp_RxSubStateMachine = CANTP_RX_WAIT;
                CanIf_Transmit(CanTpLocalConfig->CanTpCfg->CanTpChannelCfg->CanTpTxNSduCfg->CanTpTxNPduRefCfg->CanTpTxNPduConfirmationPduId, &PduInfo);
            }
            return;
        }
    }

#endif

#ifdef MASTER
    if (CanTp_TxSubStateMachine != CANTP_TX_PROCESSING)
    {
        Det_ReportError(0, 0, 0, 0);
        return;
    }
    for (int i = 0; i < NUMBER_OF_CAN_TP_TX_NSDU; i++)
    {
        if (CanTpLocalConfig->CanTpCfg->CanTpChannelCfg->CanTpTxNSduCfg->CanTpTxNPduRefCfg->CanTpTxNPduConfirmationPduId == RxPduId)
        {
            // Doi FC phan hoi FF
            if (CanTp_TxState == CANTP_TX_WAIT_FC)
            {
                if (PduInfoPtr->SduDataPtr[0] == 0x30)
                {
                    Bs = PduInfoPtr->SduDataPtr[1];
                    StMin = PduInfoPtr->SduDataPtr[2];
                    CanTp_TxState = CANTP_TX_SEND_CF;
                }
            }

            // Gui CF
            if (CanTp_TxState == CANTP_TX_SEND_CF)
            {
                for (int k = 0; k < 2; k++)
                {
                    static PduInfoType PduInfo;
                    static uint8 TxBuffer[8] = {0};
                    TxBuffer[0] = (0x20 | (Count & 0x0F));
                    for (int j = 0; j < 7; j++)
                        == == == =
                                     CanTpBuffer[CanTpIndex++] = PduInfoPtr->SduDataPtr[DataIndex + 1];
                    if (CanTpIndex >= CanTpRxDataLength)
>>>>>>> develop
                    {
                        PduInfoType CanTpPduInfo;
                        CanTpPduInfo.SduDataPtr = CanTpBuffer;
                        CanTpPduInfo.SduLength = CanTpRxDataLength;
                        PduR_CanTpRxIndication(CanTpLocalConfig->CanTpRxPduCfg[i].PduRRxPduId, &CanTpPduInfo);
                        CanTpIndex = 0;
                        CanTpRxDataLength = 0;
                        CanTp_RxState[i] = RX_IDLE;
                        CanTp_TxState[i] = TX_IDLE;
                        return;
                    }
                }
                CanTp_RxState[i] = SEND_FC;
            }

            if (CanTp_RxState[i] == SEND_FC)
            {
                uint8 CanTpData[8] = {0};
                PduInfoType CanTpPduInfo;
                CanTpData[0] = 0x30;
                CanTpData[1] = 0x01;
                CanTpPduInfo.SduDataPtr = CanTpData;
                CanTpPduInfo.SduLength = 8;
                CanIf_Transmit(CanTpLocalConfig->CanTpRxPduCfg[i].CanIfTxRespondPduId, &CanTpPduInfo);
                CanTp_RxState[i] = RECEIVE_CF;
            }
        }
    }
}
