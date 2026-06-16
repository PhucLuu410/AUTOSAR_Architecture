#include "Com_Cfg.h"

uint8 Engine_Status[8] = {0x0B, 0xD8, 0x5A, 0x64, 0x02, 0x1A, 0x00, 0x00};
uint8 Diag_Season_Control[2] = {0x10, 0x03};
uint8 Diag_RPM_Id[3] = {0x22, 0x01, 0x0C};
uint8 Diag_TEMP_Id[3] = {0x22, 0x01, 0x05};
uint8 Diag_VIN_Id[3] = {0x22, 0xF1, 0x90};
uint8 Diag_SoftwareVersion_Id[3] = {0x22, 0xF1, 0x89};

uint8 Vehicle_Command[8] = {0};
uint8 Diag_Season_Control_Accept[20] = {0};
uint8 Diag_Data[30] = {0};
uint8 Engine_TEMP_Data[8] = {0};

ComTxSignalType ComTxSignalConfig[NUMBER_OF_COM_TX_SIGNAL] = {
    [0] = {.GlobalPduId = 0, .DataLength = sizeof(Engine_Status), .SduDataPtr = Engine_Status},
    [1] = {.GlobalPduId = 1, .DataLength = sizeof(Diag_Season_Control), .SduDataPtr = Diag_Season_Control},
    [2] = {.GlobalPduId = 2, .DataLength = sizeof(Diag_SoftwareVersion_Id), .SduDataPtr = Diag_SoftwareVersion_Id},
    [3] = {.GlobalPduId = 3, .DataLength = sizeof(Diag_TEMP_Id), .SduDataPtr = Diag_TEMP_Id}};

ComRxSignalType ComRxSignalConfig[NUMBER_OF_COM_RX_SIGNAL] = {
    [0] = {.GlobalPduId = 0, .DataLength = sizeof(Vehicle_Command), .SduDataPtr = Vehicle_Command},
    [1] = {.GlobalPduId = 1, .DataLength = sizeof(Diag_Season_Control_Accept), .SduDataPtr = Diag_Season_Control_Accept},
    [2] = {.GlobalPduId = 2, .DataLength = sizeof(Engine_TEMP_Data), .SduDataPtr = Engine_TEMP_Data},
    [3] = {.GlobalPduId = 3, .DataLength = sizeof(Diag_Data), .SduDataPtr = Diag_Data}};