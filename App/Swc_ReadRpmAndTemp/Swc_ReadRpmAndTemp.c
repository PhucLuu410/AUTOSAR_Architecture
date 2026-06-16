#include "Swc_ReadRpmAndTemp.h"

uint8 Open_Diag_Flag = 0;
uint16 RPM = 0;
uint8 TEMP = 0;
uint64 SoftwareVersion = 0;
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

void Parse_Diag_Data(uint8 *RPMData)
{
    if (((uint16)RPMData[1] << 8 | RPMData[2]) == 0x010C)
    {
        RPM = ((uint16)RPMData[3] << 8) | RPMData[4];
    }
    if (((uint16)RPMData[1] << 8 | RPMData[2]) == 0x0105)
    {
        TEMP = RPMData[3];
    }
    if ((((uint16)RPMData[1] << 8 | RPMData[2]) == 0xF189))
    {
        SoftwareVersion = RPMData[3];
    }
}

void Send_Open_Diag_Command(void)
{
    if (Open_Diag_Flag == 0)
    {
        Com_SendSignal(1);
        Open_Diag_Flag = 1;
    }
}