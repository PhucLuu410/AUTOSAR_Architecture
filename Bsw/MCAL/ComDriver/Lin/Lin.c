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
    Lin_Local_Config = Config;
    Lin_Hardware[Config->LinChannel->LinChannel]->CR1 = ((Config->LinHardware->LinRx << 2) | (Config->LinHardware->LinTx << 3) | (Config->LinHardware->LinUartEn << 13));
    Lin_Hardware[Config->LinChannel->LinChannel]->CR2 = ((Config->LinHardware->LinEn << 14) | (Config->LinChannel->LinBreakDetect << 6));
    Lin_Hardware[Config->LinChannel->LinChannel]->BRR = 8000000 / Config->LinChannel->LinBaud;
    Lin_Hardware[Config->LinChannel->LinChannel]->CR1 &= ~(1 << 7);
    Lin_Hardware[Config->LinChannel->LinChannel]->CR1 |= (1 << 6);
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
        return E_NOT_OK;
    }
    if (Channel >= NUMBER_OF_LIN_CHANNEL)
    {
        return E_NOT_OK;
    }
    if (Lin_ChannelStatus[Channel] != LIN_CH_SLEEP)
    {
        return E_OK;
    }
    else
    {
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
    if (Lin_ChannelStatus[Channel] != LIN_OPERATIONAL)
    {
        return E_NOT_OK;
    }
    if (PduInfoPtr == NULL_PTR)
    {
        return E_NOT_OK;
    }

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

    if (Lin_Hardware[Channel]->CR1 & (1 << 0))
    {
        Lin_Hardware[Channel]->CR1 |= (1 << 0);
    }
    if (Lin_Hardware[Channel]->SR & (1 << 7))
    {
        Lin_Hardware[Channel]->DR = 0x55;
    }
    if (Lin_Hardware[Channel]->SR & (1 << 7))
    {
        Lin_Hardware[Channel]->DR = PduInfoPtr->Pid;
    }
    if (Lin_Hardware[Channel]->SR & (1 << 7))
    {
        Lin_Hardware[Channel]->DR = PduInfoPtr->Dl;
    }
    if (Lin_Hardware[Channel]->SR & (1 << 7))
    {
        Lin_Hardware[Channel]->DR = PduInfoPtr->CsModel;
    }
    if (Lin_Hardware[Channel]->SR & (1 << 7))
    {
        Lin_Hardware[Channel]->DR = PduInfoPtr->Response;
    }
    if (Lin_Hardware[Channel]->SR & (1 << 7))
    {
        Lin_Hardware[Channel]->DR = PduInfoPtr->Pid;
    }
    if (Lin_Hardware[Channel]->SR & (1 << 7))
    {
        Lin_Hardware[Channel]->DR = Lin_Cs;
    }

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
    Lin_ChannelStatus[Channel] = LIN_CH_SLEEP;
    return E_OK;
}

// Lin nen set thanh Sleep va cho wake up boi external wake-up hay bien LinChannelWakeupSupport
// LIN_CH_OPERATIONAL -> LIN_CH_SLEEP_PENDING sau khi nhan duoc lenh ngu tren bus
// Lin-GetStatus duoc goi nen vao LIN_CH_SLEEP tru khi lenh Go to sleep chua duoc goi chi dung cho master node
// LIN_CH_OPERATIONAL -> LIN_CH_SLEEP thong qua Lin_GotoSleep day Lin vao trang thai LIN_CH_SLEEP
// LIN_CH_SLEEP -> LIN_CH_OPERATIONAL thong qua  Lin_Wakeup va  Lin_WakeupInternal
// neu tu LIN_CH_SLEEP -> LIN_CH_OPERATIONAL tao wake-up Request từ 250uS den 5ms

// Lin Frame : Lin Header va Lin Response
// Lin Header luon luon duoc truyen boi master va la start of frame bao gom Lin PID
// Lin Response xuat hien sau truoc truyen boi ca 2 la Header va Response
// Du lieu day vao buffer Can Driver gom data va check sum Lin 1.3 khong duoc su dung voi Lin 2.0 tro len
// Lin Id 0x60 va 0x63 Dung classic checksum model
// Lin Master Gui header kem Drc
// Neu Drc la Tx thi Lin Response truyen sau header luon
// Neu Drc la Rx thi Lin Response truyen sau header tu Slave

// Master
// Lin_SendFrame
// Gui Lin header gom Break Sync va PID protect
// Lin getStatus return transmit status
// Slave
// co the nhan luc nao cung duoc neu o trang thai LIN_CH_OPERATIONAL
// Khi nhan Header thi call LinIf_HeaderIndication
// Neu gui loi thi call LinIf_LinErrorIndication voi LIN_ERR_HEADER
// Sau khi goi LinIf_HeaderIndication return E_OK
// Sau khi gui lai check LinIf_TxConfirmation
// Neu trong luc truyen co loi goi LinIf_LinErrorIndication
// Neu co loi goi dong thoi LinIf_RxIndication, LinIf_TxConfirmation or LinIf_LinErrorIndication tre nhat la den khi header tiep theo
// Common
// Neu khong ho tro buffer thi tao buffer
// Nhat quan data
// Transmit
// Copy data len tang tren
// Master phai giu data cho den khi return funtion
// Slave phai giu data den khi xong transmition
// Receive
// De trong buffer increase
// Du lieu phai giu nguyen khong ISR giua chung
