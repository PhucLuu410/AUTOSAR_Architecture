#ifndef __COM_H
#define __COM_H

#include "PduR.h"
#include "PduR_Cfg.h"

void Com_RxIndication(PduIdType PduId, const PduInfoType *PduInfoPtr);
void CanTp_RxIndication(PduIdType PduId, const PduInfoType *PduInfoPtr);
#endif