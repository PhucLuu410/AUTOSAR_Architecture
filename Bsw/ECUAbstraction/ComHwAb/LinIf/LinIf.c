#include "LinIf.h"
#include "LinIf_Cfg.h"
#include "stm32f103xb.h"

const LinIf_ConfigType *LinIf_Local_Config;
uint8 data[8] = {0};
static uint8 BS = 0;
static uint8 STmin = 0;
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
    if (TxPduId >= NUMBER_OF_LINIF_FRAME_TX)
    {
        return E_NOT_OK;
    }
    if (PduInfoPtr == NULL_PTR)
    {
        return E_NOT_OK;
    }

    for (int ChannelNumber = 0; ChannelNumber < NUMBER_OF_LIN_CHANNEL; ChannelNumber++)
    {
        for (int FrameNumber = 0; FrameNumber < NUMBER_OF_LINIF_FRAME_TX; FrameNumber++)
        {
            if (LinIf_Local_Config->LinIfGlobalCfg.LinIfChannelCfg[ChannelNumber].LinIfFrameCfg[FrameNumber].LinIfFrameIndex == TxPduId)
            {
                Lin_PduType LinPdu;
                LinPdu.Pid = LinIf_Local_Config->LinIfGlobalCfg.LinIfChannelCfg[ChannelNumber].LinIfFrameCfg[FrameNumber].LinIfFrameId;
                LinPdu.Dl = PduInfoPtr->SduLength;
                if (LinIf_Local_Config->LinIfGlobalCfg.LinIfChannelCfg[ChannelNumber].LinIfFrameCfg[FrameNumber].LinIfChecksum == CLASSIC)
                {
                    LinPdu.CsModel = LIN_CLASSIC_CS;
                }
                else
                {
                    LinPdu.CsModel = LIN_ENHANCED_CS;
                }
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
    for (uint8 LinFrameNumber = 0; LinFrameNumber < NUMBER_OF_LINIF_FRAME_RX; LinFrameNumber++)
    {
        if (LinIfFrameConfigRx[LinFrameNumber].Channel == Channel && LinIfFrameConfigRx[LinFrameNumber].Pid == Lin_SduPtr[0])
        {
            PduInfoType PduInfo;
            PduInfo.SduLength = LinIfFrameConfigRx[LinFrameNumber].Length;
            PduInfo.SduDataPtr = Lin_SduPtr + 1;
            LinIfFrameConfigRx[LinFrameNumber].Receive_Func(LinIfFrameConfigRx[LinFrameNumber].PduId, &PduInfo);
        }
    }
}

//-----------------------------------------------------------------------------------------------------------
const LinTp_ConfigType *LinTp_Local_Config;

typedef enum
{
    LIN_TP_TX_IDLE,
    LIN_TP_TX_SF,
    LIN_TP_TX_FF,
    LIN_TP_TX_WAIT_FC_SF,
    LIN_TP_TX_WAIT_FC_FF,
    LIN_TP_TX_CF,
} LinTp_TxStateType;

typedef enum
{
    LIN_TP_RX_IDLE,
    LIN_TP_RX_WAIT_SF,
    LIN_TP_RX_WAIT_FF,
    LIN_TP_RX_WAIT_CF,
} LinTp_RxStateType;

LinTp_RxStateType LinTp_RxState[NUMBER_OF_LINTP_FRAME_RX] = {LIN_TP_RX_IDLE};
LinTp_TxStateType LinTp_TxState[NUMBER_OF_LINTP_FRAME_TX] = {LIN_TP_TX_IDLE};

void LinTp_Init(const LinTp_ConfigType *ConfigPtr)
{
    if (ConfigPtr == NULL_PTR)
    {
        return;
    }
    LinTp_Local_Config = ConfigPtr;
}

Std_ReturnType LinTp_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr)
{
    for (uint8 IdNumberInTable = 0; IdNumberInTable < NUMBER_OF_LINTP_FRAME_TX; IdNumberInTable++)
    {
        if (LinTp_Local_Config->LinTpGlobalCfg.LinTpTxNSduCfg[IdNumberInTable].LinTpTxNSduId == TxPduId)
        {
            for (int i = 0; i < PduInfoPtr->SduLength; i++)
            {
                LinTp_Local_Config->LinTpGlobalCfg.LinTpTxNSduCfg[IdNumberInTable].LinTpTxNSduPduRef[i] = PduInfoPtr->SduDataPtr[i];
            }

            if (LinTp_TxState[IdNumberInTable] == LIN_TP_TX_IDLE)
            {
                if (PduInfoPtr->SduLength <= 6)
                {
                    // Chuyen doi trang thai sang gui SF
                    LinTp_TxState[IdNumberInTable] = LIN_TP_TX_SF;

                    // Chuan bi goi tin SF , Length do o tren dua xuong
                    uint8 SF[8] = {0};
                    SF[0] = (0x00 | (PduInfoPtr->SduLength & 0x0F));
                    for (int i = 0; i < PduInfoPtr->SduLength; i++)
                    {
                        SF[i + 1] = PduInfoPtr->SduDataPtr[i];
                    }

                    // Chuan bi goi tin cho Lin_SendFrame va gui di
                    Lin_PduType LinPdu;
                    LinPdu.Pid = LinTp_Local_Config->LinTpGlobalCfg.LinTpTxNSduCfg[IdNumberInTable].LinTpTxNSduNad;
                    LinPdu.Dl = 8;
                    LinPdu.CsModel = LIN_CLASSIC_CS;
                    LinPdu.Response = LIN_FRAMERESPONSE_TX;
                    LinPdu.SduDataPtr = SF;
                    LinTp_TxState[IdNumberInTable] = LIN_TP_TX_WAIT_FC_SF;
                    return Lin_SendFrame(LinTp_Local_Config->LinTpGlobalCfg.LinTpTxNSduCfg[IdNumberInTable].LinTpTxNSduChannelRef, &LinPdu);
                }
                else
                {
                    // Chuyen doi trang thai sang gui FF
                    LinTp_TxState[IdNumberInTable] = LIN_TP_TX_FF;
                    uint8 SF[8] = {0};
                    SF[0] = (0x10 | ((PduInfoPtr->SduLength >> 8) & 0x0F));
                    SF[1] = PduInfoPtr->SduLength & 0xFF;
                    for (int i = 0; i < 6; i++)
                    {
                        SF[i + 2] = PduInfoPtr->SduDataPtr[i];
                    }
                    Lin_PduType LinPdu;
                    LinPdu.Pid = LinTp_Local_Config->LinTpGlobalCfg.LinTpTxNSduCfg[IdNumberInTable].LinTpTxNSduNad;
                    LinPdu.Dl = 8;
                    LinPdu.CsModel = LIN_CLASSIC_CS;
                    LinPdu.Response = LIN_FRAMERESPONSE_TX;
                    LinPdu.SduDataPtr = SF;
                    LinTp_TxState[IdNumberInTable] = LIN_TP_TX_WAIT_FC_FF;
                    return Lin_SendFrame(LinTp_Local_Config->LinTpGlobalCfg.LinTpTxNSduCfg[IdNumberInTable].LinTpTxNSduChannelRef, &LinPdu);
                }
            }
        }
    }
    return E_NOT_OK;
}

void LinTp_RxIndication(PduIdType TxPduId, const PduInfoType *PduInfoPtr)
{
    // SLAVE
    for (int i = 0; i < NUMBER_OF_LINTP_FRAME_RX; i++)
    {
        if (LinTp_Local_Config->LinTpGlobalCfg.LinTpRxNSduCfg[i].LinTpRxNSduId == TxPduId)
        {
            static uint16 count = 0;

            // Kiem tra goi tin xem la SF hay FF
            if (LinTp_RxState[i] == LIN_TP_RX_IDLE)
            {
                if ((PduInfoPtr->SduDataPtr[0] & 0xF0) == 0x10)
                {
                    LinTp_RxState[i] = LIN_TP_RX_WAIT_FF;
                }
                else
                {
                    LinTp_RxState[i] = LIN_TP_RX_WAIT_SF;
                }
            }

            if (LinTp_RxState[i] == LIN_TP_RX_WAIT_SF)
            {
                for (int j = 0; j < (PduInfoPtr->SduDataPtr[0] & 0x0F) - 2; j++)
                {
                    LinTp_Local_Config->LinTpGlobalCfg.LinTpRxNSduCfg[i].LinTpRxNSduPduRef[count++] = PduInfoPtr->SduDataPtr[j + 2];
                }
                uint8 FC[8] = {0};
                FC[0] = 0x30;
                FC[1] = 0;
                FC[2] = 0;
                Lin_PduType LinPdu;
                LinPdu.Pid = LinTp_Local_Config->LinTpGlobalCfg.LinTpTxNSduCfg[i].LinTpTxNSduNad;
                LinPdu.Dl = 8;
                LinPdu.CsModel = LIN_CLASSIC_CS;
                LinPdu.Response = LIN_FRAMERESPONSE_TX;
                LinPdu.SduDataPtr = FC;
                Lin_SendFrame(LinTp_Local_Config->LinTpGlobalCfg.LinTpTxNSduCfg[i].LinTpTxNSduChannelRef, &LinPdu);
                LinTp_RxState[i] = LIN_TP_RX_IDLE;
                return;
            }

            if (LinTp_RxState[i] == LIN_TP_RX_WAIT_FF)
            {
                for (int j = 0; j < PduInfoPtr->SduLength - 2; j++)
                {
                    LinTp_Local_Config->LinTpGlobalCfg.LinTpRxNSduCfg[i].LinTpRxNSduPduRef[count++] = PduInfoPtr->SduDataPtr[j + 2];
                }
                uint8 FC[8] = {0};
                FC[0] = 0x30;
                FC[1] = LINTP_BLOCK_SIZE;
                FC[2] = LINTP_ST_MIN;
                Lin_PduType LinPdu;
                LinPdu.Pid = LinTp_Local_Config->LinTpGlobalCfg.LinTpTxNSduCfg[i].LinTpTxNSduNad;
                LinPdu.Dl = 8;
                LinPdu.CsModel = LIN_CLASSIC_CS;
                LinPdu.Response = LIN_FRAMERESPONSE_TX;
                LinPdu.SduDataPtr = FC;
                Lin_SendFrame(LinTp_Local_Config->LinTpGlobalCfg.LinTpTxNSduCfg[i].LinTpTxNSduChannelRef, &LinPdu);
                LinTp_RxState[i] = LIN_TP_RX_WAIT_CF;
                return;
            }

            if (LinTp_RxState[i] == LIN_TP_RX_WAIT_CF)
            {
                // Copy phan tu vao mang cho truoc
                for (int j = 0; j < PduInfoPtr->SduLength - 1; j++)
                {
                    LinTp_Local_Config->LinTpGlobalCfg.LinTpRxNSduCfg[i].LinTpRxNSduPduRef[count++] = PduInfoPtr->SduDataPtr[j + 1];
                }
                static uint8 BS_Count = LINTP_BLOCK_SIZE;
                if (count >= LINTP_DATA_LENGTH)
                {
                    count = 0;
                    BS_Count = LINTP_BLOCK_SIZE;
                    PduInfoType PduInfo;
                    PduInfo.SduLength = LINTP_DATA_LENGTH;
                    PduInfo.SduDataPtr = LinTp_Local_Config->LinTpGlobalCfg.LinTpRxNSduCfg[i].LinTpRxNSduPduRef;
                    PduR_RxIndication(LinTp_Local_Config->LinTpGlobalCfg.LinTpRxNSduCfg[i].LinTpRxNSduId, &PduInfo);
                    uint8 FC[8] = {0};
                    FC[0] = 0x30;
                    FC[1] = LINTP_BLOCK_SIZE;
                    FC[2] = LINTP_ST_MIN;
                    Lin_PduType LinPdu;
                    LinPdu.Pid = LinTp_Local_Config->LinTpGlobalCfg.LinTpTxNSduCfg[i].LinTpTxNSduNad;
                    LinPdu.Dl = 8;
                    LinPdu.CsModel = LIN_CLASSIC_CS;
                    LinPdu.Response = LIN_FRAMERESPONSE_TX;
                    LinPdu.SduDataPtr = FC;
                    Lin_SendFrame(LinTp_Local_Config->LinTpGlobalCfg.LinTpTxNSduCfg[i].LinTpTxNSduChannelRef, &LinPdu);
                    LinTp_RxState[i] = LIN_TP_RX_IDLE;
                    return;
                }
                BS_Count--;
                if (BS_Count == 0)
                {
                    BS_Count = LINTP_BLOCK_SIZE;
                    uint8 FC[8] = {0};
                    FC[0] = 0x30;
                    FC[1] = LINTP_BLOCK_SIZE;
                    FC[2] = LINTP_ST_MIN;
                    Lin_PduType LinPdu;
                    LinPdu.Pid = LinTp_Local_Config->LinTpGlobalCfg.LinTpTxNSduCfg[i].LinTpTxNSduNad;
                    LinPdu.Dl = 8;
                    LinPdu.CsModel = LIN_CLASSIC_CS;
                    LinPdu.Response = LIN_FRAMERESPONSE_TX;
                    LinPdu.SduDataPtr = FC;
                    Lin_SendFrame(LinTp_Local_Config->LinTpGlobalCfg.LinTpTxNSduCfg[i].LinTpTxNSduChannelRef, &LinPdu);
                    return;
                }

                // uint8 FC[8] = {0};
                // FC[0] = 0x30;
                // FC[1] = LINTP_BLOCK_SIZE;
                // FC[2] = LINTP_ST_MIN;
                // Lin_PduType LinPdu;
                // LinPdu.Pid = LinTp_Local_Config->LinTpGlobalCfg.LinTpTxNSduCfg[i].LinTpTxNSduNad;
                // LinPdu.Dl = 8;
                // LinPdu.CsModel = LIN_CLASSIC_CS;
                // LinPdu.Response = LIN_FRAMERESPONSE_TX;
                // LinPdu.SduDataPtr = FC;
                // Lin_SendFrame(LinTp_Local_Config->LinTpGlobalCfg.LinTpTxNSduCfg[i].LinTpTxNSduChannelRef, &LinPdu);
                // LinTp_RxState[i] = LIN_TP_RX_WAIT_CF;
                // return;
            }
        }
    }

    // // MASTER
    // for (int i = 0; i < NUMBER_OF_LINTP_FRAME_RX; i++)
    // {
    //     if (LinTp_Local_Config->LinTpGlobalCfg.LinTpRxNSduCfg[i].LinTpRxNSduId == TxPduId)
    //     {
    //         // Nhan FC check xem SF hay FF
    //         if (PduInfoPtr->SduDataPtr[0] == 0x30 && LinTp_TxState[i] == LIN_TP_TX_WAIT_FC_SF)
    //         {
    //             LinTp_TxState[i] = LIN_TP_TX_IDLE;
    //         }
    //         else if (PduInfoPtr->SduDataPtr[0] == 0x30 && LinTp_TxState[i] == LIN_TP_TX_WAIT_FC_FF)
    //         {
    //             BS = PduInfoPtr->SduDataPtr[1];
    //             STmin = PduInfoPtr->SduDataPtr[2];
    //             LinTp_TxState[i] = LIN_TP_TX_CF;
    //         }
    //         else if (PduInfoPtr->SduDataPtr[0] == 0x31)
    //         {
    //             LinTp_TxState[i] = LIN_TP_TX_WAIT_FC_FF;
    //             return;
    //         }
    //         else if (PduInfoPtr->SduDataPtr[0] == 0x32)
    //         {
    //             return;
    //         }

    //         // Neu la gui FF chuan bi FC
    //         for (int j = 0; j < BS; j++)
    //         {

    //             if (LinTp_TxState[i] == LIN_TP_TX_CF)
    //             {
    //                 static uint16 DataPtrIndex = 6;
    //                 static uint16 Count = 1;
    //                 uint8 CF[8] = {0};
    //                 CF[0] = (0x20 | (Count & 0x0F));
    //                 for (int j = 0; j < 7; j++)
    //                 {
    //                     if (DataPtrIndex >= 20)
    //                     {
    //                         LinTp_TxState[i] = LIN_TP_TX_IDLE;
    //                         break;
    //                     }
    //                     CF[j + 1] = LinTp_Local_Config->LinTpGlobalCfg.LinTpTxNSduCfg[i].LinTpTxNSduPduRef[DataPtrIndex++];
    //                 }
    //                 Lin_PduType LinPdu;
    //                 LinPdu.Pid = LinTp_Local_Config->LinTpGlobalCfg.LinTpTxNSduCfg[i].LinTpTxNSduNad;
    //                 LinPdu.Dl = 8;
    //                 LinPdu.CsModel = LIN_CLASSIC_CS;
    //                 LinPdu.Response = LIN_FRAMERESPONSE_TX;
    //                 LinPdu.SduDataPtr = CF;
    //                 if (LinTp_TxState[i] != LIN_TP_TX_IDLE)
    //                 {
    //                     Lin_SendFrame(LinTp_Local_Config->LinTpGlobalCfg.LinTpTxNSduCfg[i].LinTpTxNSduChannelRef, &LinPdu);
    //                     Count++;
    //                 }
    //                 else if (LinTp_TxState[i] == LIN_TP_TX_IDLE)
    //                 {
    //                     DataPtrIndex = 6;
    //                     Count = 1;
    //                     return;
    //                 }
    //             }
    //             while (STmin)
    //             {
    //                 STmin--;
    //             }
    //         }
    //         LinTp_TxState[i] = LIN_TP_TX_WAIT_FC_FF;
    //     }
    // }
}