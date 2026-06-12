#include "CanTp.h"
#include "CanTp_Cfg.h"
#include "CanIf.h"
#include "Det.h"

#define MASTER

static CanTp_InitAndShutdownStateMachineType CanTp_InitAndShutdownStateMachine = CANTP_OFF;
static CanTp_TxSubStateMachineType CanTp_TxSubStateMachine = CANTP_TX_WAIT;
static CanTp_RxSubStateMachineType CanTp_RxSubStateMachine = CANTP_RX_WAIT;
static CanTp_BufferStateMachineType CanTp_BufferStateMachine = CANTP_BUFFER_UNLOCK;
static CanTp_TxStateMachine CanTp_TxState = CANTP_TX_IDLE;
static CanTp_RxStateMachine CanTp_RxState = CANTP_RX_IDLE;
static const CanTp_ConfigType *CanTpLocalConfig;

// // Master
#ifdef MASTER

volatile uint8 Index = 0;
volatile uint8 Count = 1;
volatile uint32 Length = 0;
volatile uint32 Bs = 0;
volatile uint32 StMin = 0;
#endif

// Slave
#ifdef SLAVE
volatile uint8 Index = 0;
volatile uint8 Count = 1;
volatile uint32 Length = 20;
volatile uint32 Bs = BS;
volatile uint32 StMin = STmin;
#endif

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
    if (CanTp_TxSubStateMachine != CANTP_TX_WAIT)
    {
        Det_ReportError(0, 0, 0, 0);
        return E_NOT_OK;
    }

    for (int i = 0; i < NUMBER_OF_CAN_TP_TX_NSDU; i++)
    {

        if (CanTpLocalConfig->CanTpCfg->CanTpChannelCfg->CanTpTxNSduCfg->CanTpTxNSduIdCfg == TxPduId)
        {
            CanTp_TxSubStateMachine = CANTP_TX_PROCESSING;
            for (int j = 0; j < PduInfoPtr->SduLength; j++)
            {
                CanTpLocalConfig->CanTpCfg->CanTpChannelCfg->CanTpTxNSduCfg->CanTpTxNPduRefCfg->CanTpTxNPduRef[j] = PduInfoPtr->SduDataPtr[j];
            }
            Length = PduInfoPtr->SduLength;
            if (CanTp_TxState == CANTP_TX_IDLE)
            {
                if (PduInfoPtr->SduLength <= 6)
                {
                    CanTp_TxState = CANTP_TX_SEND_SF;
                    uint8 TxBuffer[8] = {0};
                    TxBuffer[0] = (0x00 | (PduInfoPtr->SduLength & 0x0F));
                    CanTpLocalConfig->CanTpCfg->CanTpChannelCfg->CanTpTxNSduCfg->CanTpTxNPduRefCfg->CanTpTxNPduRef = TxBuffer;
                    for (int j = 0; j < PduInfoPtr->SduLength; j++)
                    {
                        TxBuffer[j + 1] = CanTpLocalConfig->CanTpCfg->CanTpChannelCfg->CanTpTxNSduCfg->CanTpTxNPduRefCfg->CanTpTxNPduRef[j];
                    }
                    PduInfoType PduInfo;
                    PduInfo.SduLength = 8;
                    PduInfo.SduDataPtr = TxBuffer;
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
                    CanTp_TxState = CANTP_TX_WAIT_FC;
                    return CanIf_Transmit(CanTpLocalConfig->CanTpCfg->CanTpChannelCfg->CanTpTxNSduCfg->CanTpTxNPduRefCfg->CanTpTxNPduConfirmationPduId, &PduInfo);
                }
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
#ifdef SLAVE

    for (int i = 0; i < NUMBER_OF_CAN_TP_RX_NSDU; i++)
    {
        if (CanTpLocalConfig->CanTpCfg->CanTpChannelCfg->CanTpRxNSduCfg->CanTpRxNPduRefCfg->CanTpRxNPduIdCfg == RxPduId)
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
                    PduR_RxIndication(CanTpLocalConfig->CanTpCfg->CanTpChannelCfg->CanTpRxNSduCfg->CanTpRxNSduIdCfg, &PduInfoToPduR);
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
                for (int k = 0; k < Bs; k++)
                {
                    static PduInfoType PduInfo;
                    static uint8 TxBuffer[8] = {0};
                    TxBuffer[0] = (0x20 | (Count & 0x0F));
                    for (int j = 0; j < 7; j++)
                    {
                        TxBuffer[j + 1] = CanTpLocalConfig->CanTpCfg->CanTpChannelCfg->CanTpTxNSduCfg->CanTpTxNPduRefCfg->CanTpTxNPduRef[Index++];
                        if (Index >= Length)
                        {
                            Index = 0;
                            Count = 1;
                            PduInfo.SduLength = 8;
                            PduInfo.SduDataPtr = TxBuffer;
                            CanTp_TxState = CANTP_TX_IDLE;
                            CanTp_TxSubStateMachine = CANTP_TX_WAIT;
                            CanIf_Transmit(CanTpLocalConfig->CanTpCfg->CanTpChannelCfg->CanTpTxNSduCfg->CanTpTxNPduRefCfg->CanTpTxNPduConfirmationPduId, &PduInfo);
                            return;
                        }
                    }
                    PduInfo.SduLength = 8;
                    PduInfo.SduDataPtr = TxBuffer;
                    CanTp_TxState = CANTP_TX_WAIT_FC;
                    CanIf_Transmit(CanTpLocalConfig->CanTpCfg->CanTpChannelCfg->CanTpTxNSduCfg->CanTpTxNPduRefCfg->CanTpTxNPduConfirmationPduId, &PduInfo);
                    for (int delay = 0; delay < StMin * 100; delay++)
                        ;
                }
            }
        }
    }
#endif
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