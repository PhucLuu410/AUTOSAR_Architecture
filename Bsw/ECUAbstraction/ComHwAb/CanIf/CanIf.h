#ifndef __COMHWAB_H
#define __COMHWAB_H

#include "Std_GeneralTypes.h "
#include "Can_GeneralTypes.h"
#include "ComStack_Types.h "
#include "EcuM.h"

typedef struct
{
    uint64 CanIfRxPduId;
    uint32 CanIfRxCanId;
    void (*DestinationFuncPtr)(PduIdType RxPduId, const PduInfoType *PduInfoPtr);
} CanIfRxPduCfg;

typedef struct
{
    uint64 CanIfTxPduId;
    uint32 CanIfTxCanId;
    uint8 CanIfCanHoh;
} CanIfTxPduCfg;

typedef struct
{
    CanIfRxPduCfg *CanIfRxPduCfgRef;
    CanIfTxPduCfg *CanIfTxPduCfgRef;
} CanIf_ConfigType;

void CanIf_Init(const CanIf_ConfigType *ConfigPtr);
void CanIf_DeInit(void);
Std_ReturnType CanIf_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr);
void CanIf_RxIndication(const Can_HwType *Mailbox, const PduInfoType *PduInfoPtr);
#endif
