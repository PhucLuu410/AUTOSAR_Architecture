#ifndef __CANTP_H
#define __CANTP_H

#include "Std_Types.h "
#include "Can_GeneralTypes.h"
#include "ComStack_Types.h "
#include "EcuM.h"

Std_ReturnType CanTp_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoType);
void CanTp_RxIndication(PduIdType PduId, const PduInfoType *PduInfoPtr);

#endif