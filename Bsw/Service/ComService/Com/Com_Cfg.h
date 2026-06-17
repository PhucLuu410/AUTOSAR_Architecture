#ifndef __COM_CFG_H
#define __COM_CFG_H

#include "Com.h"

#define NUMBER_OF_COM_RX_SIGNAL 4
#define NUMBER_OF_COM_TX_SIGNAL 8
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

extern uint8 Engine_Status[8];
extern uint8 Diag_Season_Control[2];
extern uint8 Diag_RPM_Id[3];
extern uint8 Diag_TEMP_Id[3];

extern uint8 Vehicle_Command[8];
extern uint8 Diag_Season_Control_Accept[20];
extern uint8 Diag_Data[30];
extern uint8 Engine_TEMP_Data[8];
#endif
