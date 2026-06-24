#include "PduR.h"
#include "Com.h"

typedef uint8 Dcm_NegativeResponseCodeType;

Std_ReturnType Dcm_ReadData(uint8 *Data);
Std_ReturnType Dcm_WriteData(const uint8 *Data, uint16 DataLength, Dcm_NegativeResponseCodeType *ErrorCode);
BufReq_ReturnType Dcm_CopyRxData(PduIdType id, const PduInfoType *info, PduLengthType *bufferSizePtr);
BufReq_ReturnType Dcm_StartOfReception(PduIdType id, const PduInfoType *info, PduLengthType TpSduLength, PduLengthType *bufferSizePtr);
void Dcm_TpRxIndication(PduIdType id, Std_ReturnType result);