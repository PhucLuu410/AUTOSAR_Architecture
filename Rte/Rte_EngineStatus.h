#ifndef RTE_ENGINESTATUS_H
#define RTE_ENGINESTATUS_H

#include "Std_GeneralTypes.h"
#include "Com.h"
#include "Swc_EngineStatus.h"

typedef struct
{
    uint16 Engine_RPM;
    uint8 Engine_Temp;
    uint8 Engine_TorqueActual;
    uint8 Engine_State;
    uint8 Engine_AliveAndCrc;
    uint16 Mac;
} EngineStatusType;

void Rte_Send_Engine_Status(void);
void Rte_Write_Engine_RPM(uint16 rpm);
void Rte_Write_Engine_Temp(uint8 temp);
void Rte_Write_Engine_TorqueActual(uint8 torque);
void Rte_Write_Engine_State(uint8 state);
void Rte_Write_Engine_AliveAndCrc(uint8 aliveAndCrc);
void Rte_Write_Engine_Mac(uint16 Mac);

#endif