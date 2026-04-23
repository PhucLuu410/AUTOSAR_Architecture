#include "Adc.h"
#include <stdlib.h>
#include "stm32f103xb.h"

static ADC_TypeDef *ADC[] = {ADC1, ADC2};
const static Adc_ConfigType *InternalUseConfigPtr;
static Adc_ValueGroupType Adc_BufferGroupValue[NUMBER_CHANNELS_OF_GROUP0 +
                                               NUMBER_CHANNELS_OF_GROUP1 +
                                               NUMBER_CHANNELS_OF_GROUP2 +
                                               NUMBER_CHANNELS_OF_GROUP3 +
                                               NUMBER_CHANNELS_OF_GROUP4 +
                                               NUMBER_CHANNELS_OF_GROUP5 +
                                               NUMBER_CHANNELS_OF_GROUP6 +
                                               NUMBER_CHANNELS_OF_GROUP7] = {0};

void Adc_Init(const Adc_ConfigType *ConfigPtr)
{
    ADC[ConfigPtr->CommonConfig->AdcNumber]->CR2 = 0;
    ADC[ConfigPtr->CommonConfig->AdcNumber]->CR1 = 0;
    RCC->CFGR |= ConfigPtr->CommonConfig->Prescale << 14;
    ADC[ConfigPtr->CommonConfig->AdcNumber]->CR2 |= ConfigPtr->CommonConfig->Adc_ResultAlignment << 11;
    ADC[ConfigPtr->CommonConfig->AdcNumber]->CR2 |= (ConfigPtr->CommonConfig->DMAEnable << 8); // DMA MODE
    ADC[ConfigPtr->CommonConfig->AdcNumber]->CR1 |= (ConfigPtr->CommonConfig->ScanDMA << 8);   // SCAN MODE
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
    if (DataBufferPtr == NULL)
        return E_NOT_OK;
    switch (Group)
    {
    case ADC_GROUP_0:
        DataBufferPtr = &Adc_BufferGroupValue[0];
        break;
    case ADC_GROUP_1:
        DataBufferPtr = &Adc_BufferGroupValue[NUMBER_CHANNELS_OF_GROUP0];
        break;
    case ADC_GROUP_2:
        DataBufferPtr = &Adc_BufferGroupValue[NUMBER_CHANNELS_OF_GROUP0 +
                                              NUMBER_CHANNELS_OF_GROUP1];
        break;
    case ADC_GROUP_3:
        DataBufferPtr = &Adc_BufferGroupValue[NUMBER_CHANNELS_OF_GROUP0 +
                                              NUMBER_CHANNELS_OF_GROUP1 +
                                              NUMBER_CHANNELS_OF_GROUP2];
        break;
    case ADC_GROUP_4:
        DataBufferPtr = &Adc_BufferGroupValue[NUMBER_CHANNELS_OF_GROUP0 +
                                              NUMBER_CHANNELS_OF_GROUP1 +
                                              NUMBER_CHANNELS_OF_GROUP2 +
                                              NUMBER_CHANNELS_OF_GROUP3];
        break;
    case ADC_GROUP_5:
        DataBufferPtr = &Adc_BufferGroupValue[NUMBER_CHANNELS_OF_GROUP0 +
                                              NUMBER_CHANNELS_OF_GROUP1 +
                                              NUMBER_CHANNELS_OF_GROUP2 +
                                              NUMBER_CHANNELS_OF_GROUP3 +
                                              NUMBER_CHANNELS_OF_GROUP4];
        break;
    case ADC_GROUP_6:
        DataBufferPtr = &Adc_BufferGroupValue[NUMBER_CHANNELS_OF_GROUP0 +
                                              NUMBER_CHANNELS_OF_GROUP1 +
                                              NUMBER_CHANNELS_OF_GROUP2 +
                                              NUMBER_CHANNELS_OF_GROUP3 +
                                              NUMBER_CHANNELS_OF_GROUP4 +
                                              NUMBER_CHANNELS_OF_GROUP5];
        break;
    case ADC_GROUP_7:
        DataBufferPtr = &Adc_BufferGroupValue[NUMBER_CHANNELS_OF_GROUP0 +
                                              NUMBER_CHANNELS_OF_GROUP1 +
                                              NUMBER_CHANNELS_OF_GROUP2 +
                                              NUMBER_CHANNELS_OF_GROUP3 +
                                              NUMBER_CHANNELS_OF_GROUP4 +
                                              NUMBER_CHANNELS_OF_GROUP5 +
                                              NUMBER_CHANNELS_OF_GROUP6];
        break;
    default:
        return E_NOT_OK;
    }
    return E_OK;
}

void Adc_StartGroupConversion(Adc_GroupType Group)
{
    for (int i = 0; i < NUMBER_OF_GROUPS; i++)
    {
        if (InternalUseConfigPtr[i].GroupNums == Group)
        {
            ADC[InternalUseConfigPtr[i].CommonConfig->AdcNumber]->CR2 |= (InternalUseConfigPtr[i].HwTriggerTimer) << 17;
            ADC[InternalUseConfigPtr[i].CommonConfig->AdcNumber]->CR2 |= (InternalUseConfigPtr[i].HwTriggerTimer) << 17;
            ADC[InternalUseConfigPtr[i].CommonConfig->AdcNumber]->CR2 |= (InternalUseConfigPtr[i].GroupConvMode) << 1;
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
            ADC[InternalUseConfigPtr[i].CommonConfig->AdcNumber]->CR2 |= (1 << 0);
            ADC[InternalUseConfigPtr[i].CommonConfig->AdcNumber]->CR2 |= (1 << 2);
            ADC[InternalUseConfigPtr[i].CommonConfig->AdcNumber]->CR2 |= (1 << 3);
            ADC[InternalUseConfigPtr[i].CommonConfig->AdcNumber]->CR2 |= (1 << 0);
            ADC[InternalUseConfigPtr[i].CommonConfig->AdcNumber]->CR2 |= (1 << 22);
        }
    }
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
    if (!(InternalUseConfigPtr->CommonConfig->DMAEnable == ADC_USING_DMA))
    {

        for (int i = 0; i < NUMBER_OF_GROUPS; i++)
        {
            if (InternalUseConfigPtr[i].GroupNums == Group)
            {
                switch (Group)
                {
                case ADC_GROUP_0:
                    for (int i = 0; i < NUMBER_CHANNELS_OF_GROUP0; i++)
                    {
                        while (!(ADC1->SR & (1 << 1)))
                            ;
                        DataBufferPtr[i] = ADC1->DR;
                    }
                case ADC_GROUP_1:
                    for (int i = 0; i < NUMBER_CHANNELS_OF_GROUP1; i++)
                    {
                        while (!(ADC1->SR & (1 << 1)))
                            ;
                        DataBufferPtr[i] = ADC1->DR;
                    }
                }
            }
        }
    }
}
