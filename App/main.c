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
#include "Os.h"
#include "IoHwAb.h"
#include "IoHwAb_Cfg.h"
#include "Can.h"
#include "Can_Cfg.h"
#include "CanIf.h"
#include "CanIf_Cfg.h"
typedef struct
{
    uint32_t id;
    uint8_t len;
    uint8_t data[8];
} Can_RxMessageType;

Can_RxMessageType RxMsg;

void Can_Read(Can_RxMessageType *RxMsg)
{
    if ((CAN1->RF0R & 0x3) == 0)
        return;
    GPIOC->BSRR = (1 << 13);
    RxMsg->id = (CAN1->sFIFOMailBox[0].RIR >> 21) & 0x7FF;
    RxMsg->len = (CAN1->sFIFOMailBox[0].RDTR) & 0xF;
    RxMsg->data[0] = CAN1->sFIFOMailBox[0].RDLR & 0xFF;
    RxMsg->data[1] = (CAN1->sFIFOMailBox[0].RDLR >> 8) & 0xFF;
    RxMsg->data[2] = (CAN1->sFIFOMailBox[0].RDLR >> 16) & 0xFF;
    RxMsg->data[3] = (CAN1->sFIFOMailBox[0].RDLR >> 24) & 0xFF;
    RxMsg->data[4] = CAN1->sFIFOMailBox[0].RDHR & 0xFF;
    RxMsg->data[5] = (CAN1->sFIFOMailBox[0].RDHR >> 8) & 0xFF;
    RxMsg->data[6] = (CAN1->sFIFOMailBox[0].RDHR >> 16) & 0xFF;
    RxMsg->data[7] = (CAN1->sFIFOMailBox[0].RDHR >> 24) & 0xFF;
    CAN1->RF0R |= (1 << 5);
}

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
    CanIf_Init(&CanIf_Config);

    while (1)
    {
        CanIf_ReadRxPduData(CAN_SENSOR_0, &info);
    }
}