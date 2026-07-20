#ifndef OS_TASK_H
#define OS_TASK_H

#include "AutosarOs.h"

Std_ReturnType ActivateTask(TaskType TaskID);
OsTaskType *Os_SelectNextTask(void);
void Os_Dispatch(void);
#endif