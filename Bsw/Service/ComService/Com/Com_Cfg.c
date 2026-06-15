#include "Com_Cfg.h"

uint8 Engine_Status[8] = {0x0B, 0xD8, 0x5A, 0x64, 0x02, 0x1A, 0x00, 0x00};
uint8 Diag_Season_Control[8] = {0x02, 0x10, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8 Read_Diag_Data_By_Id[8] = {0x03, 0x22, 0x01, 0x0C, 0x00, 0x00, 0x00, 0x00};
uint8 Diag_Error_Data_Tx[20] = {0x22, 0xF1, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8 Diag_Error_Data_Tx2[3] = {0x10, 0x11, 0x12};

uint8 Vehicle_Command[8] = {0};
uint8 Engine_RPM_Data[8] = {0};
uint8 Electric_Door_Data[8] = {0};
uint8 Diag_Data[20] = {0};

ComTxSignalType ComTxSignalConfig[NUMBER_OF_COM_TX_SIGNAL] = {
    [0] = {.GlobalPduId = 0, .DataLength = sizeof(Engine_Status), .SduDataPtr = Engine_Status},
    [1] = {.GlobalPduId = 1, .DataLength = sizeof(Diag_Season_Control), .SduDataPtr = Diag_Season_Control},
    [2] = {.GlobalPduId = 2, .DataLength = sizeof(Read_Diag_Data_By_Id), .SduDataPtr = Read_Diag_Data_By_Id},
    [3] = {.GlobalPduId = 3, .DataLength = sizeof(Diag_Error_Data_Tx), .SduDataPtr = Diag_Error_Data_Tx}};

ComRxSignalType ComRxSignalConfig[NUMBER_OF_COM_RX_SIGNAL] = {
    [0] = {.GlobalPduId = 0, .DataLength = sizeof(Vehicle_Command), .SduDataPtr = Vehicle_Command},
    [1] = {.GlobalPduId = 1, .DataLength = sizeof(Engine_RPM_Data), .SduDataPtr = Engine_RPM_Data},
    [2] = {.GlobalPduId = 2, .DataLength = sizeof(Electric_Door_Data), .SduDataPtr = Electric_Door_Data},
    [3] = {.GlobalPduId = 3, .DataLength = sizeof(Diag_Data), .SduDataPtr = Diag_Data}};