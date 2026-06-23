#include "Rte_Diag.h"

uint8 Open_Diag[2] = {0x10, 0x03};
uint8 RPM_Diag[3] = {0x22, 0x01, 0x0C};
uint8 NegativeResponseCode;
boolean Diag_Request_Flag = 0;

void Rte_Open_Diag_Request(void)
{
    if (Diag_Request_Flag == 0)
    {
        Diag_Request_Flag = 1;
        Dcm_WriteData(Open_Diag, sizeof(Open_Diag), &NegativeResponseCode);
    }
}

void Rte_Diag_RPM(void)
{
    if (Diag_Request_Flag == 1)
    {
        Dcm_WriteData(RPM_Diag, sizeof(RPM_Diag), &NegativeResponseCode);
    }
}
