#include "Com_Cfg.h"

uint8 Engine_Status[8] = {0x0B, 0xD8, 0x5A, 0x64, 0x02, 0x1A, 0x00, 0x00};

uint8 Vehicle_Command[8] = {0};
uint8 Another_Command[8] = {0};

ComTxSignalType ComTxSignalConfig[NUMBER_OF_COM_TX_SIGNAL] = {
    [0] = {.GlobalPduId = 0, .DataLength = sizeof(Engine_Status), .SduDataPtr = Engine_Status},
};

ComRxSignalType ComRxSignalConfig[NUMBER_OF_COM_RX_SIGNAL] = {
    [0] = {.GlobalPduId = 0, .DataLength = sizeof(Vehicle_Command), .SduDataPtr = Vehicle_Command},
    [1] = {.GlobalPduId = 1, .DataLength = sizeof(Another_Command), .SduDataPtr = Another_Command},
};