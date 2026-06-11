#ifndef CANTP_CFG_H
#define CANTP_CFG_H

#include "CanTp.h"

#define NUMBER_OF_CAN_TP_TX_NSDU 1
#define NUMBER_OF_CAN_TP_RX_NSDU 1

#define BS 2
#define STmin 10

typedef enum
{
    CANTP_OFF,
    CANTP_ON,
} CanTp_InitAndShutdownStateMachineType;

typedef enum
{
    CANTP_TX_WAIT,
    CANTP_TX_PROCESSING,
} CanTp_TxSubStateMachineType;

typedef enum
{
    CANTP_RX_WAIT,
    CANTP_RX_PROCESSING,
} CanTp_RxSubStateMachineType;

typedef enum
{
    CANTP_BUFFER_LOCK,
    CANTP_BUFFER_UNLOCK,
} CanTp_BufferStateMachineType;

typedef enum
{
    CANTP_TX_IDLE,
    CANTP_TX_SEND_SF,
    CANTP_TX_SEND_FF,
    CANTP_TX_SEND_CF,
    CANTP_TX_WAIT_FC,
} CanTp_TxStateMachine;

typedef enum
{
    CANTP_RX_IDLE,
    CANTP_RX_RECEIVE_SF,
    CANTP_RX_RECEIVE_FF,
    CANTP_RX_RECEIVE_CF,
    CANTP_RX_SEND_FC,
} CanTp_RxStateMachine;

extern const CanTp_ConfigType CanTp_Config;

#endif