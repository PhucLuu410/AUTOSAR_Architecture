#include "Adc.h"
#include <stdlib.h>
#include "stm32f103xb.h"

static ADC_TypeDef *ADC[] = {ADC1, ADC2};
const static Adc_ConfigType *InternalUseConfigPtr;

void Adc_Init(const Adc_ConfigType *ConfigPtr)
{
    ADC[ConfigPtr->CommonConfig->AdcNumber]->CR2 = 0;
    ADC[ConfigPtr->CommonConfig->AdcNumber]->CR1 = 0;
    RCC->CFGR |= ConfigPtr->CommonConfig->Prescale << 14;
    ADC[ConfigPtr->CommonConfig->AdcNumber]->CR2 |= ConfigPtr->CommonConfig->Adc_ResultAlignment << 11;
    ADC[ConfigPtr->CommonConfig->AdcNumber]->CR2 |= (1 << 8); // DMA MODE
    ADC[ConfigPtr->CommonConfig->AdcNumber]->CR1 |= (1 << 8); // SCAN MODE
    InternalUseConfigPtr = ConfigPtr;
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

Std_ReturnType Adc_SetupResultBuffer(Adc_GroupType Group, Adc_ValueGroupType *DataBufferPtr)
{
    DMA1_Channel1->CCR &= ~(1 << 0);
    DMA1_Channel1->CMAR = (uint32_t)DataBufferPtr;
    return E_OK;
}

void Adc_StartGroupConversion(Adc_GroupType Group)
{
    for (int i = 0; i < NUMBER_OF_CHANNELS; i++)
    {
        ADC[InternalUseConfigPtr[i].CommonConfig->AdcNumber]->CR2 |= (InternalUseConfigPtr[i].HwTriggerTimer) << 17;
        if (InternalUseConfigPtr[i].GroupNums == Group)
        {
            ADC[InternalUseConfigPtr[i].CommonConfig->AdcNumber]->CR2 |= (InternalUseConfigPtr[i].HwTriggerTimer) << 17;
            ADC[InternalUseConfigPtr[i].CommonConfig->AdcNumber]->CR2 |= InternalUseConfigPtr[i].GroupConvMode << 1;
            ADC[InternalUseConfigPtr[i].CommonConfig->AdcNumber]->SQR1 |= (NUMBER_CHANNELS_OF_GROUP0 - 1) << 20;
            for (int j = 0; j < NUMBER_CHANNELS_OF_GROUP0; j++)
            {
                if (InternalUseConfigPtr[i].ChannelId[j] < 10)
                {
                    ADC[InternalUseConfigPtr[i].CommonConfig->AdcNumber]->SMPR2 |= ((InternalUseConfigPtr[i].SamplingTime) << (InternalUseConfigPtr[i].ChannelId[j] * 3));
                }
                else
                {
                    ADC[InternalUseConfigPtr[i].CommonConfig->AdcNumber]->SMPR1 |= ((InternalUseConfigPtr[i].SamplingTime) << ((InternalUseConfigPtr[i].ChannelId[j] - 10) * 3));
                }

                if (InternalUseConfigPtr[i].ChannelId[j] < 7)
                {
                    ADC[InternalUseConfigPtr[i].CommonConfig->AdcNumber]->SQR3 |= ((InternalUseConfigPtr[i].ChannelId[j]) << (InternalUseConfigPtr[i].Reference[j] * 5));
                }
                else if (InternalUseConfigPtr[i].ChannelId[j] >= 7 && InternalUseConfigPtr[i].ChannelId[j] < 13)
                {
                    ADC[InternalUseConfigPtr[i].CommonConfig->AdcNumber]->SQR2 |= ((InternalUseConfigPtr[i].SamplingTime) << ((InternalUseConfigPtr[i].ChannelId[j] - 7) * 5));
                }
                else
                {
                    ADC[InternalUseConfigPtr[i].CommonConfig->AdcNumber]->SQR1 |= ((InternalUseConfigPtr[i].SamplingTime) << ((InternalUseConfigPtr[i].ChannelId[j] - 13) * 5));
                }
            }
        }
    }
    ADC1->CR2 |= (1 << 0);
    ADC1->CR2 |= (1 << 2);
    ADC1->CR2 |= (1 << 3);
    ADC1->CR2 |= (1 << 0);
}

void Adc_StopGroupConversion(Adc_GroupType Group)
{
    ADC1->SQR1 = 0;
    ADC1->SQR2 = 0;
    ADC1->SQR3 = 0;
    ADC1->CR2 &= ~(1 << 0);
}

Std_ReturnType Adc_ReadGroup(Adc_GroupType Group, Adc_ValueGroupType *DataBufferPtr)
{
    // Adc_ValueGroupType *sourceAddr = (Adc_ValueGroupType *)DMA1_Channel1->CMAR;
    // uint8_t ChannelInGroup = 0;
    // for (int j = 0; j < 16; j++)
    // {
    //     if (Adc_Group[Group][j] != 0)
    //         ChannelInGroup++;
    // }

    // for (uint8_t i = 0; i < ChannelInGroup; i++)
    // {
    //     DataBufferPtr[i] = sourceAddr[i];
    // }

    return E_OK;
}
