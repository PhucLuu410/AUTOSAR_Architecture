#include "CanTp.h"
#include "CanTp_Cfg.h"
#include "CanIf.h"
#include "Det.h"

static CanTp_InitAndShutdownStateMachineType CanTp_InitAndShutdownStateMachine = CANTP_OFF;
static CanTp_TxSubStateMachineType CanTp_TxSubStateMachine = CANTP_TX_WAIT;
static CanTp_RxSubStateMachineType CanTp_RxSubStateMachine = CANTP_RX_WAIT;
static CanTp_BufferStateMachineType CanTp_BufferStateMachine = CANTP_BUFFER_UNLOCK;
static CanTp_TxStateMachine CanTp_TxState = CANTP_TX_IDLE;
static CanTp_RxStateMachine CanTp_RxState = CANTP_RX_IDLE;
static const CanTp_ConfigType *CanTpLocalConfig;

// // Master
// volatile uint8 Index = 0;
// volatile uint8 Count = 1;

// Slave
volatile uint8 Index = 0;
volatile uint8 Count = 1;

void CanTp_Init(const CanTp_ConfigType *CfgPtr)
{
    if (CfgPtr == NULL_PTR)
    {
        CanTp_InitAndShutdownStateMachine = CANTP_OFF;
        Det_ReportError(0, 0, 0, 0);
    }
    CanTpLocalConfig = CfgPtr;
    CanTp_InitAndShutdownStateMachine = CANTP_ON;
}

void CanTp_Shutdown(void)
{
    CanTp_InitAndShutdownStateMachine = CANTP_OFF;
}

Std_ReturnType CanTp_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr)
{
    if (CanTp_InitAndShutdownStateMachine == CANTP_OFF)
    {
        Det_ReportError(0, 0, 0, 0);
        return E_NOT_OK;
    }
    if (CanTp_TxSubStateMachine == CANTP_TX_WAIT)
    {
        CanTp_TxSubStateMachine = CANTP_TX_PROCESSING;
    }
    else
    {
        Det_ReportError(0, 0, 0, 0);
        return E_NOT_OK;
    }

    for (int i = 0; i < NUMBER_OF_CAN_TP_TX_NSDU; i++)
    {

        if (CanTpLocalConfig->CanTpCfg->CanTpChannelCfg->CanTpTxNSduCfg->CanTpTxNSduIdCfg == TxPduId)
        {
            for (int j = 0; j < PduInfoPtr->SduLength; j++)
            {
                CanTpLocalConfig->CanTpCfg->CanTpChannelCfg->CanTpTxNSduCfg->CanTpTxNPduRefCfg->CanTpTxNPduRef[j] = PduInfoPtr->SduDataPtr[j];
            }
            if (CanTp_TxState == CANTP_TX_IDLE)
                if (PduInfoPtr->SduLength <= 6)
                {
                    CanTp_TxState = CANTP_TX_SEND_SF;
                    static uint8 TxBuffer[8];
                    TxBuffer[0] = (0x00 | (PduInfoPtr->SduLength & 0x0F));
                    CanTpLocalConfig->CanTpCfg->CanTpChannelCfg->CanTpTxNSduCfg->CanTpTxNPduRefCfg->CanTpTxNPduRef = TxBuffer;
                    for (int j = 0; j < PduInfoPtr->SduLength; j++)
                    {
                        TxBuffer[j + 1] = CanTpLocalConfig->CanTpCfg->CanTpChannelCfg->CanTpTxNSduCfg->CanTpTxNPduRefCfg->CanTpTxNPduRef[j];
                    }
                    PduInfoType PduInfo;
                    PduInfo.SduLength = 8;
                    PduInfo.SduDataPtr = TxBuffer;
                    CanTp_TxSubStateMachine = CANTP_TX_WAIT;
                    CanTp_TxState = CANTP_TX_WAIT_FC;
                    return CanIf_Transmit(CanTpLocalConfig->CanTpCfg->CanTpChannelCfg->CanTpTxNSduCfg->CanTpTxNPduRefCfg->CanTpTxNPduConfirmationPduId, &PduInfo);
                }
                else
                {
                    CanTp_TxState = CANTP_TX_SEND_FF;
                    uint8 TxBuffer[8] = {0};
                    TxBuffer[0] = (0x10 | ((PduInfoPtr->SduLength & 0xF00) >> 8));
                    TxBuffer[1] = (PduInfoPtr->SduLength & 0x0FF);
                    for (int j = 0; j < 6; j++)
                    {
                        TxBuffer[j + 2] = CanTpLocalConfig->CanTpCfg->CanTpChannelCfg->CanTpTxNSduCfg->CanTpTxNPduRefCfg->CanTpTxNPduRef[Index++];
                    }
                    PduInfoType PduInfo;
                    PduInfo.SduLength = 8;
                    PduInfo.SduDataPtr = TxBuffer;
                    CanTp_TxSubStateMachine = CANTP_TX_WAIT;
                    CanTp_TxState = CANTP_TX_WAIT_FC;
                    return CanIf_Transmit(CanTpLocalConfig->CanTpCfg->CanTpChannelCfg->CanTpTxNSduCfg->CanTpTxNPduRefCfg->CanTpTxNPduConfirmationPduId, &PduInfo);
                }
        }
        return E_NOT_OK;
    }
}

