#ifndef SWC_ENGINESTATUS_H
#define SWC_ENGINESTATUS_H

#include "Std_Types.h"
#include "Rte_EngineStatus.h"

void Swc_EngineStatus_MainFunction(void);
void Swc_EngineStatus_Update_RPM(uint16 RPM);
void Swc_EngineStatus_Update_Temp(uint8 Temp);
void Swc_EngineStatus_Update_TorqueActual(uint8 TorqueActual);
void Swc_EngineStatus_Update_State(uint8 State);
void Swc_EngineStatus_Update_AliveAndCrc(uint8 AliveAndCrc);

#endif