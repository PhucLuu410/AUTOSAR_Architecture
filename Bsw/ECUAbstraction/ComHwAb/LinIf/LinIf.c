#include "LinIf.h"
#include "LinIf_Cfg.h"
#include "stm32f103xb.h"
#include "Std_Types.h"

static const LinIf_ConfigType *LinIf_LocalConfig = NULL_PTR;
static const LinTp_ConfigType *LinTp_LocalConfig = NULL_PTR;

LinTpStateMachine LinTpState[] = {[0] = LINTP_UNINIT};
LinTpMaterSubStateMachine LinTpMaterSubState[] = {[0] = LINTP_MASTER_IDLE};
LinTpSlaveSubStateMachine LinTpSlaveSubState[] = {[0] = LINTP_SLAVE_IDLE};

static Lin_PduType LocalPduInfo = {
    .Pid = 0,
    .Dl = 0,
    .CsModel = 0xFF,
    .Response = 0xFF,
    .SduDataPtr = NULL_PTR,
};

static uint8 BS[3] = {0};
static uint8 TP_CURRENT_POINTER[3] = {0};
//---------------------------------------------------------------------------------------------------------
void LinIf_Init(const LinIf_ConfigType *ConfigPtr)
{
    if (ConfigPtr != NULL_PTR)
        LinIf_LocalConfig = ConfigPtr;
}

Std_ReturnType LinIf_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr)
{
    for (int i = 0; i < 2; i++)
    {
        if (TxPduId == LinIf_LocalConfig->LinIfGlobalConfig_0->LinIfChannel_0[i].LinIfFrame_0[0].LinIfFrameIndex)
        {
            LocalPduInfo.Pid = LinIf_LocalConfig->LinIfGlobalConfig_0->LinIfChannel_0[i].LinIfFrame_0[0].LinIfFrameId;
            LocalPduInfo.Dl = PduInfoPtr->SduLength;
            LocalPduInfo.CsModel = LinIf_LocalConfig->LinIfGlobalConfig_0->LinIfChannel_0[i].LinIfFrame_0[0].LinIfChecksumType_0;
            LocalPduInfo.Response = LinIf_LocalConfig->LinIfGlobalConfig_0->LinIfChannel_0[i].LinIfFrame_0[0].LinIfFrameType_0 == UNCONDITIONAL ? LIN_FRAMERESPONSE_TX : LIN_FRAMERESPONSE_RX;
            LocalPduInfo.SduDataPtr = PduInfoPtr->SduDataPtr;
            return Lin_SendFrame(LIN_CHANNEL_1, &LocalPduInfo);
        }
    }
    return E_NOT_OK;
}

Std_ReturnType LinIf_EnableBusMirroring(NetworkHandleType Channel, boolean MirroringActive)
{
    for (int i = 0; i < 1; i++)
    {
        if (LinIf_LocalConfig->LinIfGlobalConfig_0->LinIfChannel_0[i].LinIfChannelRef_0 == Channel)
        {
            LinIf_LocalConfig->LinIfGeneral_0->LinIfBusMirroringSupported = MirroringActive;
            return E_OK;
        }
    }
    return E_NOT_OK;
}

Std_ReturnType LinIf_GotoSleep(NetworkHandleType Channel)
{
    return Lin_GoToSleep(Channel);
}

Std_ReturnType LinIf_Wakeup(NetworkHandleType Channel)
{
    return Lin_Wakeup(Channel);
}

