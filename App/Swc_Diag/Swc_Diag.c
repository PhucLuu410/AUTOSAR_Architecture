#include "Swc_Diag.h"

void Swc_Diag_Init(void)
{
    Rte_Open_Diag_Request();
}

void Swc_Request_Diag_RPM(void)
{
    Rte_Diag_RPM();
    Rte_Parse_Diag_Response();
}

void Swc_Request_Diag_Temp(void)
{
    Rte_Diag_Temp();
    Rte_Parse_Diag_Response();
}

void Swc_Request_Diag_Vin(void)
{
    Rte_Diag_Vin();
    Rte_Parse_Diag_Response();
}

void Swc_Request_Diag_SwVersion(void)
{
    Rte_Diag_SwVersion();
    Rte_Parse_Diag_Response();
}

void Swc_Request_Diag_Evcu_Snapshot(void)
{
    Rte_Diag_Evcu_Snapshot();
    Rte_Parse_Diag_Response();
}

void Swc_Request_Diag_DTC(void)
{
    Rte_Diag_DTC();
    Rte_Parse_Diag_Response();
}