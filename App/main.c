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

static uint8 CanIfSensor1TxDataBuffer[8] = {0x08, 0x01, 0x04, 0x04, 0x05, 0x06, 0x07, 0x08};
static uint8 CanIfSensor2TxDataBuffer[8] = {0x00, 0x04, 0x04, 0x04, 0x05, 0x06, 0x07, 0x08};
static uint8 CanIfSensor3TxDataBuffer[8] = {0x01, 0x02, 0x04, 0x04, 0x05, 0x06, 0x07, 0x08};

PduInfoType CanIfTx1PduInfo = {
    .SduDataPtr = CanIfSensor1TxDataBuffer,
    .SduLength = 8,
};
PduInfoType CanIfTx2PduInfo = {
    .SduDataPtr = CanIfSensor2TxDataBuffer,
    .SduLength = 8,
};
PduInfoType CanIfTx3PduInfo = {
    .SduDataPtr = CanIfSensor3TxDataBuffer,
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
    PduR_Init(&PduR_PBConfig);
    while (1)
    {

        // PduR_ComTransmit(SENSOR_0, &CanIfTx1PduInfo);
        // delay(1000000);
        // PduR_ComTransmit(SENSOR_1, &CanIfTx2PduInfo);
        // delay(1000000);
        // PduR_ComTransmit(SENSOR_2, &CanIfTx3PduInfo);
        // delay(1000000);
    }
}

void HardFault_Handler(void)
{
    while (1)
        ;
}