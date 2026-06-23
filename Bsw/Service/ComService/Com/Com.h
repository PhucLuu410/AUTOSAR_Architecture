#ifndef __COM_H
#define __COM_H

#include "PduR.h"
#include "PduR_Cfg.h"

typedef uint16 Com_SignalIdType;
typedef uint16 Com_SignalGroupIdType;
typedef uint16 Com_IpduGroupIdType;

// Std_ReturnType Com_SendSignal(PduIdType PduId);
uint8 Com_ReceiveSignal(Com_SignalIdType SignalId, void *SignalDataPtr);
uint8 Com_SendSignal(Com_SignalIdType SignalId, const void *SignalDataPtr);
void Com_RxIndication(PduIdType PduId, const PduInfoType *PduInfoPtr);
void Dcm_RxIndication(PduIdType PduId, const PduInfoType *PduInfoPtr);
#endif