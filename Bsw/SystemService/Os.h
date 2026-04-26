#ifndef __OS_H
#define __OS_H

#include "Std_Types.h"

typedef struct
{
    uint8_t ADC_Flag;
} SystemFlagTypeDef;

void Os_Schedule(void);

#endif
