#define NUMBER_OF_CHANNELS 3

#include "Adc.h"

Adc_GroupConvModeType ConversionMode = ADC_CONV_MODE_CONTINUOUS;
Adc_ResultAlignmentType ResultAlignment = ADC_ALIGN_LEFT;

void Adc_Init(const Adc_ConfigType *ConfigPtr)
{
    ADC1->SQR1 |= ((NUMBER_OF_CHANNELS - 1) << 20);
    ADC1->CR2 |= ConversionMode << 1;
    ADC1->CR2 |= ResultAlignment << 11;
    ADC1->CR1 |= 1 << 8;
    ADC1->CR2 |= 1 << 8;

    for (int i = 0; i < NUMBER_OF_CHANNELS; i++)
    {
        if (ConfigPtr[i].ChannelId < 7)
        {
            ADC1->SQR3 |= (ConfigPtr[i].ChannelId << (ConfigPtr[i].Reference * 5));
        }
        else if (ConfigPtr[i].ChannelId > 7 && ConfigPtr[i].ChannelId < 13)
        {
            ADC1->SQR2 |= (ConfigPtr[i].ChannelId << (ConfigPtr[i].Reference * 5));
        }
        else
        {
            ADC1->SQR1 |= (ConfigPtr[i].ChannelId << (ConfigPtr[i].Reference * 5));
        }

        if (ConfigPtr[i].ChannelId < 10)
        {
            ADC1->SMPR2 |= (ConfigPtr[i].SamplingTime << (ConfigPtr[i].ChannelId * 3));
        }
        else
        {
            ADC1->SMPR1 |= (ConfigPtr[i].SamplingTime << ((ConfigPtr[i].ChannelId - 10) * 3));
        }
    }
    ADC1->CR2 |= (1 << 0);
    ADC1->CR2 |= (1 << 2);
    ADC1->CR2 |= (1 << 3);
    ADC1->CR2 |= (1 << 0);
}

Std_ReturnType Adc_SetupResultBuffer(Adc_GroupType Group, Adc_ValueGroupType *DataBufferPtr)
{
    DMA1_Channel1->CCR = 0;
    DMA1_Channel1->CCR |= (1 << 5);
    DMA1_Channel1->CCR |= (1 << 7);
    DMA1_Channel1->CCR |= (1 << 8);
    DMA1_Channel1->CCR |= (1 << 10);
    DMA1_Channel1->CCR |= (1 << 12);
    DMA1_Channel1->CNDTR = 3;
    DMA1_Channel1->CPAR = (uint32_t)&ADC1->DR;
    DMA1_Channel1->CMAR = (uint32_t)DataBufferPtr;
    DMA1_Channel1->CCR |= (1 << 0);
    ADC1->CR2 |= (1 << 0);
    ADC1->CR2 |= (1 << 22);
    while (ADC1->SR & (1 << 1))
        ;
    return E_OK;
}