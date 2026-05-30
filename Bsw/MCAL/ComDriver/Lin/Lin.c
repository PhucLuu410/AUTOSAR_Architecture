#include "Lin.h"
#include "Lin_Cfg.h"
#include "LinIf.h"
#include "stm32f103xb.h"
#include "Det.h"

uint32 count12 = 0;

USART_TypeDef *Lin_Driver[NUMBER_OF_LIN_CHANNEL] = {USART1, USART2};

static const Lin_ConfigType *Lin_Local_Config;

void Lin_Init(const Lin_ConfigType *Config)
{
    Lin_Local_Config = Config;
    Lin_Driver[Config->LinChannel->LinChannel]->CR1 = ((Config->LinHardware->LinRx << 2) | (Config->LinHardware->LinTx << 3) | (Config->LinHardware->LinUartEn << 13));
    Lin_Driver[Config->LinChannel->LinChannel]->CR2 = ((Config->LinHardware->LinEn << 14) | (Config->LinChannel->LinBreakDetect << 6));
    Lin_Driver[Config->LinChannel->LinChannel]->BRR = 8000000 / Config->LinChannel->LinBaud;
    Lin_Driver[Config->LinChannel->LinChannel]->CR1 &= ~(1 << 7);
    Lin_Driver[Config->LinChannel->LinChannel]->CR1 &= ~(1 << 6);
    Lin_Driver[Config->LinChannel->LinChannel]->CR1 &= ~(1 << 5);
    Lin_Driver[Config->LinChannel->LinChannel]->CR2 &= ~(1 << 6);
    if (Config->LinChannel->LinChannel == LIN_CHANNEL_1)
    {
        NVIC_EnableIRQ(USART1_IRQn);
    }
    else if (Config->LinChannel->LinChannel == LIN_CHANNEL_2)
    {
        NVIC_EnableIRQ(USART2_IRQn);
    }
}

Std_ReturnType Lin_SendFrame(uint8 Channel, const Lin_PduType *PduInfoPtr)
{
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

    Lin_Driver[Channel]->CR1 |= (1 << 0);
    while (Lin_Driver[Channel]->CR1 & (1 << 0))
        ;
    Lin_Driver[Channel]->DR = 0x55;
    while (!(Lin_Driver[Channel]->SR & (1 << 7)))
        ;
    Lin_Driver[Channel]->DR = PduInfoPtr->Pid;
    while (!(Lin_Driver[Channel]->SR & (1 << 7)))
        ;
    for (int i = 0; i < PduInfoPtr->Dl; i++)
    {
        Lin_Driver[Channel]->DR = PduInfoPtr->SduDataPtr[i];
        while (!(Lin_Driver[Channel]->SR & (1 << 7)))
            ;
    }

    Lin_Driver[Channel]->DR = Lin_Cs;
    while (!(Lin_Driver[Channel]->SR & (1 << 7)))
        ;
    return E_OK;
}

Std_ReturnType Lin_WakeupInternal(uint8 Channel)
{
    if (Channel >= NUMBER_OF_LIN_CHANNEL)
    {
        return E_NOT_OK;
    }
    Lin_Driver[Channel]->CR1 |= (1 << 6);
    Lin_Driver[Channel]->CR1 |= (1 << 5);
    return E_OK;
}

Std_ReturnType Lin_GoToSleepInternal(uint8 Channel)
{
    if (Channel >= NUMBER_OF_LIN_CHANNEL)
    {
        return E_NOT_OK;
    }
    Lin_Driver[Channel]->CR1 &= ~(1 << 6);
    Lin_Driver[Channel]->CR1 &= ~(1 << 5);
    return E_OK;
}

void USART1_IRQHandler(void)
{
    if (Lin_Driver[LIN_CHANNEL_1]->SR & (1 << 6))
    {
        Lin_Driver[LIN_CHANNEL_1]->SR &= ~(1 << 6);
    }
    if (Lin_Driver[LIN_CHANNEL_1]->SR & (1 << 8))
    {
        Lin_Driver[LIN_CHANNEL_1]->SR &= ~(1 << 8);
        LinIf_RxIndication(LIN_CHANNEL_1, (uint8 *)&Lin_Driver[LIN_CHANNEL_1]->DR);
    }
    if (Lin_Driver[LIN_CHANNEL_1]->SR & (1 << 5))
    {
        LinIf_RxIndication(LIN_CHANNEL_1, (uint8 *)&Lin_Driver[LIN_CHANNEL_1]->DR);
    }
}