#include "Dio.h"
#include "Dio_Cfg.h"
#include "Port.h"
#include "Port_Cfg.h"
#include "Pwm.h"
#include "Pwm_Cfg.h"
#include "Adc/Adc.h"
#include "Adc/Adc_Cfg.h"
#include "Mcu.h"
#include "Mcu_Cfg.h"
#include "IoHwAb.h"
#include "IoHwAb_Cfg.h"
#include "Can.h"
#include "Can_Cfg.h"
#include "CanIf.h"
#include "CanIf_Cfg.h"
#include "PduR.h"
#include "PduR_Cfg.h"

uint8 buffer[8];

PduInfoType info = {
    .SduDataPtr = buffer,
    .SduLength = 8,
};

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
    Can_EnableControllerInterrupts(CAN_1);
    Can_SetBaudrate(CAN_1, 0);
    Can_SetControllerMode(CAN_1, CAN_CS_STARTED);
    CanIf_Init(&CanIfConfig);
    PduR_Init(&PduR_GlobalConfig);
    while (1)
    {
        CanIf_Transmit(SENSOR_0, &CanIfTxPduInfo[SENSOR_0]);
        delay(100000);
        CanIf_Transmit(SENSOR_1, &CanIfTxPduInfo[SENSOR_1]);
        delay(100000);
        CanIf_Transmit(SENSOR_2, &CanIfTxPduInfo[SENSOR_2]);
    }
}

void HardFault_Handler(void)
{
    while (1)
        ;
}