#ifndef __COM_CFG_H
#define __COM_CFG_H

#include "Com.h"

#define NUMBER_OF_COM_RX_SIGNAL 2
#define NUMBER_OF_COM_TX_SIGNAL 1
typedef struct
{
    PduIdType GlobalPduId;
    uint8 DataLength;
    uint8 *SduDataPtr;
} ComTxSignalType;

typedef struct
{
    PduIdType GlobalPduId;
    uint8 DataLength;
    uint8 *SduDataPtr;
} ComRxSignalType;

extern ComTxSignalType ComTxSignalConfig[];
extern ComRxSignalType ComRxSignalConfig[];
#endif
