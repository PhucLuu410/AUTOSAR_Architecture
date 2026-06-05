#include "LinIf.h"
#include "LinIf_Cfg.h"
#include "stm32f103xb.h"
#include "Std_Types.h"

static const LinIf_ConfigType *LinIf_LocalConfig;
static const LinTp_ConfigType *LinTp_LocalConfig;

const uint8 *LinDriverData;
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
                    PduInfo.SduDataPtr = Lin_SduPtr + 1;
                    PduInfo.SduLength = 8;
                    PduR_RxIndication(LinIf_LocalConfig->LinIfGlobalConfig_0->LinIfChannel_0[i].LinIfComMNetworkHandleRef_0, &PduInfo);
                    break;
                }
            }
        }
    }
}

void LinTp_Init(const LinTp_ConfigType *ConfigPtr)
{
}
Std_ReturnType LinTp_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr)
{
}
void LinTp_Shutdown(void)
{
}
Std_ReturnType LinTp_ChangeParameter(PduIdType id, TPParameterType parameter, uint16 value)
{
}