#ifndef __PDUR_H
#define __PDUR_H

#include "ComStack_Types.h"
#include "Std_Types.h"

typedef uint16 PduR_PBConfigIdType;
typedef uint16 PduR_RoutingPathGroupIdType;

typedef enum
{
    PDUR_UNINIT,
    PDUR_ONLINE,
} PduR_StateType;

typedef struct
{
    boolean PduRDevErrorDetect;
    boolean PduRMetaDataSupport;
    boolean PduRZeroCostOperation;
} PduRGeneral;

typedef struct
{
    uint32 PduRConfigurationId;
} PduRRoutingPaths;
typedef struct
{
    PduRGeneral *PduRGeneralConfig;
    PduRRoutingPaths *PduRRoutingPathsConfig;
} PduR_PBConfigType;

void PduR_Init(const PduR_PBConfigType *ConfigPtr);
PduR_PBConfigIdType PduR_GetConfigurationId(void);
void PduR_EnableRouting(PduR_RoutingPathGroupIdType id);
void PduR_DisableRouting(PduR_RoutingPathGroupIdType id, boolean initialize);
void PduR_CanIfRxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr);
void PduR_LinIfRxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr);
void PduR_CanTpRxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr);
BufReq_ReturnType PduR_CanTpCopyRxData(PduIdType id, const PduInfoType *info, PduLengthType *bufferSizePtr);
BufReq_ReturnType PduR_CanTpStartOfReception(PduIdType id, const PduInfoType *info, PduLengthType TpSduLength, PduLengthType *bufferSizePtr);
Std_ReturnType PduR_ComTransmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr);
Std_ReturnType PduR_DcmTransmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr);
#endif