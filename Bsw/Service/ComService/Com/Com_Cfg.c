#include "Com_Cfg.h"

static uint8 Com_TxBuffer[NUMBER_OF_COM_TX_SIGNAL][8] = {
    {0x11, 0x22, 0x22, 0x22, 0x55, 0x66, 0x77, 0x88},
    {0x12, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88},
    {0x13, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88},
};

static uint8 Com_RxBuffer[NUMBER_OF_COM_RX_SIGNAL][20] = {0};

ComTxSignalType ComTxSignalConfig[NUMBER_OF_COM_TX_SIGNAL] = {
    [0] = {.GlobalPduId = 0, .DataLength = 8, .SduDataPtr = Com_TxBuffer[0]},
    [1] = {.GlobalPduId = 1, .DataLength = 8, .SduDataPtr = Com_TxBuffer[0]},
    [2] = {.GlobalPduId = 2, .DataLength = 8, .SduDataPtr = Com_TxBuffer[2]},
};

ComRxSignalType ComRxSignalConfig[NUMBER_OF_COM_RX_SIGNAL] = {
    [0] = {.GlobalPduId = 0, .DataLength = 20, .SduDataPtr = Com_RxBuffer[0]},
    [1] = {.GlobalPduId = 1, .DataLength = 20, .SduDataPtr = Com_RxBuffer[1]},
    [2] = {.GlobalPduId = 2, .DataLength = 20, .SduDataPtr = Com_RxBuffer[2]},
    [3] = {.GlobalPduId = 3, .DataLength = 20, .SduDataPtr = Com_RxBuffer[3]}};