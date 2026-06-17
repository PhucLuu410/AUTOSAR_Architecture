#include "Swc_Diag.h"

uint8 Open_Diag_Flag = 0;
uint16 RPM = 0;
uint8 TEMP = 0;
uint32 SW_VERSION = 0;
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

void Parse_Diag_Data(uint8 *DiagData)
{
    if (DiagData[0] == 0x50 && DiagData[1] == 0x03 && DiagData[2] == 0x00 && Open_Diag_Flag == 1)
    {
        Open_Diag_Flag = 2;
    }
    if (((uint16)DiagData[1] << 8 | DiagData[2]) == 0x010C)
    {
        RPM = ((uint16)DiagData[3] << 8) | DiagData[4];
    }
    if (((uint16)DiagData[1] << 8 | DiagData[2]) == 0x0105)
    {
        TEMP = DiagData[3];
    }
    if (DiagData[0] == 0x62 && DiagData[1] == 0xF1 && DiagData[2] == 0x89)
    {
        SW_VERSION = (uint32)DiagData[10];
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

void Send_Diag_RPM_Command(void)
{
    if (Open_Diag_Flag == 2)
    {
        Com_SendSignal(2);
    }
}

void Send_Diag_TEMP_Command(void)
{
    if (Open_Diag_Flag == 2)
    {
        Com_SendSignal(3);
    }
}

void Send_Diag_SOFTWARE_VERSION_Command(void)
{
    if (Open_Diag_Flag == 2)
    {
        Com_SendSignal(4);
    }
}

void Send_Diag_VIN_Command(void)
{
    if (Open_Diag_Flag == 2)
    {
        Com_SendSignal(5);
    }
}

void Send_Diag_eVCUSnapShot_Command(void)
{
    if (Open_Diag_Flag == 2)
    {
        Com_SendSignal(6);
    }
}

void Send_Diag_ReadDTCInformation_Command(void)
{
    if (Open_Diag_Flag == 2)
    {
        Com_SendSignal(7);
    }
}

void Clear_Diag_Buffer(void)
{
    for (int i = 0; i < 30; i++)
    {
        Diag_Data[i] = 0;
    }
}