#ifndef __LINIF_H__
#define __LINIF_H__

#include "ComStack_Types.h"
#include "EcuM.h"
#include "Lin_GeneralTypes.h"

typedef uint8 LinIf_SchHandleType;

typedef struct
{
    uint8 LinChannel;
    uint8 LinIf_LocalId;
    uint8 LinIf_LinId;
} LinIf_PduTableConfig;

typedef struct
{
    LinIf_PduTableConfig *LinIf_PduTable;
} LinIf_ConfigType;

typedef struct
{
    /* data */
} LinTp_ConfigType;

typedef enum
{
    LINTP_APPLICATIVE_SCHEDULE,
    LINTP_DIAG_REQUEST,
    LINTP_DIAG_RESPONSE,
} LinTp_Mode;

void LinIf_Init(const LinIf_ConfigType *ConfigPtr);
Std_ReturnType LinIf_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr);

#endif