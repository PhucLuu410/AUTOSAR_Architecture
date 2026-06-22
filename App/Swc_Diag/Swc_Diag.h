#ifndef SWC_ELECTRICDOORCONTROL_H
#define SWC_ELECTRICDOORCONTROL_H

#include "Com.h"
#include "Com_Cfg.h"
#include "Rte.h"

typedef enum
{
    DIAG_IDLE,
    DIAG_REQUEST_TRANSMIT,
    DIAG_PROCESS_RESPONSE
} DiagState;

extern DiagState Uds_Open_Diag_Flag;
void Swc_Request_Open_Diag(void);
void Swc_Request_RPM_Diag(void);
void Swc_Request_TEMP_Diag(void);
#endif