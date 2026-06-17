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
void Send_Open_Diag_Command(void);
void Send_Diag_RPM_Command(void);
void Send_Diag_TEMP_Command(void);
void Send_Diag_SOFTWARE_VERSION_Command(void);
void Send_Diag_VIN_Command(void);
void Send_Diag_eVCUSnapShot_Command(void);
void Send_Diag_ReadDTCInformation_Command(void);
void Clear_Diag_Buffer(void);

#endif