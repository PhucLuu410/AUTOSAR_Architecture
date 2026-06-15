#include "Rte.h"

Std_ReturnType Rte_Write_Gas_Control(Rte_Gas_Control_Pdu_Type *AppData)
{
    Engine_Status[0] = AppData->TargetSpeed;
    Engine_Status[1] = AppData->Acceleration;
    Engine_Status[2] = AppData->Direction;
    Engine_Status[3] = AppData->MotorTemp;
    Engine_Status[4] = AppData->CurrentSense;
    Engine_Status[5] = AppData->Reserved[0];
    Engine_Status[6] = AppData->AliveCounter;
    Engine_Status[7] = AppData->Checksum;
    return E_OK;
}
Std_ReturnType Rte_Write_Pedal_Control(Rte_Pedal_Control_Pdu_Type *AppData)
{
    return E_OK;
}
Std_ReturnType Rte_Write_Electric_Door_Control(Rte_Electric_Door_Pdu_Type *AppData)
{
    return E_OK;
}
Std_ReturnType Rte_Write_Diag_Error(Rte_Diag_Error_Pdu_Type *AppData)
{
    return E_OK;
}
