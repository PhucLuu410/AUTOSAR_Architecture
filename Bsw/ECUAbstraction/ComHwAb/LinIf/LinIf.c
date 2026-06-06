#include "LinIf.h"
#include "LinIf_Cfg.h"
#include "stm32f103xb.h"
#include "Std_Types.h"

static const LinIf_ConfigType *LinIf_LocalConfig = NULL_PTR;
static const LinTp_ConfigType *LinTp_LocalConfig = NULL_PTR;

static uint8 *LinTpFcCheckPduPtr;

static uint8 LinTpMasterState = 0;
uint8 LinDriverDataArray[9] = {0};

static Lin_PduType LocalPduInfo = {
    .Pid = 0,
    .Dl = 0,
    .CsModel = 0xFF,
    .Response = 0xFF,
    .SduDataPtr = NULL_PTR,
};

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
}

//---------------------------------------------------------------------------------------------------------

typedef enum
{
    LINTP_UNINIT,
    LINTP_INIT,
} LinTpStateMachine;

typedef enum
{
    LINTP_CHANNEL_IDLE,
    LINTP_CHANNEL_BUSY,
} LinTpSubStateMachine;

LinTpStateMachine LinTpState[] = {[0] = LINTP_UNINIT};
LinTpSubStateMachine LinTpSubState[] = {[0] = LINTP_CHANNEL_IDLE};

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
    for (int a = 0; a < sizeof(LinTpTxNSduConfig) / sizeof(LinTpTxNSduConfig[0]); a++)
    {
        if (LinTp_LocalConfig->LinTpGlobalConfig_0->LinTpTxNSdu_0[a].LinTpTxNSduId == TxPduId)
        {
            if (LinTpState[a] != LINTP_INIT)
                return E_NOT_OK;

            if (LinTpSubState[a] != LINTP_CHANNEL_IDLE)
                return E_NOT_OK;

            LinTpSubState[a] = LINTP_CHANNEL_BUSY;
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

void LinIf_MainFunction_LinTpSendHeader(void)
{
    if (LinTpSubState[0] == LINTP_CHANNEL_BUSY)
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
            for (int i = 0; i < PduInfo.Dl; i++)
            {
                DATA[1 + i] = LinTp_LocalConfig->LinTpGlobalConfig_0->LinTpTxNSdu_0[0].LinTpTxNSduPduRef[i];
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
            for (int i = 0; i < 6; i++)
            {
                DATA[i + 2] = LinTp_LocalConfig->LinTpGlobalConfig_0->LinTpTxNSdu_0[0].LinTpTxNSduPduRef[i];
            }
            PduInfo.SduDataPtr = DATA;
        }
        Lin_SendFrame(LinTp_LocalConfig->LinTpGlobalConfig_0->LinTpTxNSdu_0[0].LinTpTxNSduChannelRef, &PduInfo);
        LinTpSubState[0] = LINTP_CHANNEL_IDLE;
    }
}

void LinTp_Shutdown(void)
{
}
