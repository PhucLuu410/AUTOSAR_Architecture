#include "Swc_ReadRpmAndTemp.h"

uint16 RPM = 0;
uint8 TEMP = 0;

VehicleCommand VehicleCommandData = {
    .ThrottleReg = 0,
    .EngineStartReg = 0,
    .TorqueLimit = 0,
    .Alive = 0,
    .Crc = 0,
};

void ReadVehicleCommandData(uint8 *VehicleData)
{
    VehicleCommandData.ThrottleReg = VehicleData[0];
    VehicleCommandData.EngineStartReg = VehicleData[1] & 0x80;
    VehicleCommandData.TorqueLimit = VehicleData[2];
    VehicleCommandData.Alive = VehicleData[3] & 0xF0;
    VehicleCommandData.Crc = VehicleData[3] & 0x0F;
}

void Read_RPM_And_TEMP_Data(uint8 *RPMData)
{
    if (((uint16)RPMData[0] << 8 | RPMData[1]) == 0x010C)
    {
        RPM = ((uint16)RPMData[2] << 8) | RPMData[3];
    }
    if (((uint16)RPMData[0] << 8 | RPMData[1]) == 0x0105)
    {
        TEMP = RPMData[2];
    }
}

void Change_Diag(uint8 *DiagData, uint8 DiagH, uint8 DiagL)
{
    DiagData[2] = DiagH;
    DiagData[3] = DiagL;
    ;
}