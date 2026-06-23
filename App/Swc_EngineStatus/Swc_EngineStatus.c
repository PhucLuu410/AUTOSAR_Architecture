#include "Swc_EngineStatus.h"

void Swc_EngineStatus_MainFunction(void)
{
    Rte_Send_Engine_Status();
}

void Swc_EngineStatus_Update_RPM(uint16 RPM)
{
    Rte_Write_Engine_RPM(RPM);
}

void Swc_EngineStatus_Update_Temp(uint8 Temp)
{
    Rte_Write_Engine_Temp(Temp);
}

void Swc_EngineStatus_Update_TorqueActual(uint8 TorqueActual)
{
    Rte_Write_Engine_TorqueActual(TorqueActual);
}

void Swc_EngineStatus_Update_State(uint8 State)
{
    Rte_Write_Engine_State(State);
}

void Swc_EngineStatus_Update_AliveAndCrc(uint8 AliveAndCrc)
{
    Rte_Write_Engine_AliveAndCrc(AliveAndCrc);
}
