#include "Rte.h"

#define TASK(FunctionName) void FunctionName(void)

typedef struct
{
    void (*pTask)(void);
    uint32_t interval;
    uint32_t *timer;
    volatile uint8 ReadyFlag;
} Task_ConfigType;

void Os_Start(void);