#ifndef DCM_H
#define DCM_H

#include "Dcm.h"

#define DCM_ID 1
typedef enum
{
    Diag_Close = 0,
    Diag_Open = 1,
} Diag_StateType;

extern uint8 Dcm_Rx_Buffer[30];
extern Diag_StateType Diag_Flag;

#endif