#ifndef __RTE_H
#define __RTE_H

#include "Com.h"
#include "Com_Cfg.h"

typedef struct
{
    uint16 SteeringAngle;
    uint8 Speed;
    uint8 Mode;
    uint8 BrakeForce;
    uint8 Reserved;
    uint8 AliveCounter;
    uint8 Checksum;
} Rte_Cruise_Control_Pdu_Type;

typedef struct
{
    uint16 SteeringAngle;
    uint8 Speed;
    uint8 Mode;
    uint8 BrakeForce;
    uint8 Reserved;
    uint8 AliveCounter;
    uint8 Checksum;
} Rte_Electric_Window_Control_Pdu_Type;

typedef struct
{
    uint16 SteeringAngle;
    uint8 Speed;
    uint8 Mode;
    uint8 BrakeForce;
    uint8 Reserved;
    uint8 AliveCounter;
    uint8 Checksum;
} Rte_Motor_Control_Pdu_Type;

typedef struct
{
    uint16 SteeringAngle;
    uint8 Speed;
    uint8 Mode;
    uint8 BrakeForce;
    uint8 Reserved;
    uint8 AliveCounter;
    uint8 Checksum;
} Rte_Diag_Error_Pdu_Type;

Std_ReturnType Rte_Write_CruiseControl(Rte_Cruise_Control_Pdu_Type *AppData);
Std_ReturnType Rte_Write_ElectricWindowControl(Rte_Electric_Window_Control_Pdu_Type *AppData);
Std_ReturnType Rte_Write_MotorControl(Rte_Motor_Control_Pdu_Type *AppData);
Std_ReturnType Rte_Write_DiagError(Rte_Diag_Error_Pdu_Type *AppData);

#endif