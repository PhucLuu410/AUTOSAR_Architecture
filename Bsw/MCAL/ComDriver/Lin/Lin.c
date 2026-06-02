#include "Lin_Cfg.h"
#include "Lin_GeneralTypes.h"
#include "Lin.h"
#include "stm32f103xb.h"

#define LIN_UNINIT 0x00
#define LIN_INIT 0x01

static const Lin_ConfigType *Lin_Local_Config;
static USART_TypeDef *Lin_Hardware[NUMBER_OF_LIN_CHANNEL] = {USART1, USART2};
Lin_StatusType Lin_ChannelStatus[NUMBER_OF_LIN_CHANNEL];
static uint8 Lin_StateMachine[NUMBER_OF_LIN_CHANNEL] = {LIN_UNINIT};

void Lin_Init(const Lin_ConfigType *Config)
{
    if (Config == NULL_PTR)
    {
        return;
    }
    Lin_Local_Config = Config;
    Lin_Hardware[Config->LinChannel->LinChannel]->CR1 = ((Config->LinHardware->LinRx << 2) | (Config->LinHardware->LinTx << 3) | (Config->LinHardware->LinUartEn << 13));
    Lin_Hardware[Config->LinChannel->LinChannel]->CR2 = ((Config->LinHardware->LinEn << 14) | (Config->LinChannel->LinBreakDetect << 6));
    Lin_Hardware[Config->LinChannel->LinChannel]->BRR = 8000000 / Config->LinChannel->LinBaud;
    Lin_Hardware[Config->LinChannel->LinChannel]->CR1 &= ~(1 << 7);
    Lin_Hardware[Config->LinChannel->LinChannel]->CR1 &= ~(1 << 6);
    Lin_Hardware[Config->LinChannel->LinChannel]->CR1 |= (1 << 5);
    Lin_Hardware[Config->LinChannel->LinChannel]->CR2 |= (1 << 6);
    if (Config->LinChannel->LinChannel == LIN_CHANNEL_1)
    {
        NVIC_EnableIRQ(USART1_IRQn);
    }
    if (Config->LinChannel->LinChannel == LIN_CHANNEL_2)
    {
        NVIC_EnableIRQ(USART2_IRQn);
    }
    Lin_StateMachine[Config->LinChannel->LinChannel] = LIN_INIT;
    Lin_ChannelStatus[Config->LinChannel->LinChannel] = LIN_CH_SLEEP;
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

    static uint32 Lin_Cs = 0;
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

    Lin_Hardware[Channel]->DR = PduInfoPtr->Dl;
    while (!(Lin_Hardware[Channel]->SR & (1 << 7)))
        ;

    Lin_Hardware[Channel]->DR = PduInfoPtr->CsModel;
    while (!(Lin_Hardware[Channel]->SR & (1 << 7)))
        ;

    Lin_Hardware[Channel]->DR = PduInfoPtr->Response;
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

    if (Lin_Local_Config->LinChannel->LinMasterSlave != LIN_MASTER)
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

    if (Lin_Local_Config->LinChannel->LinMasterSlave != LIN_MASTER)
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

    __disable_irq();

    *Lin_SduPtr = Lin_RxPdu[Channel].SduDataPtr;

    Lin_StatusType status = Lin_ChannelStatus[Channel];

    __enable_irq();

    return status;
}

void USART1_IRQHandler(void)
{
    if (Lin_StateMachine[LIN_CHANNEL_1] == LIN_UNINIT)
    {
        return;
    }

    static uint8 index = 0;
    static uint8 SyncFlag = 0;
    static uint8 CurrentPdu = 0;

    if (Lin_Hardware[LIN_CHANNEL_1]->SR & (1 << 8))
    {
        Lin_Hardware[LIN_CHANNEL_1]->SR &= ~(1 << 8);
        if (SyncFlag == 0)
        {
            SyncFlag = 1;
        }
        return;
    }

    if (Lin_Hardware[LIN_CHANNEL_1]->SR & (1 << 5))
    {
        volatile uint8 Data = Lin_Hardware[LIN_CHANNEL_1]->DR;
        if (Data == 0x55)
        {
            SyncFlag = 2;
            return;
        }

        if (SyncFlag == 2)
        {
            switch (Data)
            {
            case 0x12:
                CurrentPdu = Lin_ElectronicWindow;
                SyncFlag = 3;
                return;
            }
        }

        if (SyncFlag == 3)
        {
            Lin_RxPdu[CurrentPdu].Dl = Data;
            SyncFlag = 4;
            return;
        }
        if (SyncFlag == 4)
        {
            Lin_RxPdu[CurrentPdu].CsModel = Data;
            SyncFlag = 5;
            return;
        }
        if (SyncFlag == 5)
        {
            Lin_RxPdu[CurrentPdu].Response = Data;
            SyncFlag = 6;
            return;
        }
        if (SyncFlag == 6)
        {
            Lin_RxPdu[CurrentPdu].SduDataPtr[(index++)] = Data;
            if (index == Lin_RxPdu[CurrentPdu].Dl)
            {
                SyncFlag = 7;
            }
            return;
        }
        if (SyncFlag == 7)
        {
            Lin_RxPdu[CurrentPdu].Crc = Data;
            index = 0;
            SyncFlag = 0;
            Lin_ChannelStatus[LIN_CHANNEL_1] = LIN_RX_OK;
            return;
        }
        else
        {
            index = 0;
            SyncFlag = 0;
            Lin_ChannelStatus[LIN_CHANNEL_1] = LIN_RX_ERROR;
            return;
        }
    }
}
