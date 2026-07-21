#ifndef OS_COUNTER_H
#define OS_COUNTER_H

#include "Std_GeneralTypes.h"

typedef struct
{
    uint32 Value;
    uint32 MaxValue;
} OsCounterType;

void Counter_Init(void);
void Counter_Tick(void);
uint32 Counter_GetValue(void);

#endif