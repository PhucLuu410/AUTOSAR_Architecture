#include "LinIf.h"
#include "LinIf_Cfg.h"
#include "stm32f103xb.h"
#include "Std_Types.h"

static const LinIf_ConfigType *LinIf_LocalConfig;
static const LinTp_ConfigType *LinTp_LocalConfig;
static Lin_PduType LocalPduInfo = {
    .Pid = 0,
    .Dl = 0,
    .CsModel = 0xFF,
    .Response = 0xFF,
    .SduDataPtr = NULL_PTR,
};
const uint8 *LinDriverData;
uint8 LinDriverDataArray[9] = {0};

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
    for (int i = 0; i < sizeof(LinIfFrameConfig) / sizeof(LinIfFrameConfig[0]); i++)
    {
        if (LinIfFrameConfig[i].LocalPduId == TxPduId)
        {
            Lin_PduType LocalPdu;
            LocalPdu.Pid = LinIfFrameConfig[i].Pid;
            LocalPdu.Dl = PduInfoPtr->SduLength;
            LocalPdu.CsModel = LinIfFrameConfig[i].CsModel;
            LocalPdu.Response = LinIfFrameConfig[i].Response;
            LocalPdu.SduDataPtr = PduInfoPtr->SduDataPtr;
            Lin_SendFrame(LinIfFrameConfig[i].Channel, &LocalPdu);
            return E_OK;
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

void LinIf_MainFunction_SendHeader1(void)
{
    if ((LinIf_LocalConfig == NULL_PTR))
    {
        return;
    }
    if (LinIf_LocalConfig->LinIfGeneral_0->LinIfBusMirroringSupported == TRUE)
    {
        LocalPduInfo = HeaderPdu1;
    }
    Lin_SendFrame(LIN_CHANNEL_1, &HeaderPdu1);
}

void LinIf_MainFunction_SendHeader2(void)
{
    if ((LinIf_LocalConfig == NULL_PTR))
    {
        return;
    }
    if (LinIf_LocalConfig->LinIfGeneral_0->LinIfBusMirroringSupported == TRUE)
    {
        LocalPduInfo = HeaderPdu2;
    }
    Lin_SendFrame(LIN_CHANNEL_1, &HeaderPdu2);
}

void LinIf_MainFunction_SendHeader3(void)
{
    if ((LinIf_LocalConfig == NULL_PTR))
    {
        return;
    }
    if (LinIf_LocalConfig->LinIfGeneral_0->LinIfBusMirroringSupported == TRUE)
    {
        LocalPduInfo = HeaderPdu3;
    }
    Lin_SendFrame(LIN_CHANNEL_1, &HeaderPdu3);
}

void LinIf_MainFunction_SendData3(void)
{
    if ((LinIf_LocalConfig == NULL_PTR))
    {
        return;
    }
    if (LinIf_LocalConfig->LinIfGeneral_0->LinIfBusMirroringSupported == TRUE)
    {
        LocalPduInfo = DataPdu3;
    }
    Lin_SendFrame(LIN_CHANNEL_1, &DataPdu3);
}

void LinIf_MainFunction_ReceiveStatus(void)
{
    if ((LinIf_LocalConfig == NULL_PTR))
    {
        return;
    }
    if (Lin_GetStatus(LIN_CHANNEL_1, &LinDriverData) != LIN_RX_OK)
    {
        LinDriverData = NULL_PTR;
    }

    if (*LinDriverData == 0x20)
    {
        Lin_SendFrame(0, &DataPdu1);
        return;
    }

    if (*LinDriverData == 0x21)
    {
        Lin_SendFrame(0, &DataPdu2);
        return;
    }

    if (*LinDriverData == 0x22)
    {
        for (int i = 0; i < 8; i++)
        {
            LinDriverDataArray[i] = LinDriverData[i + 1];
        }
        Lin_SendFrame(0, &DataPdu2);
        return;
    }
}
