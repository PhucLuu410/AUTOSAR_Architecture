#include "OsTask.h"
#include "stm32f103xb.h"

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
    for (int i = 0; i < OS_MAX_TASKS; i++)
    {
        if (OsTaskTable[i].State == READY && OsTaskTable[i].Priority < HighPriorityTask)
        {
            CurrentTask = &OsTaskTable[i];
            HighPriorityTask = OsTaskTable[i].Priority;
        }
    }
    return CurrentTask;
}

void Os_TerminateTask(void)
{
    CurrentTask->Activation--;
    if (CurrentTask->Activation > 0)
    {
        CurrentTask->State = READY;
    }
    else
    {
        CurrentTask->State = SUSPENDED;
    }
    NextTask = Os_SelectNextTask();
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}
