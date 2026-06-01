#include "Lin_Cfg.h"
#include "Lin_GeneralTypes.h"
#include "Lin.h"
#include "stm32f103xb.h"

// Lin module khong khoi tao cac Parameter khong su dung
// Lin module cung cap moi truong de thay doi config trong luc runtime
// Lin module config baudrate boi bien tinh
// Lin_ConFig type luu tren Rom va duoc khoi tao
// Lin PID phai co checksum
// Moi Lin PID phai co do dai nhat dinh

static const Lin_ConfigType *Lin_Local_Config;
static USART_TypeDef *Lin_Hardware[NUMBER_OF_LIN_CHANNEL] = {USART1, USART2};

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
