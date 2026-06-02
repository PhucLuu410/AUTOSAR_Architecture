#ifndef __RTE_H
#define __RTE_H

#include "Com.h"
#include "Com_Cfg.h"

typedef struct
{
    uint8 WindowPosition; /* 0-100% */
    uint8 Direction;      /* 0: Stop, 1: Up, 2: Down */
    uint8 AutoMode;       /* 0: Manual, 1: Auto */
    uint8 SafetyStatus;   /* Anti-pinch sensor */
    uint8 Reserved[3];
    uint8 AliveCounter;
    uint8 Checksum;
} Rte_Electric_Door_Pdu_Type;

typedef struct
{
    uint8 TargetSpeed;
    uint8 Acceleration;
    uint8 Direction;
    uint8 MotorTemp;
    uint8 CurrentSense;
    uint8 Reserved[1];
    uint8 AliveCounter;
    uint8 Checksum;
} Rte_Gas_Control_Pdu_Type;

typedef struct
{
    uint8 CruiseStatus;
    uint8 SetSpeed;
    uint8 GapDistance;
    uint8 BrakeStatus;
    uint8 Reserved[2];
    uint8 AliveCounter;
    uint8 Checksum;
} Rte_Pedal_Control_Pdu_Type;

typedef struct
{
    uint16 ErrorCode;
    uint8 Severity;
    uint8 ModuleID;
    uint8 ErrorCount;
    uint8 Reserved[1];
    uint8 AliveCounter;
    uint8 Checksum;
} Rte_Diag_Error_Pdu_Type;

Std_ReturnType Rte_Write_CruiseControl(Rte_Pedal_Control_Pdu_Type *AppData);
Std_ReturnType Rte_Write_ElectricWindowControl(Rte_Electric_Door_Pdu_Type *AppData);
Std_ReturnType Rte_Write_GasControl(Rte_Gas_Control_Pdu_Type *AppData);
Std_ReturnType Rte_Write_DiagError(Rte_Diag_Error_Pdu_Type *AppData);

#endif