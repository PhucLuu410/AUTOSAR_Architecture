#ifndef __COMHWAB_CFG_H
#define __COMHWAB_CFG_H

#include "ComHwAb.h"

typedef struct
{
    uint8 CanId;
    uint8 CanDataLength;
    uint8 *Data
} CanDataTransmit;

extern CanDataTransmit DataTransmit[];

#endif