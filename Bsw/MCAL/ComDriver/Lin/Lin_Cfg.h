#ifndef __LIN_CFG_H_
#define __LIN_CFG_H_

#include "Lin.h"

typedef enum
{
    LIN_RX_IDLE,
    LIN_RX_SYNC,
    LIN_RX_PID,
    LIN_RX_DATA,
    LIN_RX_CS,
} Lin_RxStateMachineType;

#define NUMBER_OF_LIN_CHANNEL 2
#define NUMBER_OF_LIN_PDU 4

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

extern Lin_ConfigType Lin_Config;

extern Lin_PduType Lin_DataCfg[NUMBER_OF_LIN_PDU];
#endif