void LinIf_RxIndication(NetworkHandleType Channel, uint8 *Lin_SduPtr)
{
    for (int i = 0; i < 2; i++)
    {
        if (Channel == LinIf_LocalConfig->LinIfGlobalConfig_0->LinIfChannel_0[i].LinIfChannelRef_0)
        {
            for (int j = 0; j < 2; j++)
            {
                if (Lin_SduPtr[0] == LinIf_LocalConfig->LinIfGlobalConfig_0->LinIfChannel_0[i].LinIfFrame_0[j].LinIfFrameId)
                {
                    PduInfoType PduInfo;
                    PduInfo.SduDataPtr = Lin_SduPtr + 3;
                    PduInfo.SduLength = 8;
                    PduR_RxIndication(LinIf_LocalConfig->LinIfGlobalConfig_0->LinIfChannel_0[i].LinIfComMNetworkHandleRef_0, &PduInfo);
                    break;
                }
            }
        }
    }

    // // MASTER MODE
    // for (int i = 0; i < 2; i++)
    // {
    //     if (Channel == LinTp_LocalConfig->LinTpGlobalConfig_0->LinTpRxNSdu_0[i].LinTpRxNSduChannelRef)
    //     {
    //         for (int j = 0; j < 2; j++)
    //         {
    //             if (Lin_SduPtr[0] == LinTp_LocalConfig->LinTpGlobalConfig_0->LinTpRxNSdu_0[i].LinTpRxNSduNad && LinTpMaterSubState[i] == LINTP_CHANNEL_WAIT_FC)
    //             {
    //                 uint8 *DataReceivePtrFromSlaveLinTp = Lin_SduPtr + 1;
    //                 switch (DataReceivePtrFromSlaveLinTp[0])
    //                 {
    //                 case 0x30:
    //                     LinTpMaterSubState[i] = LINTP_MASTER_SEND_CF;
    //                     BS[i] = DataReceivePtrFromSlaveLinTp[1];
    //                     break;
    //                 case 0x31:
    //                     LinTpMaterSubState[i] = LINTP_MASTER_WAIT_FC;
    //                     break;
    //                 case 0x32:
    //                     LinTpMaterSubState[i] = LINTP_MASTER_FAIL;
    //                     break;
    //                 }
    //             }
    //         }
    //     }
    // }

    // SLAVE MODE
    for (int i = 0; i < 2; i++)
    {
        if (Channel == LinTp_LocalConfig->LinTpGlobalConfig_0->LinTpRxNSdu_0[i].LinTpRxNSduChannelRef)
        {
            for (int j = 0; j < 2; j++)
            {
                if (Lin_SduPtr[0] == LinTp_LocalConfig->LinTpGlobalConfig_0->LinTpRxNSdu_0[i].LinTpRxNSduNad)
                {
                    uint8 CURRENT_BS = (Lin_SduPtr[1] & 0x0F) << 8 | ((Lin_SduPtr[2] & 0xFF));
                    CURRENT_BS = ((CURRENT_BS - 6) / 8) + 1;
                    if (LinTpSlaveSubState[i] == LINTP_SLAVE_IDLE)
                    {
                        Lin_PduType PduInfo;
                        PduInfo.Pid = Lin_SduPtr[0];
                        PduInfo.Dl = 8;
                        PduInfo.CsModel = LIN_CLASSIC_CS;
                        PduInfo.Response = LIN_FRAMERESPONSE_RX;
                        uint8 DATA[8] = {0};
                        DATA[0] = 0x30;
                        DATA[1] = CURRENT_BS;
                        PduInfo.SduDataPtr = DATA;
                        Lin_SendFrame(LinTp_LocalConfig->LinTpGlobalConfig_0->LinTpTxNSdu_0[i].LinTpTxNSduChannelRef, &PduInfo);
                        LinTpSlaveSubState[i] = LINTP_SLAVE_WAIT_CF;
                        break;
                    }
                    if (LinTpSlaveSubState[i] == LINTP_SLAVE_WAIT_CF)
                    {
                        --CURRENT_BS;
                        if (CURRENT_BS == 0)
                        {
                            LinTpSlaveSubState[i] = LINTP_SLAVE_IDLE;
                        }
                    }
                }
            }
        }
    }
}

//---------------------------------------------------------------------------------------------------------

void LinTp_Init(const LinTp_ConfigType *ConfigPtr)
{
    if (ConfigPtr != NULL_PTR)
        LinTp_LocalConfig = ConfigPtr;
    for (int i = 0; i < sizeof(LinTpTxNSduConfig) / sizeof(LinTpTxNSduConfig[0]); i++)
    {
        LinTpState[i] = LINTP_INIT;
    }
}

Std_ReturnType LinTp_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr)
{
    // MASTER MODE
    for (int a = 0; a < sizeof(LinTpTxNSduConfig) / sizeof(LinTpTxNSduConfig[0]); a++)
    {
        if (LinTp_LocalConfig->LinTpGlobalConfig_0->LinTpTxNSdu_0[a].LinTpTxNSduId == TxPduId)
        {
            if (LinTpState[a] != LINTP_INIT)
                return E_NOT_OK;

            if (LinTpMaterSubState[a] != LINTP_MASTER_IDLE)
                return E_NOT_OK;

            LinTpMaterSubState[a] = LINTP_MASTER_BUSY;
            for (int j = 0; j < PduInfoPtr->SduLength; j++)
            {
                LinTp_LocalConfig->LinTpGlobalConfig_0->LinTpTxNSdu_0[a].LinTpTxNSduPduRef[j] = PduInfoPtr->SduDataPtr[j];
            }
            break;
        }
        return E_OK;
    }
    return E_NOT_OK;
}

