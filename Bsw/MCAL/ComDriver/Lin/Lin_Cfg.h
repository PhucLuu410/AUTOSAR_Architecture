#ifndef __LIN_CFG_H_
#define __LIN_CFG_H_

#include "Lin.h"

#define NUMBER_OF_LIN_CHANNEL 2

#define LIN_CHANNEL_1 0
#define LIN_CHANNEL_2 1

#define LIN_UART_DISABLE 0
#define LIN_UART_ENABLE 1

#define LIN_MODE_DISABLE 0
#define LIN_MODE_ENABLE 1

#define LIN_TX_DISABLE 0
#define LIN_TX_ENABLE 1

#define LIN_RX_DISABLE 0
#define LIN_RX_ENABLE 1

#define LIN_MASTER 0
#define LIN_SLAVE 1

#define LIN_INTERRUPT_ENABLE 0
#define LIN_INTERRUPT_DISABLE 1

#define LIN_BREAK_DETECT_ENABLE 0
#define LIN_BREAK_DETECT_DISABLE 1

#define Lin_ElectronicWindow 0
#define Lin_ElectricWipers 1

extern Lin_ConfigType Lin_Config[NUMBER_OF_LIN_CHANNEL];

typedef struct
{
    uint32 Pid;
    uint8 Dl;
    boolean CsModel;
    boolean Response;
    uint8 *SduDataPtr;
    uint8 Crc;
} Lin_RxPduType;

extern Lin_RxPduType Lin_RxPdu[];
// extern uint8 Lin_RxBuffer[2][8];
#endif