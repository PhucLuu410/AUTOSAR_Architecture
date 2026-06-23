#include "Rte_VehicleCommand.h"

VehicleCommandType VehicleCommand;

void Rte_Parse_Vehicle_Command(void)
{
    Com_ReceiveSignal(0, &VehicleCommand);
}

void Rte_Read_ThrottleReq(uint8 *ThrottleReq)
{
    if (ThrottleReq != NULL_PTR)
    {
        *ThrottleReq = VehicleCommand.ThrottleReq;
    }
}

void Rte_Read_EngineStartReq(boolean *EngineStartReq)
{
    if (EngineStartReq != NULL_PTR)
    {
        *EngineStartReq = (VehicleCommand.EngineStartReq & 0x01) ? 1 : 0;
    }
}

void Rte_Read_TorqueLimit(uint8 *TorqueLimit)
{
    if (TorqueLimit != NULL_PTR)
    {
        *TorqueLimit = VehicleCommand.TorqueLimit;
    }
}

void Rte_Read_AliveAndCrc(uint8 *AliveAndCrc)
{
    if (AliveAndCrc != NULL_PTR)
    {
        *AliveAndCrc = VehicleCommand.AliveAndCrc;
    }
}