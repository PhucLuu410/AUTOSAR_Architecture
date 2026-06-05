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
    //---------------------------------------------------------------------------------------------------------
    // Slave
    for (int i = 0; i < 2; i++)
    {
        if (Channel == LinTp_LocalConfig->LinTpGlobalConfig_0->LinTpRxNSdu_0[0].LinTpRxNSduChannelRef)
        {
            for (int j = 0; j < 2; j++)
            {
                if (Lin_SduPtr[0] == LinTp_LocalConfig->LinTpGlobalConfig_0->LinTpRxNSdu_0[0].LinTpRxNSduNad)
                {
                    uint8 LENGTH = ((Lin_SduPtr[1] && 0x0F) >> 4 | Lin_SduPtr[2] & 0x0FF);
                    uint8 LinTpRxBuffer[LENGTH];
                    for (int a = 0; a < LENGTH; a++)
                    {
                        LinTpRxBuffer[a] = 0xFF;
                    }
                    if (LENGTH <= 4)
                    {
                        for (int a = 0; a < LENGTH; a++)
                        {
                            LinTpRxBuffer[a] = Lin_SduPtr[a + 3];
                        }
                    }
                    else
                    {
                        for (int a = 0; a < 4; a++)
                        {
                            LinTpRxBuffer[a] = Lin_SduPtr[a + 3];
                        }
                        Lin_PduType LocalPduInfo;
                        LocalPduInfo.Pid = Lin_SduPtr[0];
                        LocalPduInfo.Dl = 7;
                        LocalPduInfo.CsModel = CLASSIC;
                        LocalPduInfo.Response = LIN_FRAMERESPONSE_TX;
                        LocalPduInfo.SduDataPtr = (uint8[]){Lin_SduPtr[0], 0x30, 0x08, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
                        Lin_SendFrame(LIN_CHANNEL_1, &LocalPduInfo);
                    }
                }
            }
        }
    }

    // Master
    // for (int i = 0; i < 2; i++)
    // {
    //     if (Channel == LinTp_LocalConfig->LinTpGlobalConfig_0->LinTpTxNSdu_0[i].LinTpTxNSduChannelRef)
    //     {
    //         for (int j = 0; j < 2; j++)
    //         {
    //             if (Lin_SduPtr[0] == LinTp_LocalConfig->LinTpGlobalConfig_0->LinTpTxNSdu_0[i].LinTpTxNSduId)
    //             {
    //                 if (Lin_SduPtr[1] == 0x30)
    //                     LinTpMasterState = 0;
    //             }
    //         }
    //     }
    // }
}

//---------------------------------------------------------------------------------------------------------
void LinTp_Init(const LinTp_ConfigType *ConfigPtr)
{
    if (ConfigPtr != NULL_PTR)
        LinTp_LocalConfig = ConfigPtr;
}

Std_ReturnType LinTp_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr)
{
    // Master
    // for (int i = 0; i < 2; i++)
    // {
    //     if (TxPduId == LinTp_LocalConfig->LinTpGlobalConfig_0->LinTpTxNSdu_0[i].LinTpTxNSduId)
    //     {
    //         uint16 current_length = PduInfoPtr->SduLength;
    //         Lin_PduType LocalPduInfo;
    //         LocalPduInfo.Pid = LinTp_LocalConfig->LinTpGlobalConfig_0->LinTpTxNSdu_0[i].LinTpTxNSduNad;
    //         if (current_length > 4)
    //         {
    //             LocalPduInfo.Dl = 7;
    //             LocalPduInfo.CsModel = CLASSIC;
    //             LocalPduInfo.Response = LIN_FRAMERESPONSE_TX;
    //             uint8 PCI = 0x10 | ((current_length & 0x0F00) >> 8);
    //             uint8 LENGTH = current_length & 0xFF;
    //             static uint8 FF[7] = {0};
    //             FF[0] = PCI;
    //             FF[1] = LENGTH;
    //             for (int a = 0; a <= LocalPduInfo.Dl - 3; a++)
    //             {
    //                 FF[a + 2] = PduInfoPtr->SduDataPtr[a];
    //             }
    //             LocalPduInfo.SduDataPtr = FF;
    //             for (int c = 0; c < 1; c++) //
    //             {
    //                 if (LinTpMasterState == 0)
    //                 {
    //                     Lin_SendFrame(LinTp_LocalConfig->LinTpGlobalConfig_0->LinTpTxNSdu_0[i].LinTpTxNSduChannelRef, &LocalPduInfo);
    //                 }
    //                 LinTpMasterState = 1;
    //                 // while (LinTpMasterState != 1)
    //                 // {
    //                 //     break;
    //                 // }
    //             }
    //         }
    //         else
    //         {
    //             LocalPduInfo.Dl = 7;
    //             LocalPduInfo.CsModel = CLASSIC;
    //             LocalPduInfo.Response = LIN_FRAMERESPONSE_TX;
    //             uint8 PCI = 0x10 | ((current_length & 0x0F00) >> 8);
    //             uint8 LENGTH = current_length & 0xFF;
    //             static uint8 SF[7] = {0};
    //             SF[0] = PCI;
    //             SF[1] = LENGTH;
    //             for (int a = 0; a < current_length; a++)
    //             {
    //                 SF[a + 2] = PduInfoPtr->SduDataPtr[a];
    //             }
    //             uint8 total_length = current_length + 3;
    //             while (total_length < 7)
    //             {
    //                 SF[total_length] = 0;
    //                 total_length++;
    //             }
    //             LocalPduInfo.SduDataPtr = SF;
    //             Lin_SendFrame(LinTp_LocalConfig->LinTpGlobalConfig_0->LinTpTxNSdu_0[i].LinTpTxNSduChannelRef, &LocalPduInfo);
    //         }
    //     }
    // }

    // Slave

    return E_OK;
}

void LinTp_Shutdown(void)
{
}

Std_ReturnType LinTp_ChangeParameter(PduIdType id, TPParameterType parameter, uint16 value)
{
}