#include "OS.h"

uint32 OS_TASK_0[SIZE_OF_TASK_STACK];
uint32 OS_TASK_1[SIZE_OF_TASK_STACK];
uint32 OS_TASK_2[SIZE_OF_TASK_STACK];
uint32 OS_IDLE_STACK[SIZE_OF_TASK_STACK];
uint32 count1;
uint32 system_tick = 0;
uint32 current_task_index = 3;
uint32 *current_psp;
uint8 MutexLock = 0;
uint32 a = 0;
uint8 b = 0;

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

TASK(Task_3ms)
{
    // POP LAN THU 2 BI LOI
    if (TaskList[0].State == TASK_READY)
    {
        TaskList[0].State = TASK_RUNNING;
        for (int i = 0; i < 100; i++)
            ;
        TaskList[0].State = TASK_SUSPENDED;
    }
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

TASK(Task_5ms)
{
    if (TaskList[1].State == TASK_READY)
    {
        TaskList[1].State = TASK_RUNNING;
        for (int i = 0; i < 100; i++)
            ;
        TaskList[1].State = TASK_SUSPENDED;
    }
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

TASK(Task_13ms)
{
    if (TaskList[2].State == TASK_READY)
    {
        TaskList[2].State = TASK_RUNNING;
        for (int i = 0; i < 100; i++)
            ;
        TaskList[2].State = TASK_SUSPENDED;
    }
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

TASK(Task_Idle)
{
    while (1)
    {
    }
}

Task_ConfigType TaskList[] = {[0] = {.OsStackPointer = &OS_TASK_0[SIZE_OF_TASK_STACK - 1],
                                     .pTask = Task_3ms,
                                     .interval = 3,
                                     .timer = &system_tick,
                                     .Priority = 0,
                                     .State = TASK_SUSPENDED},
                              [1] = {.OsStackPointer = &OS_TASK_1[SIZE_OF_TASK_STACK - 1],
                                     .pTask = Task_5ms,
                                     .interval = 5,
                                     .timer = &system_tick,
                                     .Priority = 1,
                                     .State = TASK_SUSPENDED},
                              [2] = {.OsStackPointer = &OS_TASK_2[SIZE_OF_TASK_STACK - 1],
                                     .pTask = Task_13ms,
                                     .interval = 13,
                                     .timer = &system_tick,
                                     .Priority = 2,
                                     .State = TASK_SUSPENDED},
                              [3] = {.OsStackPointer = &OS_IDLE_STACK[SIZE_OF_TASK_STACK - 1],
                                     .pTask = Task_Idle,
                                     .interval = 1,
                                     .timer = &system_tick,
                                     .Priority = 255,
                                     .State = TASK_READY}};

Task_ConfigType *TaskListWithPriority[] = {&TaskList[0], &TaskList[1], &TaskList[2], &TaskList[3]};

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

void SysTick_Handler(void)
{
    system_tick++;
    if ((system_tick % TaskList[0].interval) == 0)
    {
        TaskList[0].State = TASK_READY;
    }

    if ((system_tick % TaskList[1].interval) == 0)
    {
        TaskList[1].State = TASK_READY;
    }

    if ((system_tick % TaskList[2].interval) == 0)
    {
        TaskList[2].State = TASK_READY;
    }
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}
void Os_Init(void)
{
    TaskList[0].OsStackPointer = PrepareTaskStack(&OS_TASK_0[SIZE_OF_TASK_STACK - 1], Task_3ms);
    TaskList[1].OsStackPointer = PrepareTaskStack(&OS_TASK_1[SIZE_OF_TASK_STACK - 1], Task_5ms);
    TaskList[2].OsStackPointer = PrepareTaskStack(&OS_TASK_2[SIZE_OF_TASK_STACK - 1], Task_13ms);
    TaskList[3].OsStackPointer = PrepareTaskStack(&OS_IDLE_STACK[SIZE_OF_TASK_STACK - 1], Task_Idle);

    for (int i = 0; i < NUMBER_OF_TASKS; i++)

    {
        for (int j = i + 1; j < NUMBER_OF_TASKS; j++)
        {
            if (TaskListWithPriority[j]->Priority < TaskListWithPriority[i]->Priority)
            {
                Task_ConfigType *temp = TaskListWithPriority[i];
                TaskListWithPriority[i] = TaskListWithPriority[j];
                TaskListWithPriority[j] = temp;
            }
        }
    }
}
void Os_Start(void)
{
    current_psp = TaskListWithPriority[3]->OsStackPointer;
    SysTick->CTRL = 0x07;
    __asm volatile("SVC #0");
}

__attribute__((naked)) void SVC_Handler(void)
{
    __asm__ __volatile__(
        "LDR     R2, [%0]             \n"
        "LDMIA   R2!, {R4-R11}        \n"
        "MSR     PSP, R2              \n"
        "MOV     R0, #2               \n"
        "MSR     CONTROL, R0          \n"
        "ISB                          \n"
        "LDR     LR, =0xFFFFFFFD      \n"
        "BX      LR                   \n"
        :
        : "r"(&current_psp)
        : "r0", "r2", "memory");
}

void Os_Scheduler(void)
{
    TaskListWithPriority[current_task_index]->OsStackPointer = current_psp;
    for (int i = 0; i < NUMBER_OF_TASKS; i++)
    {
        if (TaskListWithPriority[i]->State == TASK_READY)
        {
            current_task_index = i;
            break;
        }
    }
    current_psp = TaskListWithPriority[current_task_index]->OsStackPointer;
}

__attribute__((naked)) void PendSV_Handler(void)
{
    __asm__ __volatile__(
        "MRS     R0, PSP                 \n"
        "STMDB   R0!, {R4-R11}          \n"
        "LDR     R1, =current_psp       \n"
        "STR     R0, [R1]               \n"
        "PUSH    {LR}                   \n"
        "CPSID   I                      \n"
        "BL      Os_Scheduler           \n"
        "CPSIE   I                      \n"
        "POP     {LR}                   \n"
        "LDR     R1, =current_psp       \n"
        "LDR     R0, [R1]               \n"
        "LDMIA   R0!, {R4-R11}          \n"
        "MSR     PSP, R0                \n"
        "BX      LR                     \n"
        :
        :
        : "memory");
}