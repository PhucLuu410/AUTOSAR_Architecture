#include "Os.h"
#include "stm32f103xb.h"
#include "ADC/Adc.h"
#include "ADC/Adc_Cfg.h"
SystemFlagTypeDef SystemFlags = {0};

void ADC1_2_IRQHandler(void)
{
    uint32_t temp = ADC1->DR;
    SystemFlags.ADC_Flag = 1;
}