#ifndef SWC_ELECTRICDOORCONTROL_H
#define SWC_ELECTRICDOORCONTROL_H

#include "Com.h"
#include "Com_Cfg.h"

typedef struct
{
    uint8 ThrottleReg;
    uint8 EngineStartReg;
    uint8 TorqueLimit;
    uint8 Alive;
    uint8 Crc;
} VehicleCommand;

extern VehicleCommand VehicleCommandData;

void ReadVehicleCommandData(uint8 *VehicleData);
void Parse_Diag_Data(uint8 *RPMData);

#endif