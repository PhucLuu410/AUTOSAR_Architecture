#ifndef __COM_CFG_H
#define __COM_CFG_H

#include "Com.h"

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

extern uint8 Gas_Sensor_Data[8];
extern uint8 Pedal_Sensor_Data[8];
extern uint8 Door_Control_Data[8];
extern uint8 Diag_Error_Data_Tx[20];

extern uint8 Motor_Control_Data[8];
extern uint8 Pedal_Handle_Data[8];
extern uint8 Electric_Door_Data[8];
extern uint8 Diag_Error_Data_Rx[20];
#endif
