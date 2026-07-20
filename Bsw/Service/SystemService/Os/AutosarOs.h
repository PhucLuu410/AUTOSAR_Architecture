#ifndef AUTOSAR_OS_H
#define AUTOSAR_OS_H

#include "Std_GeneralTypes.h"
#include "Det.h"

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
} OsTaskType;

extern OsTaskType OsTaskTable[];

#endif