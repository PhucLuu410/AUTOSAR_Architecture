#include "Mcu.h"
#include "Mcu_Cfg.h"

MCU_PrehiralConfigType PrehiralConfig = {
    MCU_PREHIRAL_AHB,
    MCU_PREHIRAL_APB2,
    MCU_PREHIRAL_APB1};

Mcu_ClockConfigType Mcu_Clock_Configuration = {
    MCU_HSE_CLOCK_CRYSTAL,
    MCU_AHB_PRESCALE_1,
    MCU_APB2_PRESCALE_1,
    MCU_APB1_PRESCALE_1,
    &PrehiralConfig};

Mcu_ConfigType Mcu_Configuration[] = {
    {&Mcu_Clock_Configuration,
     NULL_PTR}};