void CanTp_RxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
    if (CanTp_InitAndShutdownStateMachine == CANTP_OFF)
    {
        Det_ReportError(0, 0, 0, 0);
        return;
    }

    if (CanTp_RxSubStateMachine == CANTP_RX_WAIT)
    {
        CanTp_RxSubStateMachine = CANTP_RX_PROCESSING;
    }
    else
    {
        Det_ReportError(0, 0, 0, 0);
        return;
    }

    // SLAVE
    for (int i = 0; i < NUMBER_OF_CAN_TP_RX_NSDU; i++)
    {
        if (CanTpLocalConfig->CanTpCfg->CanTpChannelCfg->CanTpRxNSduCfg->CanTpRxNPduRefCfg->CanTpRxNPduIdCfg == RxPduId)
        {
            if (CanTp_RxState == CANTP_RX_IDLE)
            {
                if ((PduInfoPtr->SduDataPtr[0] & 0xF0) == 0x00)
                {
                    CanTp_RxState = CANTP_RX_RECEIVE_SF;
                }
                else if ((PduInfoPtr->SduDataPtr[0] & 0xF0) == 0x10)
                {
                    CanTp_RxState = CANTP_RX_RECEIVE_FF;
                }
                else if ((PduInfoPtr->SduDataPtr[0] & 0xF0) == 0x20)
                {
                    CanTp_RxState = CANTP_RX_RECEIVE_CF;
                }
            }

            if (CanTp_RxState == CANTP_RX_RECEIVE_SF)
            {
            }

            if (CanTp_RxState == CANTP_RX_RECEIVE_FF)
            {
                for (int j = 0; j < PduInfoPtr->SduLength - 2; j++)
                {
                    CanTpLocalConfig->CanTpCfg->CanTpChannelCfg->CanTpRxNSduCfg->CanTpRxNPduRefCfg->CanTpRxNPduRef[Index++] = PduInfoPtr->SduDataPtr[j + 2];
                }
                CanTp_RxState = CANTP_RX_SEND_FC;
            }

            if (CanTp_RxState == CANTP_RX_RECEIVE_CF)
            {
                for (int j = 0; j < PduInfoPtr->SduLength - 1; j++)
                {
                    CanTpLocalConfig->CanTpCfg->CanTpChannelCfg->CanTpRxNSduCfg->CanTpRxNPduRefCfg->CanTpRxNPduRef[Index++] = PduInfoPtr->SduDataPtr[j + 1];
                    if (Index >= 20)
                    {
                        Index = 0;
                        Count = 1;
                        uint8 TxBuffer[8];
                        TxBuffer[0] = 0x30;
                        TxBuffer[1] = 0;
                        TxBuffer[2] = 0;
                        CanTpLocalConfig->CanTpCfg->CanTpChannelCfg->CanTpTxNSduCfg->CanTpTxNPduRefCfg->CanTpTxNPduRef = TxBuffer;
                        PduInfoType PduInfo;
                        PduInfo.SduLength = 8;
                        PduInfo.SduDataPtr = TxBuffer;
                        CanIf_Transmit(CanTpLocalConfig->CanTpCfg->CanTpChannelCfg->CanTpTxNSduCfg->CanTpTxNPduRefCfg->CanTpTxNPduConfirmationPduId, &PduInfo);
                        PduInfoType PduInfoToPduR;
                        PduInfoToPduR.SduLength = 20;
                        PduInfoToPduR.SduDataPtr = CanTpLocalConfig->CanTpCfg->CanTpChannelCfg->CanTpRxNSduCfg->CanTpRxNPduRefCfg->CanTpRxNPduRef;
                        PduR_RxIndication(CanTpLocalConfig->CanTpCfg->CanTpChannelCfg->CanTpRxNSduCfg->CanTpRxNSduIdCfg, &PduInfoToPduR);
                        CanTp_RxState = CANTP_RX_IDLE;
                        CanTp_RxSubStateMachine = CANTP_RX_WAIT;
                        return;
                    }
                    CanTp_RxState = CANTP_RX_SEND_FC;
                }
            }

            if (CanTp_RxState == CANTP_RX_SEND_FC)
            {
                uint8 TxBuffer[8];
                TxBuffer[0] = 0x30;
                TxBuffer[1] = 0;
                TxBuffer[2] = 0;
                CanTpLocalConfig->CanTpCfg->CanTpChannelCfg->CanTpTxNSduCfg->CanTpTxNPduRefCfg->CanTpTxNPduRef = TxBuffer;
                PduInfoType PduInfo;
                PduInfo.SduLength = 8;
                PduInfo.SduDataPtr = TxBuffer;
                CanIf_Transmit(CanTpLocalConfig->CanTpCfg->CanTpChannelCfg->CanTpTxNSduCfg->CanTpTxNPduRefCfg->CanTpTxNPduConfirmationPduId, &PduInfo);
                CanTp_RxState = CANTP_RX_IDLE;
            }
            CanTp_RxSubStateMachine = CANTP_RX_WAIT;
            return;
        }
    }

    // // MASTER
    // for (int i = 0; i < NUMBER_OF_CAN_TP_RX_NSDU; i++)
    // {
    //     if (CanTpLocalConfig->CanTpCfg->CanTpChannelCfg->CanTpTxNSduCfg->CanTpTxNPduRefCfg->CanTpTxNPduConfirmationPduId == RxPduId)
    //     {
    //         if (CanTp_TxState == CANTP_TX_WAIT_FC)
    //         {
    //             if (PduInfoPtr->SduDataPtr[0] == 0x30)
    //             {
    //                 CanTp_TxState = CANTP_TX_SEND_CF;
    //             }
    //         }

    //         if (CanTp_TxState == CANTP_TX_SEND_CF)
    //         {
    //             uint8 TxBuffer[8] = {0};
    //             TxBuffer[0] = (0x20 | (Count & 0x0F));
    //             for (int j = 0; j < 7; j++)
    //             {
    //                 TxBuffer[j + 1] = CanTpLocalConfig->CanTpCfg->CanTpChannelCfg->CanTpTxNSduCfg->CanTpTxNPduRefCfg->CanTpTxNPduRef[Index++];
    //                 if (Index >= 20)
    //                 {
    //                     Index = 0;
    //                     Count = 1;
    //                     PduInfoType PduInfo;
    //                     PduInfo.SduLength = 8;
    //                     PduInfo.SduDataPtr = TxBuffer;
    //                     CanIf_Transmit(CanTpLocalConfig->CanTpCfg->CanTpChannelCfg->CanTpTxNSduCfg->CanTpTxNPduRefCfg->CanTpTxNPduConfirmationPduId, &PduInfo);
    //                     CanTp_RxSubStateMachine = CANTP_RX_WAIT;
    //                     CanTp_TxState = CANTP_TX_IDLE;
    //                     return;
    //                 }
    //             }
    //             PduInfoType PduInfo;
    //             PduInfo.SduLength = 8;
    //             PduInfo.SduDataPtr = TxBuffer;
    //             Count++;
    //             CanIf_Transmit(CanTpLocalConfig->CanTpCfg->CanTpChannelCfg->CanTpTxNSduCfg->CanTpTxNPduRefCfg->CanTpTxNPduConfirmationPduId, &PduInfo);
    //             CanTp_RxSubStateMachine = CANTP_RX_WAIT;
    //             CanTp_TxState = CANTP_TX_WAIT_FC;
    //             return;
    //         }
    //     }
    // }
}

void CanTp_TxConfirmation(PduIdType TxPduId, Std_ReturnType result)
{
}

Std_ReturnType CanTp_CancelTransmit(PduIdType TxPduId)
{
    if (CanTp_InitAndShutdownStateMachine == CANTP_OFF)
    {
        Det_ReportError(0, 0, 0, 0);
        return E_NOT_OK;
    }
    CanTp_TxConfirmation(TxPduId, E_NOT_OK);
    return E_NOT_OK;
}

Std_ReturnType CanTp_CancelReceive(PduIdType RxPduId)
{
    if (CanTp_InitAndShutdownStateMachine == CANTP_OFF)
    {
        Det_ReportError(0, 0, 0, 0);
        return E_NOT_OK;
    }

    return E_NOT_OK;
}