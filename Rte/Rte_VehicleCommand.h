#ifndef RTE_VEHICLECOMMAND_H
#define RTE_VEHICLECOMMAND_H

#include "Com.h"
#include "Std_Types.h"

typedef struct
{
    uint8 ThrottleReq;
    uint8 EngineStartReq;
    uint8 TorqueLimit;
    uint8 AliveAndCrc;
    uint32 Reserve;
} VehicleCommandType;

void Rte_Parse_Vehicle_Command(void);
void Rte_Read_ThrottleReq(uint8 *ThrottleReq);
void Rte_Read_EngineStartReq(bool *EngineStartReq);
void Rte_Read_TorqueLimit(uint8 *TorqueLimit);
void Rte_Read_AliveAndCrc(uint8 *AliveAndCrc);

#endif