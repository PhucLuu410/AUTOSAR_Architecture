#include "OS.h"

uint32 OS_TASK_1[128] __attribute__((aligned(8)));
uint32 OS_TASK_2[128] __attribute__((aligned(8)));
uint32 OS_TASK_3[128] __attribute__((aligned(8)));

uint32 system_tick = 0;
uint32 current_task_index = 0;
uint32 *current_psp;

Robot_Control_PDU_Type RobotControlData1 = {
    .SteeringAngle = 2,
    .Speed = 2,
    .Mode = 2,
    .BrakeForce = 2,
    .Reserved = 2,
    .AliveCounter = 2,
    .Checksum = 2};

Robot_Safety_PDU_Type RobotSafetyData2 = {
    .SteeringAngle = 1,
    .Speed = 1,
    .Mode = 1,
    .BrakeForce = 1,
    .Reserved = 1,
    .AliveCounter = 1,
    .Checksum = 1};

TASK(Task_5ms)
{
    Rte_Write_RobotControl(&RobotControlData1);
}

TASK(Task_10ms)
{
    Rte_Write_RobotSafety(&RobotSafetyData2);
}
TASK(Task_3ms)
{
    Can_MainFunction_Read();
}

uint32 *PrepareTaskStack(uint32 *stack_top, void (*pTask)(void))
{
    stack_top--;
    *stack_top = 0x01000000;
    stack_top--;
    *stack_top = (uint32)pTask;
    stack_top--;
    *stack_top = 0xFFFFFFFD;
    for (int i = 0; i < 5; i++)
    {
        stack_top--;
        *stack_top = 0;
    }

    for (int i = 0; i < 8; i++)
    {
        stack_top--;
        *stack_top = 0;
    }
    return stack_top;
}

Task_ConfigType TaskList[] = {
    {.pTask = Task_5ms, .interval = 5, .timer = &system_tick, .OsStackPointer = NULL_PTR, .ReadyFlag = 0},
    {.pTask = Task_10ms, .interval = 10, .timer = &system_tick, .OsStackPointer = NULL_PTR, .ReadyFlag = 0},
    {.pTask = Task_3ms, .interval = 3, .timer = &system_tick, .OsStackPointer = NULL_PTR, .ReadyFlag = 0}};

void SysTick_Handler(void)
{
    system_tick++;
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
    if (system_tick % 5 == 0)
    {
        TaskList[0].ReadyFlag = 1;
    }
    if (system_tick % 10 == 0)
    {
        TaskList[1].ReadyFlag = 1;
    }
    if (system_tick % 3 == 0)
    {
        TaskList[2].ReadyFlag = 1;
    }
}

void Os_Init(void)
{
    for (int i = 0; i < sizeof(TaskList) / sizeof(Task_ConfigType); i++)
    {
        if (TaskList[i].pTask == Task_5ms)
        {
            TaskList[i].OsStackPointer = PrepareTaskStack(&OS_TASK_1[128], Task_5ms);
        }
        else if (TaskList[i].pTask == Task_10ms)
        {
            TaskList[i].OsStackPointer = PrepareTaskStack(&OS_TASK_2[128], Task_10ms);
        }
        else if (TaskList[i].pTask == Task_3ms)
        {
            TaskList[i].OsStackPointer = PrepareTaskStack(&OS_TASK_3[128], Task_3ms);
        }
    }
}
void Os_Start(void)
{
    while (1)
    {
        for (int i = 0; i < sizeof(TaskList) / sizeof(Task_ConfigType); i++)
        {
            if (TaskList[i].ReadyFlag == 1)
            {
                TaskList[i].pTask();
                TaskList[i].ReadyFlag = 0;
            }
        }
    }
}

void PendSV_Handler(void)
{
    __asm volatile(
        "CPSID   I                 \n"
        "MRS     R0, PSP           \n"
        "CBZ     R0, FIRST_TIME    \n"
        "STMDB   R0!, {R4-R11}     \n"
        "LDR     R1, =current_task_index \n"
        "LDR     R1, [R1]          \n"
        "LDR     R2, =TaskList     \n"
        "MOV     R3, #16           \n"
        "MLA     R2, R1, R3, R2    \n"
        "STR     R0, [R2]          \n"
        "FIRST_TIME:               \n"
        "LDR     R1, =current_task_index \n"
        "LDR     R2, [R1]          \n"
        "ADD     R2, R2, #1        \n"
        "CMP     R2, #3            \n"
        "IT      GE                \n"
        "MOVGE   R2, #0            \n"
        "STR     R2, [R1]          \n"
        "LDR     R2, =TaskList     \n"
        "LDR     R1, =current_task_index \n"
        "LDR     R1, [R1]          \n"
        "MOV     R3, #16           \n"
        "MLA     R2, R1, R3, R2    \n"
        "LDR     R0, [R2]          \n"
        "LDMIA   R0!, {R4-R11}     \n"
        "MSR     PSP, R0           \n"
        "CPSIE   I                 \n"
        "BX      LR                \n");
}