#ifndef __RTE_H
#define __RTE_H

#include "Dcm.h"

void Rte_Open_Diag_Request(void);
void Rte_Diag_RPM(void);
void Rte_Diag_Temp(void);
void Rte_Diag_Vin(void);
void Rte_Diag_SwVersion(void);
void Rte_Diag_Evcu_Snapshot(void);
void Rte_Diag_DTC(void);

#endif