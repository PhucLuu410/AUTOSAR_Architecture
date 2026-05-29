#include "OS.h"
#include "stm32f103xb.h"

uint32 Os_Task_0[SIZE_OF_TASK_STACK];
uint32 Os_Task_1[SIZE_OF_TASK_STACK];
uint32 Os_Task_2[SIZE_OF_TASK_STACK];
uint32 Os_Task_3[SIZE_OF_TASK_STACK];

uint32 Os_System_Tick = 0;
uint32 Os_Current_Task = 0;
uint32 *Os_Current_Psp = NULL_PTR;
uint8 MutexLock = 0;
uint32 a = 0;
uint8 Mutex_Lock(void)
{
    __disable_irq();
    if (MutexLock == 0)
    {
        MutexLock = 1;
        __enable_irq();
        return 1;
    }
    __enable_irq();
    return 0;
}

void Mutex_Unlock(void)
{
    __disable_irq();
    if (MutexLock == 1)
    {
        MutexLock = 0;
    }
    __enable_irq();
}

uint32 *PrepareTaskStack(uint32 *stack_pointer, void (*pTask)(void))
{
    *stack_pointer = 0x01000000; // xPSR
    stack_pointer--;
    *stack_pointer = (uint32_t)pTask | 0x01; // PC
    stack_pointer--;
    *stack_pointer = 0xFFFFFFFD; // LR
    stack_pointer--;
    *stack_pointer = 0x12121212; // R12
    stack_pointer--;
    *stack_pointer = 0x03030303; // R3
    stack_pointer--;
    *stack_pointer = 0x02020202; // R2
    stack_pointer--;
    *stack_pointer = 0x01010101; // R1
    stack_pointer--;
    *stack_pointer = 0x00000000; // R0
    stack_pointer--;
    *stack_pointer = 0x11111111; // R11
    stack_pointer--;
    *stack_pointer = 0x10101010; // R10
    stack_pointer--;
    *stack_pointer = 0x09090909; // R9
    stack_pointer--;
    *stack_pointer = 0x08080808; // R8
    stack_pointer--;
    *stack_pointer = 0x07070707; // R7
    stack_pointer--;
    *stack_pointer = 0x06060606; // R6
    stack_pointer--;
    *stack_pointer = 0x05050505; // R5
    stack_pointer--;
    *stack_pointer = 0x04040404; // R4

    return stack_pointer;
}

