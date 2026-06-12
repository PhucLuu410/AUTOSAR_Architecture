#include "Com_Cfg.h"

uint8 Gas_Sensor_Data[8] = {0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01};
uint8 Pedal_Sensor_Data[8] = {0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02};
uint8 Door_Control_Data[8] = {0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03};
uint8 Diag_Error_Data_Tx[20] = {0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x11, 0x21,
                                0x31, 0x41, 0x51, 0x61, 0x71, 0x81, 0x12, 0x22, 0x32, 0x42};
uint8 Diag_Error_Data_Tx2[3] = {0x10, 0x11, 0x12};

uint8 Motor_Control_Data[8] = {0};
uint8 Pedal_Handle_Data[8] = {0};
uint8 Electric_Door_Data[8] = {0};
uint8 Diag_Error_Data_Rx[20] = {0};

ComTxSignalType ComTxSignalConfig[NUMBER_OF_COM_TX_SIGNAL] = {
    [0] = {.GlobalPduId = 0, .DataLength = sizeof(Gas_Sensor_Data), .SduDataPtr = Gas_Sensor_Data},
    [1] = {.GlobalPduId = 1, .DataLength = sizeof(Pedal_Sensor_Data), .SduDataPtr = Pedal_Sensor_Data},
    [2] = {.GlobalPduId = 2, .DataLength = sizeof(Door_Control_Data), .SduDataPtr = Door_Control_Data},
    [3] = {.GlobalPduId = 3, .DataLength = sizeof(Diag_Error_Data_Tx), .SduDataPtr = Diag_Error_Data_Tx}};

ComRxSignalType ComRxSignalConfig[NUMBER_OF_COM_RX_SIGNAL] = {
    [0] = {.GlobalPduId = 0, .DataLength = sizeof(Motor_Control_Data), .SduDataPtr = Motor_Control_Data},
    [1] = {.GlobalPduId = 1, .DataLength = sizeof(Pedal_Handle_Data), .SduDataPtr = Pedal_Handle_Data},
    [2] = {.GlobalPduId = 2, .DataLength = sizeof(Electric_Door_Data), .SduDataPtr = Electric_Door_Data},
    [3] = {.GlobalPduId = 3, .DataLength = sizeof(Diag_Error_Data_Rx), .SduDataPtr = Diag_Error_Data_Rx}};