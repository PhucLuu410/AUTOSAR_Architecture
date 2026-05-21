#include "PduR_Cfg.h"
#include "PduR.h"
#include "Com.h"

PduR_RxRoutingPathType PduR_RxRouteTable[4] = {
    [0] = {.RxPduId = 0,
           .Rx_Func = Com_RxIndication},
    [1] = {.RxPduId = 1,
           .Rx_Func = Com_RxIndication},
    [2] = {.RxPduId = 2,
           .Rx_Func = CanTp_RxIndication},
    [3] = {.RxPduId = 3,
           .Rx_Func = Com_RxIndication}};

PduR_TxRoutingPathType PduR_TxRouteTable[3] = {
    [0] = {.GlobalPduId = 0,
           .LocalPduId = 0,
           .Transmit_Func = LinIf_Transmit},
    [1] = {.GlobalPduId = 1,
           .LocalPduId = 0,
           .Transmit_Func = CanIf_Transmit},
    [2] = {.GlobalPduId = 2,
           .LocalPduId = 1,
           .Transmit_Func = CanIf_Transmit}};

PduR_PBConfigType PduR_PBConfig = {
    .RxRoutingTable = PduR_RxRouteTable,
    .TxRoutingTable = PduR_TxRouteTable,
};