void LinIf_MainFunction_LinTpMasterSend_SF_FF(void)
{
    for (int i = 0; i < sizeof(LinTpTxNSduConfig) / sizeof(LinTpTxNSduConfig[0]); i++)
    {
        if (LinTpMaterSubState[i] == LINTP_MASTER_BUSY)
        {
            Lin_PduType PduInfo;
            PduInfo.Pid = 0x12;
            PduInfo.Dl = 8;
            PduInfo.CsModel = LIN_CLASSIC_CS;
            PduInfo.Response = LIN_FRAMERESPONSE_RX;
            if (sizeof(Buffer_ID_0x12) < 8)
            {
                uint8 PCI = 0x00 | (PduInfo.Dl & 0x0F);
                uint8 DATA[8] = {0};
                DATA[0] = PCI;
                for (int j = 0; j < PduInfo.Dl; j++)
                {
                    DATA[1 + j] = LinTp_LocalConfig->LinTpGlobalConfig_0->LinTpTxNSdu_0[i].LinTpTxNSduPduRef[j];
                }
                PduInfo.SduDataPtr = DATA;
            }
            else
            {
                uint8 PCI = 0x10 | ((sizeof(Buffer_ID_0x12) >> 8) & 0x0F);
                uint8 DATA_LENGTH = sizeof(Buffer_ID_0x12) & 0xFF;
                uint8 DATA[8] = {0};
                DATA[0] = PCI;
                DATA[1] = DATA_LENGTH;
                for (int j = 0; j < 6; j++)
                {
                    DATA[j + 2] = LinTp_LocalConfig->LinTpGlobalConfig_0->LinTpTxNSdu_0[i].LinTpTxNSduPduRef[j];
                }
                PduInfo.SduDataPtr = DATA;
                TP_CURRENT_POINTER[i] = 6;
            }
            Lin_SendFrame(LinTp_LocalConfig->LinTpGlobalConfig_0->LinTpTxNSdu_0[i].LinTpTxNSduChannelRef, &PduInfo);
            LinTpMaterSubState[i] = LINTP_MASTER_WAIT_FC;
        }
    }
}

void LinIf_MainFunction_LinTpMasterSend_CF(void)
{
    for (int i = 0; i < sizeof(LinTpTxNSduConfig) / sizeof(LinTpTxNSduConfig[0]); i++)
    {
        if (LinTpMaterSubState[i] == LINTP_MASTER_SEND_CF)
        {
            Lin_PduType PduInfo;
            for (int b = 1; b <= BS[i]; b++)
            {
                uint8 DATA_LENGTH = sizeof(Buffer_ID_0x12);
                uint8 PCI = 0x20 | (b & 0x0F);
                uint8 DATA[8] = {0};
                DATA[0] = PCI;
                for (int j = 1; j < 8; j++)
                {
                    if (TP_CURRENT_POINTER[i] < DATA_LENGTH)
                    {
                        DATA[j] = Buffer_ID_0x12[TP_CURRENT_POINTER[i]];
                        TP_CURRENT_POINTER[i]++;
                    }
                    else
                    {
                        DATA[j] = 0x00;
                    }
                }
                PduInfo.Pid = 0x12;
                PduInfo.Dl = 8;
                PduInfo.CsModel = LIN_CLASSIC_CS;
                PduInfo.Response = LIN_FRAMERESPONSE_RX;
                PduInfo.SduDataPtr = DATA;
                Lin_SendFrame(LinTp_LocalConfig->LinTpGlobalConfig_0->LinTpTxNSdu_0[i].LinTpTxNSduChannelRef, &PduInfo);
            }
        }
        if (TP_CURRENT_POINTER[i] >= sizeof(Buffer_ID_0x12))
        {
            LinTpMaterSubState[i] = LINTP_MASTER_IDLE;
        }
        else
        {
            LinTpMaterSubState[i] = LINTP_MASTER_WAIT_FC;
        }
    }
}

void LinTp_Shutdown(void)
{
}
