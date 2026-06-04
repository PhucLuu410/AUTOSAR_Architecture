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
