#include "Com_Cfg.h"

static uint8 Com_TxBuffer[3][8] = {
    {0},
    {0},
    {0},
};

static uint8 Com_RxBuffer[4][20] = {0};

ComTxSignalType ComTxSignalConfig[] = {
    [0] = {.PduId = SENSOR_0, .DataLength = 8, .SduDataPtr = Com_TxBuffer[0]},
    [1] = {.PduId = SENSOR_1, .DataLength = 8, .SduDataPtr = Com_TxBuffer[1]},
    [2] = {.PduId = SENSOR_2, .DataLength = 8, .SduDataPtr = Com_TxBuffer[2]},
};

ComRxSignalType ComRxSignalConfig[] = {
    [0] = {.PduId = SENSOR_0, .DataLength = 20, .SduDataPtr = Com_RxBuffer[0]},
    [1] = {.PduId = SENSOR_1, .DataLength = 20, .SduDataPtr = Com_RxBuffer[1]},
    [2] = {.PduId = SENSOR_2, .DataLength = 20, .SduDataPtr = Com_RxBuffer[2]},
    [3] = {.PduId = 3, .DataLength = 20, .SduDataPtr = Com_RxBuffer[3]}};