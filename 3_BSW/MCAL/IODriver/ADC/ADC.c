#include "Adc.h"

static Adc_GroupDefType Adc_Group_Count[8];

void Adc_Init(const Adc_ConfigType *ConfigPtr)
{
    ADC1->SQR1 |= ((NUMBER_OF_CHANNELS - 1) << 20);
    ADC1->CR2 |= (ConfigPtr->GroupConvMode << 1);
    ADC1->CR2 |= (ConfigPtr->ResultAlignment << 11);
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

        for (int j = 0; j < 8; j++)
        {
            if (j == ConfigPtr[i].GroupNums)
            {
                Adc_Group_Count[j]++;
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
    DMA1_Channel1->CMAR = (uint32_t)DataBufferPtr;
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

    return E_OK;
}