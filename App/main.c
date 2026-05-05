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
#include "IoHwAb.h"
#include "IoHwAb_Cfg.h"
#include "Can.h"
#include "Can_Cfg.h"

void delay(volatile uint32_t t)
{
    while (t--)
        ;
}

int main(void)
{
    Mcu_Init(&Mcu_Configuration[0]);
    Mcu_InitClock(Mcu_Configuration[0].ClockConfig->ClockSrc);
    Port_Init(Port_Configuration);

    Can_Init(&CanConfig[0]);
    Can_SetBaudrate(CAN_1, 0);
    Can_SetControllerMode(CAN_1, CAN_CS_STARTED);
    while (1)
    {
        Can_Write(CAN_1, &Can_TxPduInfo);
    }
}
