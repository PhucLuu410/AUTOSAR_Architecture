#include "Swc_Diag.h"

void Swc_Diag_Init(void)
{
    Rte_Open_Diag_Request();
}

void Swc_Request_Diag_RPM(void)
{
    Rte_Diag_RPM();
}

void Swc_Request_Diag_Temp(void)
{
    Rte_Diag_Temp();
}

void Swc_Request_Diag_Vin(void)
{
    Rte_Diag_Vin();
}

void Swc_Request_Diag_SwVersion(void)
{
    Rte_Diag_SwVersion();
}

void Swc_Request_Diag_Evcu_Snapshot(void)
{
    Rte_Diag_Evcu_Snapshot();
}

void Swc_Request_Diag_DTC(void)
{
    Rte_Diag_DTC();
}