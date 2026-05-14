#include "PduR_Cfg.h"
#include "PduR.h"
#include "Com.h"

PduR_RxRoutingPathType PduR_RxRouteTable[] = {
    [0] = {.RxPduId = 0,
           .Rx_Func = Com_RxIndication},
    [1] = {.RxPduId = 1,
           .Rx_Func = Com_RxIndication},
    [2] = {.RxPduId = 2,
           .Rx_Func = CanTp_RxIndication},
    [3] = {.RxPduId = 3,
           .Rx_Func = Com_RxIndication}};

PduR_TxRoutingPathType PduR_TxRouteTable[] = {
    [0] = {.TxPduId = 0,
           .Transmit_Func = CanIf_Transmit},
    [1] = {.TxPduId = 1,
           .Transmit_Func = CanIf_Transmit},
    [2] = {.TxPduId = 2,
           .Transmit_Func = CanIf_Transmit}};

PduR_PBConfigType PduR_PBConfig = {
    .RxRoutingTable = PduR_RxRouteTable,
    .TxRoutingTable = PduR_TxRouteTable,
};