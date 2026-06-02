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
} LinIf_TxTableConfig;

typedef struct
{
    uint8 Lin_Channel;
    uint8 LinIf_LocalId;
    uint8 LinIf_LinId;
    uint8 LinIf_DataLength;
    uint8 *LinIf_RxData;
} LinIf_RxTableConfig;

typedef struct
{
    LinIf_TxTableConfig *LinIf_TxTable;
    LinIf_RxTableConfig *LinIf_RxTable;
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
void LinIf_RxIndication(NetworkHandleType Channel, uint8 *Lin_SduPtr);

#endif