void TerminateTask(void)
{
    __disable_irq();
    TaskList[Os_Current_Task].State = TASK_SUSPENDED;
    __enable_irq();
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

TASK(Task_0)
{
    TerminateTask();
}

TASK(Task_1)
{
    Com_SendSignal(2);
    TerminateTask();
}

TASK(Task_2)
{
    for (int i = 0; i < 1000000; i++)
    {
        a++;
    }
    TerminateTask();
}

TASK(Task_Idle)
{
    while (1)
    {
    }
}

Task_ConfigType TaskList[] = {[0] = {.OsStackPointer = &Os_Task_0[SIZE_OF_TASK_STACK - 1],
                                     .pTask = Task_0,
                                     .interval = 3,
                                     .timer = &Os_System_Tick,
                                     .Priority = 0,
                                     .State = TASK_SUSPENDED},

                              [1] = {.OsStackPointer = &Os_Task_1[SIZE_OF_TASK_STACK - 1],
                                     .pTask = Task_1,
                                     .interval = 5,
                                     .timer = &Os_System_Tick,
                                     .Priority = 1,
                                     .State = TASK_SUSPENDED},

                              [2] = {.OsStackPointer = &Os_Task_2[SIZE_OF_TASK_STACK - 1],
                                     .pTask = Task_2,
                                     .interval = 20,
                                     .timer = &Os_System_Tick,
                                     .Priority = 2,
                                     .State = TASK_SUSPENDED},

                              [3] = {.OsStackPointer = &Os_Task_3[SIZE_OF_TASK_STACK - 1],
                                     .pTask = Task_Idle,
                                     .interval = 1,
                                     .timer = &Os_System_Tick,
                                     .Priority = 255,
                                     .State = TASK_READY}};

void SysTick_Handler(void)
{
    Os_System_Tick++;

    if ((Os_System_Tick % TaskList[0].interval) == 0 && TaskList[0].State == TASK_SUSPENDED)
    {
        TaskList[0].OsStackPointer = PrepareTaskStack(&Os_Task_0[SIZE_OF_TASK_STACK - 1], TaskList[0].pTask);
        TaskList[0].State = TASK_READY;
    }

    if ((Os_System_Tick % TaskList[1].interval) == 0 && TaskList[1].State == TASK_SUSPENDED)
    {
        TaskList[1].OsStackPointer = PrepareTaskStack(&Os_Task_1[SIZE_OF_TASK_STACK - 1], TaskList[1].pTask);
        TaskList[1].State = TASK_READY;
    }

    if ((Os_System_Tick % TaskList[2].interval) == 0 && TaskList[2].State == TASK_SUSPENDED)
    {
        TaskList[2].OsStackPointer = PrepareTaskStack(&Os_Task_2[SIZE_OF_TASK_STACK - 1], TaskList[2].pTask);
        TaskList[2].State = TASK_READY;
    }

    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}
void Os_Init(void)
{
    TaskList[0].OsStackPointer = PrepareTaskStack(&Os_Task_0[SIZE_OF_TASK_STACK - 1], Task_0);
    TaskList[1].OsStackPointer = PrepareTaskStack(&Os_Task_1[SIZE_OF_TASK_STACK - 1], Task_1);
    TaskList[2].OsStackPointer = PrepareTaskStack(&Os_Task_2[SIZE_OF_TASK_STACK - 1], Task_2);
    TaskList[3].OsStackPointer = PrepareTaskStack(&Os_Task_3[SIZE_OF_TASK_STACK - 1], Task_Idle);
}
void Os_Start(void)
{
    for (int i = 0; i < NUMBER_OF_TASKS; i++)
    {
        if (TaskList[i].State == TASK_READY)
        {
            Os_Current_Task = i;
            Os_Current_Psp = TaskList[i].OsStackPointer;
            break;
        }
    }
    SysTick->CTRL = 0x07;
    __asm volatile("SVC #0");
}

__attribute__((naked)) void SVC_Handler(void)
{
    __asm__ __volatile__(
        "LDR     R2, = Os_Current_Psp   \n"
        "LDR     R2, [R2]               \n"
        "LDMIA   R2!, {R4-R11}        \n"
        "MSR     PSP, R2              \n"
        "MOV     R0, #2               \n"
        "MSR     CONTROL, R0          \n"
        "ISB                          \n"
        "LDR     LR, =0xFFFFFFFD      \n"
        "BX      LR                   \n");
}

void Os_Scheduler(void)
{

    Os_Current_Task = 3;
    Os_Current_Psp = TaskList[3].OsStackPointer;

    if (TaskList[0].State == TASK_READY || TaskList[0].State == TASK_RUNNING)
    {
        TaskList[0].State = TASK_RUNNING;
        Os_Current_Task = 0;
        Os_Current_Psp = TaskList[0].OsStackPointer;
        return;
    }

    if (TaskList[1].State == TASK_READY || TaskList[1].State == TASK_RUNNING)
    {
        TaskList[1].State = TASK_RUNNING;
        Os_Current_Task = 1;
        Os_Current_Psp = TaskList[1].OsStackPointer;
        return;
    }

    if (TaskList[2].State == TASK_READY || TaskList[2].State == TASK_RUNNING)
    {
        TaskList[2].State = TASK_RUNNING;
        Os_Current_Task = 2;
        Os_Current_Psp = TaskList[2].OsStackPointer;
        return;
    }
}

__attribute__((naked)) void PendSV_Handler(void)
{
    __asm__ __volatile__(
        "MRS     R0, PSP                 \n"
        "STMDB   R0!, {R4-R11}          \n"
        "LDR     R1, =Os_Current_Psp       \n"
        "STR     R0, [R1]               \n"
        "PUSH    {LR}                   \n"
        "CPSID   I                      \n"
        "BL      Os_Scheduler           \n"
        "CPSIE   I                      \n"
        "POP     {LR}                   \n"
        "LDR     R1, =Os_Current_Psp       \n"
        "LDR     R0, [R1]               \n"
        "LDMIA   R0!, {R4-R11}          \n"
        "MSR     PSP, R0                \n"
        "BX      LR                     \n"
        :
        :
        : "memory");
}