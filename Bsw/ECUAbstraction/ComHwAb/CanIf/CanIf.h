#ifndef __COMHWAB_H
#define __COMHWAB_H

#include "Std_Types.h "
#include "Can_GeneralTypes.h"
#include "ComStack_Types.h "
#include "EcuM.h"

typedef struct
{
    uint16 CanIfRxPduDataLength;
    boolean CanIfRxPduDataLengthCheck;
    uint64 CanIfRxPduId;
    uint32 CanIfRxCanId;
    boolean CanIfRxPduReadData;
    boolean CanIfRxPduReadNotifyStatus;
    uint8 CanIfRxPduHrhIdRef;
    uint8 CanIfRxPduRef;
} CanIfRxPduCfg;

typedef enum
{
    CAN_ID_DYNAMIC,
    CAN_ID_STATIC,
} CanIfTxPduType;

typedef struct
{
    uint64 CanIfTxPduId;
    uint32 CanIfTxCanId;
    boolean CanIfTxPduReadNotifyStatus;
    boolean CanIfTxPduTruncation;
    CanIfTxPduType CanIfTxPduTypeCfg;
    uint8 CanIfTxPduBufferRef;
    uint8 CanIfTxPduRef;
} CanIfTxPduCfg;

typedef struct
{
    uint8 CanIfInitCfgSet;
    uint64 CanIfMaxBufferSize;
    uint64 CanIfMaxRxPduCfg;
    uint64 CanIfMaxTxPduCfg;
    CanIfRxPduCfg *CanIfRxPduCfgRef;
    CanIfTxPduCfg *CanIfTxPduCfgRef;
} CanIfInitCfg;

typedef struct
{
    CanIfInitCfg CanIfInitConfig;
} CanIf_ConfigType;

void CanIf_Init(const CanIf_ConfigType *ConfigPtr);
void CanIf_DeInit(void);
Std_ReturnType CanIf_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr);
void CanIf_TxConfirmation(PduIdType CanTxPduId);
void CanIf_RxIndication(const Can_HwType *Mailbox, const PduInfoType *PduInfoPtr);
#endif
