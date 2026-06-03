#include "Rte.h"

Std_ReturnType Rte_Write_Gas_Control(Rte_Gas_Control_Pdu_Type *AppData)
{
    Gas_Sensor_Data[0] = AppData->TargetSpeed;
    Gas_Sensor_Data[1] = AppData->Acceleration;
    Gas_Sensor_Data[2] = AppData->Direction;
    Gas_Sensor_Data[3] = AppData->MotorTemp;
    Gas_Sensor_Data[4] = AppData->CurrentSense;
    Gas_Sensor_Data[5] = AppData->Reserved[0];
    Gas_Sensor_Data[6] = AppData->AliveCounter;
    Gas_Sensor_Data[7] = AppData->Checksum;
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
