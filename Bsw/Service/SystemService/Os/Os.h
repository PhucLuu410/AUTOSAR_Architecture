#include "Rte.h"

#define TASK(FunctionName) void FunctionName(void)


typedef struct
{
    void (*pTask)(void);
    uint32_t interval;
    uint32_t *timer;
} Task_ConfigType;
