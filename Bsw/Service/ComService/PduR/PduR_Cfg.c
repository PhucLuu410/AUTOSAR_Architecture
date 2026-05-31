#include "PduR_Cfg.h"
#include "PduR.h"
#include "Com.h"

PduR_TxRoutingPathType PduR_TxRouteTable[NUMBER_OF_COM_TX_SIGNAL] = {
    [0] = {.GlobalPduId = 0,
           .LocalPduId = 0,
           .Transmit_Func = CanIf_Transmit},
    [1] = {.GlobalPduId = 1,
           .LocalPduId = 1,
           .Transmit_Func = CanIf_Transmit},
    [2] = {.GlobalPduId = 2,
           .LocalPduId = 0,
           .Transmit_Func = LinIf_Transmit},
    [3] = {.GlobalPduId = 3,
           .LocalPduId = 1,
           .Transmit_Func = CanTp_Transmit}};

PduR_RxRoutingPathType PduR_RxRouteTable[NUMBER_OF_COM_RX_SIGNAL] = {
    [0] = {.GlobalPduId = 0,
           .LocalPduId = 0,
           .Rx_Func = Com_RxIndication},
    [1] = {.GlobalPduId = 1,
           .LocalPduId = 1,
           .Rx_Func = Com_RxIndication},
    [2] = {.GlobalPduId = 2,
           .LocalPduId = 2,
           .Rx_Func = Com_RxIndication},
    [3] = {.GlobalPduId = 3,
           .LocalPduId = 3,
           .Rx_Func = CanTp_RxIndication}};

PduR_PBConfigType PduR_PBConfig = {
    .RxRoutingTable = PduR_RxRouteTable,
    .TxRoutingTable = PduR_TxRouteTable,
};