#ifndef CANTP_CFG_H
#define CANTP_CFG_H

#include "CanTp.h"

#define NUMBER_OF_CANTP 1

typedef enum
{
    TX_IDLE,
    SEND_SF,
    SEND_FF,
    SEND_CF,
    WAIT_FC,
} CanTp_TxStateType;

typedef enum
{
    RX_IDLE,
    RECEIVE_SF,
    RECEIVE_FF,
    RECEIVE_CF,
    SEND_FC,
} CanTp_RxStateType;

extern const CanTp_ConfigType CanTp_Config;
extern CanTp_TxStateType CanTp_TxState[NUMBER_OF_CANTP];
extern CanTp_RxStateType CanTp_RxState[NUMBER_OF_CANTP];
#endif