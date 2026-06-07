#include "Lin_Cfg.h"
#include "Lin_GeneralTypes.h"
#include "Lin.h"
#include "stm32f103xb.h"
#include "LinIf.h"

#define LIN_UNINIT 0x00
#define LIN_INIT 0x01

static const Lin_ConfigType *Lin_Local_Config;
static USART_TypeDef *Lin_Hardware[NUMBER_OF_LIN_CHANNEL] = {USART1, USART2};
Lin_StatusType Lin_ChannelStatus[NUMBER_OF_LIN_CHANNEL];
static uint8 Lin_StateMachine[NUMBER_OF_LIN_CHANNEL] = {LIN_UNINIT};
volatile uint8 DATA;

void Lin_Init(const Lin_ConfigType *Config)
{
    if (Config == NULL_PTR)
    {
        return;
    }
    Lin_Local_Config = Config;
    Lin_Hardware[Config->LinGlobalConfig_0->LinChannel_0->LinChannelId]->CR1 |= (1 << 2) | (1 << 3) | (1 << 13);
    Lin_Hardware[Config->LinGlobalConfig_0->LinChannel_0->LinChannelId]->CR2 |= (1 << 14) | (1 << 6);
    Lin_Hardware[Config->LinGlobalConfig_0->LinChannel_0->LinChannelId]->BRR = (Config->LinGlobalConfig_0->LinChannel_0->LinClockRef) / (Config->LinGlobalConfig_0->LinChannel_0->LinChannelBaudRate);
    Lin_Hardware[Config->LinGlobalConfig_0->LinChannel_0->LinChannelId]->CR1 &= ~(1 << 6);
    Lin_Hardware[Config->LinGlobalConfig_0->LinChannel_0->LinChannelId]->CR1 |= (1 << 5);
    Lin_Hardware[Config->LinGlobalConfig_0->LinChannel_0->LinChannelId]->CR2 |= (1 << 6);
    if (Config->LinGeneral_0->LinDevErrorDetect == 1)
    {
        Lin_Hardware[Config->LinGlobalConfig_0->LinChannel_0->LinChannelId]->CR3 |= (1 << 0);
    }
    else
    {
        Lin_Hardware[Config->LinGlobalConfig_0->LinChannel_0->LinChannelId]->CR3 &= ~(1 << 0);
    }
    if (Config->LinGlobalConfig_0->LinChannel_0->LinChannelId == LIN_CHANNEL_1)
    {
        volatile uint8_t dummy = Lin_Hardware[LIN_CHANNEL_1]->DR;
        (void)dummy;
        NVIC_EnableIRQ(USART1_IRQn);
        NVIC_SetPriority(USART1_IRQn, 0);
    }
    if (Config->LinGlobalConfig_0->LinChannel_0->LinChannelId == LIN_CHANNEL_2)
    {
        volatile uint8_t dummy = Lin_Hardware[LIN_CHANNEL_2]->DR;
        (void)dummy;
        NVIC_EnableIRQ(USART2_IRQn);
        NVIC_SetPriority(USART2_IRQn, 2);
    }
    Lin_StateMachine[Config->LinGlobalConfig_0->LinChannel_0->LinChannelId] = LIN_INIT;
    Lin_ChannelStatus[Config->LinGlobalConfig_0->LinChannel_0->LinChannelId] = LIN_CH_SLEEP;
}

Std_ReturnType Lin_CheckWakeup(uint8 Channel)
{
    if (Lin_StateMachine[Channel] != LIN_INIT)
    {
        Lin_ChannelStatus[Channel] = LIN_NOT_OK;
        return E_NOT_OK;
    }
    if (Channel >= NUMBER_OF_LIN_CHANNEL)
    {
        Lin_ChannelStatus[Channel] = LIN_NOT_OK;
        return E_NOT_OK;
    }
    if (Lin_ChannelStatus[Channel] != LIN_CH_SLEEP)
    {
        return E_OK;
    }
    else
    {
        Lin_ChannelStatus[Channel] = LIN_NOT_OK;
        return E_NOT_OK;
    }
}

