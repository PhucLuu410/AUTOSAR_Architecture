#ifndef SWC_ELECTRICDOORCONTROL_H
#define SWC_ELECTRICDOORCONTROL_H

#include "Rte_Diag.h"

void Swc_Diag_Init(void);
void Swc_Request_Diag_RPM(void);
void Swc_Request_Diag_Temp(void);
void Swc_Request_Diag_Vin(void);
void Swc_Request_Diag_SwVersion(void);
void Swc_Request_Diag_Evcu_Snapshot(void);
void Swc_Request_Diag_DTC(void);

#endif