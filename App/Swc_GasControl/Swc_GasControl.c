#include "Swc_GasControl.h"

void Swc_GasControl(void)
{
    Rte_Gas_Control_Pdu_Type Gas_Control_Data = {
        .TargetSpeed = 1,
        .Acceleration = 1,
        .Direction = 1,
        .MotorTemp = 1,
        .CurrentSense = 1,
        .Reserved = {0},
        .AliveCounter = 1,
        .Checksum = 1};

    Rte_Write_Gas_Control(&Gas_Control_Data);
}