Std_ReturnType Lin_SendFrame(uint8 Channel, const Lin_PduType *PduInfoPtr)
{
    if (Lin_StateMachine[Channel] != LIN_INIT)
    {
        return E_NOT_OK;
    }
    if (Channel >= NUMBER_OF_LIN_CHANNEL)
    {
        return E_NOT_OK;
    }
    if (PduInfoPtr == NULL_PTR)
    {
        return E_NOT_OK;
    }
    Lin_ChannelStatus[Channel] = LIN_BUSY;

    uint32 Lin_Cs = 0;
    if (PduInfoPtr->CsModel == LIN_ENHANCED_CS)
    {
        Lin_Cs += PduInfoPtr->Pid;
    }
    for (int i = 0; i < PduInfoPtr->Dl; i++)
    {
        Lin_Cs += PduInfoPtr->SduDataPtr[i];
    }
    while (Lin_Cs > 0xFF)
    {
        Lin_Cs = (Lin_Cs & 0xFF) + (Lin_Cs >> 8);
    }
    Lin_Cs = ~Lin_Cs;
    Lin_Cs = (uint8)(Lin_Cs & 0xFF);

    Lin_Hardware[Channel]->CR1 |= (1 << 0);
    while (Lin_Hardware[Channel]->CR1 & (1 << 0))
        ;

    Lin_Hardware[Channel]->DR = 0x55;
    while (!(Lin_Hardware[Channel]->SR & (1 << 7)))
        ;

    Lin_Hardware[Channel]->DR = PduInfoPtr->Pid;
    while (!(Lin_Hardware[Channel]->SR & (1 << 7)))
        ;

    for (int i = 0; i < PduInfoPtr->Dl; i++)
    {
        Lin_Hardware[Channel]->DR = PduInfoPtr->SduDataPtr[i];
        while (!(Lin_Hardware[Channel]->SR & (1 << 7)))
            ;
    }

    Lin_Hardware[Channel]->DR = Lin_Cs;
    while (!(Lin_Hardware[Channel]->SR & (1 << 7)))
        ;

    Lin_ChannelStatus[Channel] = LIN_OK;
    Lin_ChannelStatus[Channel] = LIN_OPERATIONAL;
    return E_OK;
}

Std_ReturnType Lin_GoToSleep(uint8 Channel)
{
    if (Lin_StateMachine[Channel] != LIN_INIT)
    {
        return E_NOT_OK;
    }

    if (Channel >= NUMBER_OF_LIN_CHANNEL)
    {
        return E_NOT_OK;
    }

    if (Lin_Local_Config->LinGlobalConfig_0->LinChannel_0->LinNodeType != LIN_MASTER)
    {
        return E_NOT_OK;
    }
    uint8 SleepData[8] = {0};
    Lin_ChannelStatus[Channel] = LIN_BUSY;
    Lin_PduType SleepPdu;
    SleepPdu.Pid = 0x3C;
    SleepPdu.Dl = sizeof(SleepData);
    SleepPdu.CsModel = LIN_ENHANCED_CS;
    SleepPdu.Response = LIN_FRAMERESPONSE_IGNORE;
    SleepPdu.SduDataPtr = SleepData;
    Lin_SendFrame(Channel, &SleepPdu);
    Lin_ChannelStatus[Channel] = LIN_CH_SLEEP;
    return E_OK;
}

Std_ReturnType Lin_GoToSleepInternal(uint8 Channel)
{
    if (Lin_StateMachine[Channel] != LIN_INIT)
    {
        return E_NOT_OK;
    }
    if (Channel >= NUMBER_OF_LIN_CHANNEL)
    {
        return E_NOT_OK;
    }
    Lin_ChannelStatus[Channel] = LIN_CH_SLEEP;
    return E_OK;
}

Std_ReturnType Lin_Wakeup(uint8 Channel)
{
    if (Lin_StateMachine[Channel] != LIN_INIT)
    {
        return E_NOT_OK;
    }

    if (Channel >= NUMBER_OF_LIN_CHANNEL)
    {
        return E_NOT_OK;
    }

    if (Lin_Local_Config->LinGlobalConfig_0->LinChannel_0->LinNodeType != LIN_MASTER)
    {
        return E_NOT_OK;
    }

    Lin_ChannelStatus[Channel] = LIN_OPERATIONAL;
    uint8 SleepData[8] = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    Lin_ChannelStatus[Channel] = LIN_BUSY;
    Lin_PduType WakeUpPdu;
    WakeUpPdu.Pid = 0x3C;
    WakeUpPdu.Dl = sizeof(SleepData);
    WakeUpPdu.CsModel = LIN_ENHANCED_CS;
    WakeUpPdu.Response = LIN_FRAMERESPONSE_RX;
    WakeUpPdu.SduDataPtr = SleepData;
    Lin_SendFrame(Channel, &WakeUpPdu);
    return E_OK;
}

