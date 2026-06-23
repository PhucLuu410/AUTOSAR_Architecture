#include "Rte_Diag.h"

uint8 Open_Diag[2] = {0x10, 0x03};
uint8 Vin_Diag[3] = {0x22, 0xF1, 0x90};
uint8 SwVersion_Diag[3] = {0x22, 0xF1, 0x89};
uint8 RPM_Diag[3] = {0x22, 0x01, 0x0C};
uint8 Temp_Diag[3] = {0x22, 0x01, 0x05};
uint8 Evcu_Snapshot_Diag[3] = {0x22, 0xF0, 0x01};
uint8 DTC_Diag[3] = {0x19, 0x02, 0xFF};

uint8 NegativeResponseCode;

boolean Diag_Request_Flag = 0;

uint8 Rte_Diag_Response[30] = {0};

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

void Rte_Diag_Temp(void)
{
    if (Diag_Request_Flag == 1)
    {
        Dcm_WriteData(Temp_Diag, sizeof(Temp_Diag), &NegativeResponseCode);
    }
}

void Rte_Diag_Vin(void)
{
    if (Diag_Request_Flag == 1)
    {
        Dcm_WriteData(Vin_Diag, sizeof(Vin_Diag), &NegativeResponseCode);
    }
}

void Rte_Diag_SwVersion(void)
{
    if (Diag_Request_Flag == 1)
    {
        Dcm_WriteData(SwVersion_Diag, sizeof(SwVersion_Diag), &NegativeResponseCode);
    }
}

void Rte_Diag_Evcu_Snapshot(void)
{
    if (Diag_Request_Flag == 1)
    {
        Dcm_WriteData(Evcu_Snapshot_Diag, sizeof(Evcu_Snapshot_Diag), &NegativeResponseCode);
    }
}

void Rte_Diag_DTC(void)
{
    if (Diag_Request_Flag == 1)
    {
        Dcm_WriteData(DTC_Diag, sizeof(DTC_Diag), &NegativeResponseCode);
    }
}

void Rte_Parse_Diag_Response(void)
{
    Dcm_ReadData(Rte_Diag_Response);
}