#include "Swc_VehicleCommand.h"

void Swc_Read_ThrottleReq(uint8 *ThrottleReq)
{
    Rte_Parse_Vehicle_Command();
    Rte_Read_ThrottleReq(ThrottleReq);
}
void Swc_Read_EngineStartReq(bool *EngineStartReq)
{
    Rte_Parse_Vehicle_Command();
    Rte_Read_EngineStartReq(EngineStartReq);
}
void Swc_Read_TorqueLimit(uint8 *TorqueLimit)
{
    Rte_Parse_Vehicle_Command();
    Rte_Read_TorqueLimit(TorqueLimit);
}
void Swc_Read_AliveAndCrc(uint8 *AliveAndCrc)
{
    Rte_Parse_Vehicle_Command();
    Rte_Read_AliveAndCrc(AliveAndCrc);
}