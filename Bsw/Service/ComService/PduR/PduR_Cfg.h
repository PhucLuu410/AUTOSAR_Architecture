#ifndef __PDUR_CFG_H
#define __PDUR_CFG_H

#include "PduR.h"
#include "CanIf.h"
#include "CanIf_Cfg.h"
#include "Can_Cfg.h"
#include "LinIf.h"

extern PduR_RxRoutingPathType PduR_RxRouteTable[4];
extern PduR_TxRoutingPathType PduR_TxRouteTable[3];
extern PduR_PBConfigType PduR_PBConfig;
#endif