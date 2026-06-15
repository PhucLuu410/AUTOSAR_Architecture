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
void Read_RPM_And_TEMP_Data(uint8 *RPMData);
void Change_Diag(uint8 *DiagData, uint8 DiagH, uint8 DiagL);

#endif