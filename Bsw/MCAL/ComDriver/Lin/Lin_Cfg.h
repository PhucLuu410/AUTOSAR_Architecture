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

extern Lin_ConfigType Lin_Config[NUMBER_OF_LIN_CHANNEL];
extern Lin_PduType LinTxPduInfo[SENSOR_USING_LIN];
#endif