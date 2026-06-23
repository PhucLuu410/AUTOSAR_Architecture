#ifndef OS_H
#define OS_H

#include "Rte_Diag.h"
#include "Can_GeneralTypes.h"

#define TASK(FunctionName) __attribute__((naked)) void FunctionName(void)
#define SIZE_OF_TASK_STACK 128
#define NUMBER_OF_TASKS 4

typedef enum
{
    TASK_READY,
    TASK_RUNNING,
    TASK_WAITING,
    TASK_SUSPENDED
} TaskState;

typedef struct
{
    uint32 *OsStackPointer;
    void (*pTask)(void);
    uint32 interval;
    uint32 *timer;
    uint8 Priority;
    TaskState State;
} Task_ConfigType;

extern Task_ConfigType TaskList[];
void Os_Start(void);
void Os_Init(void);

#endif