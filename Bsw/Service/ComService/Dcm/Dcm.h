#include "PduR.h"
#include "Com.h"

BufReq_ReturnType Dcm_CopyRxData(PduIdType id, const PduInfoType *info, PduLengthType *bufferSizePtr);
BufReq_ReturnType Dcm_StartOfReception(PduIdType id, const PduInfoType *info, PduLengthType TpSduLength, PduLengthType *bufferSizePtr);
void Dcm_TpRxIndication(PduIdType id, Std_ReturnType result);