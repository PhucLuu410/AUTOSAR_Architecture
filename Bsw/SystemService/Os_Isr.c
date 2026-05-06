#include "Os.h"
#include "stm32f103xb.h"
#include "ADC/Adc.h"
#include "Can.h"

void ADC1_2_IRQHandler(void)
{
    SystemFlags.ADC_Flag = 1;
}

void USB_HP_CAN1_TX_IRQHandler(void)
{
    return;
}
