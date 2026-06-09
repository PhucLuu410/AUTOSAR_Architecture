#ifndef __COM_H
#define __COM_H

#include "PduR.h"
#include "PduR_Cfg.h"

Std_ReturnType Com_SendSignal(PduIdType PduId);
void Com_RxIndication(PduIdType PduId, const PduInfoType *PduInfoPtr);
#endif