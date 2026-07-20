#include "OsTask.h"

OsTaskType *OsCurrentTask = NULL_PTR;

Std_ReturnType ActivateTask(TaskType TaskID)
{
    if (TaskID >= 3)
    {
        Det_ReportError(0, 0, 0, 5);
        return E_NOT_OK;
    }

    for (int i = 0; i < 3; i++)
    {
        if (OsTaskTable[i].Id == TaskID)
        {
            OsTaskTable[i].Activation++;
            if (OsTaskTable[i].State == SUSPENDED)
            {
                OsTaskTable[i].State = READY;
            }
        }
    }
    return E_OK;
}

OsTaskType *Os_SelectNextTask(void)
{
    uint8 HighPriorityTask = 255;
    OsTaskType *CurrentTask = NULL_PTR;
    for (int i = 0; i < 3; i++)
    {
        if (OsTaskTable[i].State == READY && OsTaskTable[i].Priority < HighPriorityTask)
        {
            CurrentTask = &OsTaskTable[i];
            HighPriorityTask = OsTaskTable[i].Priority;
        }
    }
    return CurrentTask;
}

OsTaskType Os_TerminateTask(void)
{
    if (OsCurrentTask == NULL_PTR)
    {
        Det_ReportError(0, 0, 0, 5);
    }
    OsCurrentTask->Activation--;
    if (OsCurrentTask->Activation > 0)
    {
        OsCurrentTask->State = READY;
    }
    else
    {
        OsCurrentTask->State = SUSPENDED;
    }
    OsCurrentTask = NULL_PTR;
}

void Os_Dispatch(void)
{
    OsTaskType *Task = Os_SelectNextTask();
    if (Task == NULL_PTR)
    {
        return;
    }
    Task->State = RUNNING;
    OsCurrentTask = Task;
    Task->Entry();
    Os_TerminateTask();
}