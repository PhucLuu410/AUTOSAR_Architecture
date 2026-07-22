#ifndef OS_TASK_H
#define OS_TASK_H

#include "AutosarOs.h"

void Task_Init(void);
Std_ReturnType ActivateTask(TaskType TaskID);
OsTaskType *Os_SelectNextTask(void);
void Os_TerminateTask(void);

#endif