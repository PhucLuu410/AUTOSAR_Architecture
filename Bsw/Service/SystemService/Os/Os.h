#include "Rte.h"

#define TASK(FunctionName) __attribute__((naked)) void FunctionName(void)

typedef struct
{
    uint32 *OsStackPointer;
    void (*pTask)(void);
    uint32 interval;
    uint32 *timer;
    volatile uint8 ReadyFlag;
    uint8 Priority;
} Task_ConfigType;

extern Task_ConfigType TaskList[];
void Os_Start(void);
void Os_Init(void);