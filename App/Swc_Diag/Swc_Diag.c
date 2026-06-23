#include "Swc_Diag.h"

void Swc_Diag_Init(void)
{
    Rte_Open_Diag_Request();
}

void Swc_Diag_RPM(void)
{
    Rte_Diag_RPM();
}
