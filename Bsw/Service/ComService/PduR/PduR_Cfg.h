#ifndef __PDUR_CFG_H
#define __PDUR_CFG_H

#include "PduR.h"
#include "CanIf.h"
#include "LinIf.h"

#define NUMBER_OF_COM_TX_SIGNAL 3
#define NUMBER_OF_COM_RX_SIGNAL 4

extern PduR_RxRoutingPathType PduR_RxRouteTable[NUMBER_OF_COM_RX_SIGNAL];
extern PduR_TxRoutingPathType PduR_TxRouteTable[NUMBER_OF_COM_TX_SIGNAL];
extern PduR_PBConfigType PduR_PBConfig;
#endif