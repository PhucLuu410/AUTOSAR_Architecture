#include "PduR_Cfg.h"
#include "PduR.h"
#include "Com.h"

#define Gas_Sensor_Data 0
#define Pedal_Sensor_Data 1
#define Door_Control_Data 2
#define Diag_Error_Data_Tx 3

#define Motor_Control_Data 0
#define Pedal_Handle_Data 1
#define Electric_Door_Data 2
#define Diag_Error_Data_Rx 3

PduR_TxRoutingPathType PduR_TxRouteTable[NUMBER_OF_COM_TX_SIGNAL] = {
    [Gas_Sensor_Data] = {.GlobalPduId = 0,
                         .LocalPduId = 0,
                         .Transmit_Func = CanIf_Transmit},
    [Pedal_Sensor_Data] = {.GlobalPduId = 1,
                           .LocalPduId = 1,
                           .Transmit_Func = CanIf_Transmit},
    [Door_Control_Data] = {.GlobalPduId = 2,
                           .LocalPduId = 0,
                           .Transmit_Func = LinIf_Transmit},
    [Diag_Error_Data_Tx] = {.GlobalPduId = 3,
                            .LocalPduId = 0,
                            .Transmit_Func = LinTp_Transmit}};

PduR_RxRoutingPathType PduR_RxRouteTable[NUMBER_OF_COM_RX_SIGNAL] = {
    [Motor_Control_Data] = {.GlobalPduId = 0,
                            .LocalPduId = 0,
                            .Rx_Func = Com_RxIndication},
    [Pedal_Handle_Data] = {.GlobalPduId = 1,
                           .LocalPduId = 1,
                           .Rx_Func = Com_RxIndication},
    [Electric_Door_Data] = {.GlobalPduId = 2,
                            .LocalPduId = 2,
                            .Rx_Func = Com_RxIndication},
    [Diag_Error_Data_Rx] = {.GlobalPduId = 3,
                            .LocalPduId = 3,
                            .Rx_Func = CanTp_RxIndication}};

PduR_PBConfigType PduR_PBConfig = {
    .RxRoutingTable = PduR_RxRouteTable,
    .TxRoutingTable = PduR_TxRouteTable,
};