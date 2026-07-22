#ifndef AUTOSAR_OS_H
#define AUTOSAR_OS_H

#include "Std_GeneralTypes.h"
#include "Det.h"

#define OS_TASK_STACK_SIZE 128
#define OS_MAX_TASKS 4

typedef uint8 TaskType;

typedef enum
{
    SUSPENDED,
    READY,
    RUNNING,
    WAITING
} TaskStateType;

typedef struct
{
    TaskType Id;
    void (*Entry)(void);
    uint8 Priority;
    uint8 Activation;
    TaskStateType State;
    uint32 *StackPointer;
} OsTaskType;

extern OsTaskType OsTaskTable[];
extern OsTaskType *CurrentTask;
extern OsTaskType *NextTask;

void AutosarOs_Init(void);
void AutosarOs_StartScheduler(void);

#endif