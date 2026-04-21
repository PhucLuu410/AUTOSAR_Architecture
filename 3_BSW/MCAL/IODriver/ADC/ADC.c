#include "Adc.h"

static Adc_GroupDefType Adc_Group[8][16] = {0};

void Adc_Init(const Adc_ConfigType *ConfigPtr)
{
    ADC1->CR2 |= (ConfigPtr->GroupConvMode << 1);
    ADC1->CR2 |= (ConfigPtr->ResultAlignment << 11);
    ADC1->CR1 |= 1 << 8;
    ADC1->CR2 |= 1 << 8;
    ADC1->CR2 |= 7 << 17;

    for (int i = 0; i < NUMBER_OF_CHANNELS; i++)
    {
        if (ConfigPtr[i].ChannelId < 10)
        {
            ADC1->SMPR2 |= (ConfigPtr[i].SamplingTime << (ConfigPtr[i].ChannelId * 3));
        }
        else
        {
            ADC1->SMPR1 |= (ConfigPtr[i].SamplingTime << ((ConfigPtr[i].ChannelId - 10) * 3));
        }

        for (int j = 0; j < 8; j++)
        {
            if (j == ConfigPtr[i].GroupNums)
            {
                Adc_Group[j][i] = ConfigPtr[i].ChannelId + 1;
                break;
            }
        }
    }

    ADC1->CR2 |= (1 << 0);
    ADC1->CR2 |= (1 << 2);
    ADC1->CR2 |= (1 << 3);
    ADC1->CR2 |= (1 << 0);
}

Std_ReturnType Adc_SetupResultBuffer(Adc_GroupType Group, Adc_ValueGroupType *DataBufferPtr)
{
    DMA1_Channel1->CCR &= ~(1 << 0);
    DMA1_Channel1->CMAR = (uint32_t)DataBufferPtr;
    DMA1_Channel1->CCR |= (1 << 0);
    return E_OK;
}

void Adc_DeInit(void)
{
    ADC1->CR1 = 0;
    ADC1->CR2 = 0;
    ADC1->SMPR1 = 0;
    ADC1->SMPR2 = 0;
    ADC1->SQR1 = 0;
    ADC1->SQR2 = 0;
    ADC1->SQR3 = 0;
}

void Adc_StartGroupConversion(Adc_GroupType Group)
{
    uint8_t ChannelInGroup = 0;
    for (int j = 0; j < 16; j++)
    {
        if (Adc_Group[Group][j] != 0)
        {
            if ((Adc_Group[Group][j] - 1) < 7)
            {
                ADC1->SQR3 |= ((Adc_Group[Group][j] - 1) << (ChannelInGroup * 5));
            }
            else if ((Adc_Group[Group][j] - 1) > 7 && (Adc_Group[Group][j] - 1) < 13)
            {
                ADC1->SQR2 |= ((Adc_Group[Group][j] - 1) << ((ChannelInGroup - 6) * 5));
            }
            else
            {
                ADC1->SQR1 |= ((Adc_Group[Group][j] - 1) << ((ChannelInGroup - 12) * 5));
            }
            ChannelInGroup++;
        }
    }
    ADC1->SQR1 |= ((ChannelInGroup - 1) << 20);
    ADC1->CR2 |= (1 << 0);
    ADC1->CR2 |= (1 << 22);
}

void Adc_StopGroupConversion(Adc_GroupType Group)
{
    ADC1->SQR1 = 0;
    ADC1->SQR2 = 0;
    ADC1->SQR3 = 0;
    ADC1->CR2 &= ~(1 << 0);
}
