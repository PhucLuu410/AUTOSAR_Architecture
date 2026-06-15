#ifndef __COM_CFG_H
#define __COM_CFG_H

#include "Com.h"

#define NUMBER_OF_COM_RX_SIGNAL 4
#define NUMBER_OF_COM_TX_SIGNAL 4
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
extern uint8 Diag_Season_Control[8];
extern uint8 Read_Diag_Data_By_Id[8];
extern uint8 Diag_Error_Data_Tx[20];

extern uint8 Vehicle_Command[8];
extern uint8 Engine_RPM_Data[8];
extern uint8 Electric_Door_Data[8];
extern uint8 Diag_Data[20];
#endif
