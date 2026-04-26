#include "Dio.h"
#include "Dio_Cfg.h"
#include "Port.h"
#include "Port_Cfg.h"
#include "Pwm.h"
#include "Pwm_Cfg.h"
#include "ADC/Adc.h"
#include "ADC/Adc_Cfg.h"
#include "Mcu.h"
#include "Mcu_Cfg.h"
#include "Os.h"

uint32_t Count = 0;
uint16_t *adcValue;
uint16_t adcValue0[2];
uint16_t adcValue1[2];
Adc_StatusType status;

void delay(volatile uint32_t t)
{
    while (t--)
        ;
}
MCU_PrehiralConfigType PrehiralConfig = {
    MCU_PREHIRAL_AHB,
    MCU_PREHIRAL_APB2,
    MCU_PREHIRAL_APB1};

Mcu_ClockConfigType Mcu_Clock_Configuration = {
    MCU_PLL_CLOCK_HSE,
    MCU_AHB_PRESCALE_1,
    MCU_APB2_PRESCALE_1,
    MCU_APB1_PRESCALE_1,
    &PrehiralConfig};

Mcu_ConfigType Mcu_Configuration[] = {
    {&Mcu_Clock_Configuration,
     NULL_PTR}};

const Port_ConfigType Port_Configuration[] = {
    {PORT_A,
     0,
     PORT_MODE_INPUT,
     PORT_OUTPUT_SPEED_50MHz,
     PORT_CNF_ANALOG_INPUT},

    {PORT_A,
     1,
     PORT_MODE_INPUT,
     PORT_OUTPUT_SPEED_50MHz,
     PORT_CNF_ANALOG_INPUT},

    {PORT_A,
     2,
     PORT_MODE_INPUT,
     PORT_OUTPUT_SPEED_50MHz,
     PORT_CNF_ANALOG_INPUT},

    {PORT_A,
     3,
     PORT_MODE_INPUT,
     PORT_OUTPUT_SPEED_50MHz,
     PORT_CNF_ANALOG_INPUT},

    {PORT_A,
     8,
     PORT_MODE_OUTPUT,
     PORT_OUTPUT_SPEED_50MHz,
     PORT_CNF_AF_OUTPUT_PP},
    {PORT_C,
     13,
     PORT_MODE_OUTPUT,
     PORT_OUTPUT_SPEED_50MHz,
     PORT_CNF_GP_OUTPUT_PP}};

Dio_TypeConfig Dio_Configuration = {PORT_C, PIN_13};

Adc_ChannelType Adc_Group0_List[NUMBER_CHANNELS_OF_GROUP0] = {ADC_CHANNEL_0, ADC_CHANNEL_1};
Adc_ReferenceType Adc_Group0_Reference[NUMBER_CHANNELS_OF_GROUP0] = {ADC_REFERENCE_0, ADC_REFERENCE_1};

Adc_ChannelType Adc_Group1_List[NUMBER_CHANNELS_OF_GROUP0] = {ADC_CHANNEL_2, ADC_CHANNEL_3};
Adc_ReferenceType Adc_Group1_Reference[NUMBER_CHANNELS_OF_GROUP0] = {ADC_REFERENCE_0, ADC_REFERENCE_1};

Adc_CommonConfigType Adc_Common_Configuration[] = {{ADC_1, ADC_CLOCK_DIV_2, ADC_RESOLUTION_12_BIT, ADC_ALIGN_RIGHT, ADC_SCAN_MODE_ENABLE, ADC_USING_DMA}};

const Adc_ConfigType Adc_Configuration[NUMBER_OF_GROUPS] =
    {
        {Adc_Common_Configuration,
         ADC_GROUP_0,
         ADC_MODE_INDEPENDENT,
         ADC_CONV_MODE_CONTINUOUS,
         Adc_Group0_List,
         Adc_Group0_Reference,
         ADC_SAMPLING_TIME_239_5_CYCLES,
         ADC_SWTRIGGER_SWS},

        {Adc_Common_Configuration,
         ADC_GROUP_1,
         ADC_MODE_INDEPENDENT,
         ADC_CONV_MODE_CONTINUOUS,
         Adc_Group1_List,
         Adc_Group1_Reference,
         ADC_SAMPLING_TIME_239_5_CYCLES,
         ADC_SWTRIGGER_SWS}};

int main(void)
{
    Mcu_Init(&Mcu_Configuration[0]);
    Mcu_InitClock(Mcu_Configuration[0].ClockConfig->ClockSrc);

    Port_Init(Port_Configuration);

    Adc_Init(Adc_Configuration);
    Adc_SetupResultBuffer(ADC_GROUP_0, adcValue0);
    Adc_EnableGroupNotification(ADC_GROUP_0);
    Adc_StartGroupConversion(ADC_GROUP_0);
    while (1)
    {
    }
}