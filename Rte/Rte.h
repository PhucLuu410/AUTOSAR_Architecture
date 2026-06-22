#ifndef __RTE_H
#define __RTE_H

#include "Com.h"
#include "Com_Cfg.h"




Std_ReturnType Rte_Call_Diag_RequestTransmit(uint8_t *data, uint16_t length);
void Rte_Write_Diag_RPM(uint16_t rpm);
void Rte_Write_Diag_Temp(uint8_t temp);
void Rte_Read_Diag_RPM(uint16_t *rpmPtr);
void Rte_Read_Diag_Temp(uint8_t *tempPtr);
#endif