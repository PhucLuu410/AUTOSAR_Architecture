#include "Rte.h"

#define TASK(FunctionName) static void FunctionName(void)

typedef struct
{
    void (*pTask)(void);
    uint32 interval;
    uint32 *timer;
    uint32 *OsStackPointer;
    volatile uint8 ReadyFlag;
} Task_ConfigType;

void Os_Start(void);
void Os_Init(void);