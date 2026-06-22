#include "Swc_Diag.h"

DiagState Uds_Open_Diag_Flag = DIAG_IDLE;
uint8 Uds_SessionExtended[] = {0x10, 0x03};
uint8 Uds_RPM_Diag[] = {0x22, 0x01, 0x0C};
uint8 Uds_TEMP_Diag[] = {0x22, 0x01, 0x05};
uint8 Uds_ClearDiagInformation[] = {0x14, 0xFF, 0xFF, 0xFF};

void Swc_Request_Open_Diag(void)
{
    if (Uds_Open_Diag_Flag == DIAG_IDLE)
    {
        Rte_Call_Diag_RequestTransmit(Uds_SessionExtended, sizeof(Uds_SessionExtended));
        Uds_Open_Diag_Flag = DIAG_REQUEST_TRANSMIT;
    }
}

void Swc_Request_RPM_Diag(void)
{
    if (Uds_Open_Diag_Flag == DIAG_REQUEST_TRANSMIT)
    {
        Rte_Call_Diag_RequestTransmit(Uds_RPM_Diag, sizeof(Uds_RPM_Diag));
    }
}

void Swc_Request_TEMP_Diag(void)
{
    if (Uds_Open_Diag_Flag == DIAG_REQUEST_TRANSMIT)
    {
        Rte_Call_Diag_RequestTransmit(Uds_TEMP_Diag, sizeof(Uds_TEMP_Diag));
    }
}