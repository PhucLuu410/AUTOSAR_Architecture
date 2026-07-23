#include "AutosarOs.h"
#include "OsAlarm.h"
#include "OsArch.h"
#include "OsCounter.h"
#include "OsSchedule.h"
#include "OsTask.h"
#include "OsResource.h"
#include "stm32f103xb.h"

static uint32 OsTaskStack[OS_MAX_TASKS][OS_TASK_STACK_SIZE];

OsTaskType *CurrentTask = NULL_PTR;
OsTaskType *NextTask = NULL_PTR;

void TestFunction1(void)
{
    uint8 a = 0;
    CurrentTask->State = RUNNING;
    Os_TerminateTask();
}

void TestFunction2(void)
{
    uint8 a = 0;
}

void TestFunction3(void)
{
    uint8 a = 0;
    a++;
    for (int i = 0; i < 10000; i++)
        ;
}

void IdleFunction(void)
{
    while (1)
    {
        __WFI();
    }
}

OsTaskType OsTaskTable[] = {
    {
        .Activation = 0,
        .Entry = TestFunction1,
        .Id = 0,
        .Priority = 0,
        .State = SUSPENDED,
        .StackPointer = NULL_PTR,
    },
    {
        .Activation = 0,
        .Entry = TestFunction2,
        .Id = 1,
        .Priority = 1,
        .State = SUSPENDED,
        .StackPointer = NULL_PTR,
    },
    {
        .Activation = 0,
        .Entry = TestFunction3,
        .Id = 2,
        .Priority = 2,
        .State = SUSPENDED,
        .StackPointer = NULL_PTR,
    },
    {
        .Activation = 0,
        .Entry = IdleFunction,
        .Id = 3,
        .Priority = 3,
        .State = READY,
        .StackPointer = NULL_PTR,
    },
};

static void AutosarOs_BuildInitialStack(OsTaskType *Task)
{
    uint32 *sp;
    sp = &OsTaskStack[Task->Id][OS_TASK_STACK_SIZE];
    *(--sp) = 0x01000000;
    *(--sp) = (uint32)Task->Entry;
    *(--sp) = 0xFFFFFFFD;
    *(--sp) = 0x12121212;
    *(--sp) = 0x03030303;
    *(--sp) = 0x02020202;
    *(--sp) = 0x01010101;
    *(--sp) = 0x00000000;
    *(--sp) = 0x11111111;
    *(--sp) = 0x10101010;
    *(--sp) = 0x09090909;
    *(--sp) = 0x08080808;
    *(--sp) = 0x07070707;
    *(--sp) = 0x06060606;
    *(--sp) = 0x05050505;
    *(--sp) = 0x04040404;
    Task->StackPointer = sp;
}

void AutosarOs_Init(void)
{
    for (int i = 0; i < OS_MAX_TASKS; i++)
    {
        AutosarOs_BuildInitialStack(&OsTaskTable[i]);
    }
    Counter_Init();
}

void AutosarOs_StartScheduler(void)
{
    ActivateTask(0);
    CurrentTask = Os_SelectNextTask();

    Arch_StartFirstTask();
}

void SysTick_Handler(void)
{
    Counter_Tick();
    Alarm_Check();
    NextTask = Os_SelectNextTask();
}

// void SVC_Handler(void)
// {
//     uint32 *sp = CurrentTask->StackPointer;
//     SVC_RestoreContext(sp);
// }

void SaveContext(void)
{
    while (1)
        ;
}

void SwitchContext(void)
{
    while (1)
        ;
}

uint32 *SavePsp;

void PendSV_Handler(void)
{
    __asm volatile(
        "mrs r0, psp \n"
        "stmdb r0!, {r4-r11} \n"
        "ldr r1, =SavePsp      \n"
        "str r0, [r1]         \n");
}