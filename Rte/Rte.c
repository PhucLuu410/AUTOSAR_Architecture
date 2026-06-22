#include "Rte.h"

static uint16 Rte_Buffer_Engine_RPM = 0;
static uint8 Rte_Buffer_Engine_Temp = 0;

Std_ReturnType Rte_Call_Diag_RequestTransmit(uint8_t *data, uint16_t length)
{
    PduInfoType dcmInfo = {.SduDataPtr = data, .SduLength = length};
    return PduR_DcmTransmit(0, &dcmInfo);
}

void Rte_Write_Diag_RPM(uint16_t rpm)
{
    Rte_Buffer_Engine_RPM = rpm;
}

void Rte_Write_Diag_Temp(uint8_t temp)
{
    Rte_Buffer_Engine_Temp = temp;
}

void Rte_Read_Diag_RPM(uint16_t *rpmPtr)
{
    if (rpmPtr != NULL_PTR)
    {
        *rpmPtr = Rte_Buffer_Engine_RPM;
    }
}

void Rte_Read_Diag_Temp(uint8_t *tempPtr)
{
    if (tempPtr != NULL_PTR)
    {
        *tempPtr = Rte_Buffer_Engine_Temp;
    }
}
