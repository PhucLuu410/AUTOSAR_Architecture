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

typedef enum
{
    LIN_STATE_IDLE,
    LIN_STATE_BREAK,
    LIN_STATE_SYNC,
    LIN_STATE_PID,
    LIN_STATE_LENGTH,
    LIN_STATE_CS_MODEL,
    LIN_STATE_DRC,
    LIN_STATE_DATA,
    LIN_STATE_CHECKSUM
} Lin_FrameState;

extern Lin_ConfigType Lin_Config[NUMBER_OF_LIN_CHANNEL];
extern uint8 Lin_RxBuffer[NUMBER_OF_LIN_CHANNEL][20];
#endif