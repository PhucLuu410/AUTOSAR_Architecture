#ifndef SWC_VEHICLECOMMAND_H
#define SWC_VEHICLECOMMAND_H

#include "Rte_VehicleCommand.h"

void Swc_Read_ThrottleReq(uint8 *ThrottleReq);
void Swc_Read_EngineStartReq(boolean *EngineStartReq);
void Swc_Read_TorqueLimit(uint8 *TorqueLimit);
void Swc_Read_AliveAndCrc(uint8 *AliveAndCrc);

#endif