Std_ReturnType Lin_WakeupInternal(uint8 Channel)
{
    if (Lin_StateMachine[Channel] != LIN_INIT)
    {
        return E_NOT_OK;
    }
    if (Channel >= NUMBER_OF_LIN_CHANNEL)
    {
        return E_NOT_OK;
    }
    Lin_ChannelStatus[Channel] = LIN_OPERATIONAL;
    return E_OK;
}

Lin_StatusType Lin_GetStatus(uint8 Channel, const uint8 **Lin_SduPtr)
{
    if (Channel >= NUMBER_OF_LIN_CHANNEL)
    {
        return LIN_NOT_OK;
    }
    if (Lin_StateMachine[Channel] == LIN_UNINIT)
    {
        return LIN_NOT_OK;
    }

    // *Lin_SduPtr = Lin_RxData[Channel];

    Lin_StatusType status = Lin_ChannelStatus[Channel];

    return status;
}

void USART1_IRQHandler(void)
{
    if (Lin_StateMachine[LIN_CHANNEL_1] == LIN_UNINIT)
    {
        return;
    }

    static Lin_RxStateMachineType RxState = LIN_RX_IDLE;

    static uint8 TABLE_INDEX = 0;
    static uint8 DATA_INDEX = 0;

    if (Lin_Hardware[LIN_CHANNEL_1]->SR & (1 << 6))
    {
        Lin_Hardware[LIN_CHANNEL_1]->SR &= ~(1 << 6);
        volatile uint8 temp = (uint8)Lin_Hardware[LIN_CHANNEL_1]->DR;
        (void)temp;
        return;
    }

    if (Lin_Hardware[LIN_CHANNEL_1]->SR & (1 << 8))
    {
        Lin_Hardware[LIN_CHANNEL_1]->SR &= ~(1 << 8);
        if (RxState == LIN_RX_IDLE)
        {
            TABLE_INDEX = 0;
            DATA_INDEX = 0;
            RxState = LIN_RX_SYNC;
            return;
        }
    }

    if (Lin_Hardware[LIN_CHANNEL_1]->SR & (1 << 5))
    {

        DATA = *(volatile uint8_t *)&(Lin_Hardware[LIN_CHANNEL_1]->DR);
        if (DATA == 0x55 && RxState == LIN_RX_SYNC)
        {
            RxState = LIN_RX_PID;
            return;
        }

        if (RxState == LIN_RX_PID)
        {
            for (int CheckId = 0; CheckId < NUMBER_OF_LIN_PDU; CheckId++)
            {
                if (DATA == Lin_DataCfg[CheckId].Pid)
                {
                    TABLE_INDEX = CheckId;
                    DATA_INDEX = 0;
                    Lin_DataCfg[TABLE_INDEX].SduDataPtr[DATA_INDEX++] = DATA;
                    RxState = LIN_RX_DATA;
                    break;
                }
            }
            return;
        }

        if (RxState == LIN_RX_DATA)
        {
            Lin_DataCfg[TABLE_INDEX].SduDataPtr[DATA_INDEX++] = DATA;
            if (DATA_INDEX > Lin_DataCfg[TABLE_INDEX].Dl)
            {
                Lin_ChannelStatus[LIN_CHANNEL_1] = LIN_RX_OK;
                RxState = LIN_RX_CS;
            }
            return;
        }

        if (RxState == LIN_RX_CS)
        {
            uint32 Lin_Cs = 0;
            if (Lin_DataCfg[TABLE_INDEX].CsModel == LIN_ENHANCED_CS)
            {
                Lin_Cs += Lin_DataCfg[TABLE_INDEX].Pid;
            }
            for (int i = 0; i < Lin_DataCfg[TABLE_INDEX].Dl; i++)
            {
                Lin_Cs += Lin_DataCfg[TABLE_INDEX].SduDataPtr[i + 1];
            }
            while (Lin_Cs > 0xFF)
            {
                Lin_Cs = (Lin_Cs & 0xFF) + (Lin_Cs >> 8);
            }
            Lin_Cs = ~Lin_Cs;
            Lin_Cs = (uint8)(Lin_Cs & 0xFF);

            if (DATA == Lin_Cs)
            {
                // LinIf_RxIndication(LIN_CHANNEL_1, &Lin_DataCfg[TABLE_INDEX]);
                Lin_ChannelStatus[LIN_CHANNEL_1] = LIN_RX_OK;
            }
            else
            {
                Lin_ChannelStatus[LIN_CHANNEL_1] = LIN_RX_ERROR;
            }
            RxState = LIN_RX_IDLE;
        }
    }
}
