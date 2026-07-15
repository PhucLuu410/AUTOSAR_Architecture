#include "Rte_EngineStatus.h"

EngineStatusType EngineStatus = {
    .Engine_RPM = 0xB80B,
    .Engine_Temp = 0x5A,
    .Engine_TorqueActual = 0x64,
    .Engine_State = 0x02,
    .Engine_AliveAndCrc = 0x1A,
    .Mac = 0,
};

void Rte_Send_Engine_Status(void)
{
    Com_SendSignal(0, &EngineStatus);
}

void Rte_Write_Engine_RPM(uint16 rpm)
{
    EngineStatus.Engine_RPM = rpm;
}

void Rte_Write_Engine_Temp(uint8 temp)
{
    EngineStatus.Engine_Temp = temp;
}

void Rte_Write_Engine_TorqueActual(uint8 torque)
{
    EngineStatus.Engine_TorqueActual = torque;
}

void Rte_Write_Engine_State(uint8 state)
{
    EngineStatus.Engine_State = state;
}

void Rte_Write_Engine_AliveAndCrc(uint8 aliveAndCrc)
{
    EngineStatus.Engine_AliveAndCrc = aliveAndCrc;
}

void Rte_Write_Engine_Mac(uint16 Mac)
{
    EngineStatus.Mac = Mac;
}