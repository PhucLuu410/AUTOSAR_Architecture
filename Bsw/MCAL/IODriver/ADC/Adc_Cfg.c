#include "ADC/Adc.h"
#include "ADC/Adc_Cfg.h"

static Adc_ChannelType Adc_Group0_List[NUMBER_CHANNELS_OF_GROUP0] = {ADC_CHANNEL_1};
static Adc_ReferenceType Adc_Group0_Reference[NUMBER_CHANNELS_OF_GROUP0] = {ADC_REFERENCE_0};

static Adc_ChannelType Adc_Group1_List[NUMBER_CHANNELS_OF_GROUP0] = {ADC_CHANNEL_4};
static Adc_ReferenceType Adc_Group1_Reference[NUMBER_CHANNELS_OF_GROUP0] = {ADC_REFERENCE_0};

static Adc_CommonConfigType Adc_Common_Configuration[] = {{ADC_1, ADC_CLOCK_DIV_2, ADC_RESOLUTION_12_BIT, ADC_ALIGN_RIGHT, ADC_SCAN_MODE_ENABLE, ADC_USING_DMA}};

uint16 adcValue0[2];
uint16 adcValue1[2];

const Adc_ConfigType Adc_Configuration[NUMBER_OF_GROUPS] =
    {
        [ADC_VOLTAGE] = {Adc_Common_Configuration,
                         ADC_GROUP_0,
                         ADC_MODE_INDEPENDENT,
                         ADC_CONV_MODE_CONTINUOUS,
                         Adc_Group0_List,
                         Adc_Group0_Reference,
                         ADC_SAMPLING_TIME_239_5_CYCLES,
                         ADC_SWTRIGGER_SWS},
        [ADC_CURRENT] = {Adc_Common_Configuration,
                         ADC_GROUP_1,
                         ADC_MODE_INDEPENDENT,
                         ADC_CONV_MODE_CONTINUOUS,
                         Adc_Group1_List,
                         Adc_Group1_Reference,
                         ADC_SAMPLING_TIME_239_5_CYCLES,
                         ADC_SWTRIGGER_SWS}};