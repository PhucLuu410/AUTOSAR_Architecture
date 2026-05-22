#include "OS.h"

uint32 OS_TASK_0[128];
uint32 OS_TASK_1[128];
uint32 OS_TASK_2[128];

uint32 count1;

uint32 system_tick = 0;
uint32 current_task_index = 0;
uint32 *current_psp;

volatile uint32_t *address_pointed;

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

TASK(Task_3ms)
{
    while (1)
    {
        if (TaskList[0].ReadyFlag == 1)
        {
            // Can_MainFunction_Read();
            TaskList[0].ReadyFlag = 0;
            SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
        }
    }
}

TASK(Task_5ms)
{
    while (1)
    {
        if (TaskList[1].ReadyFlag == 1)
        {
            // Rte_Write_RobotControl(&RobotControlData1); // ID 127
            TaskList[1].ReadyFlag = 0;
            SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
        }
    }
}

TASK(Task_10ms)
{
    while (1)
    {
        if (TaskList[2].ReadyFlag == 1)
        {
            // Rte_Write_RobotSafety(&RobotSafetyData2); // ID 123
            TaskList[2].ReadyFlag = 0;
            SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
        }
    }
}

Task_ConfigType TaskList[] = {
    {.OsStackPointer = &OS_TASK_0[127], .pTask = Task_3ms, .interval = 3, .timer = &system_tick, .ReadyFlag = 0, .Priority = 2},
    {.OsStackPointer = &OS_TASK_1[127], .pTask = Task_5ms, .interval = 5, .timer = &system_tick, .ReadyFlag = 0, .Priority = 0},
    {.OsStackPointer = &OS_TASK_2[127], .pTask = Task_10ms, .interval = 10, .timer = &system_tick, .ReadyFlag = 0, .Priority = 1}};

Task_ConfigType *TaskListWithPriority[] = {NULL_PTR, NULL_PTR, NULL_PTR};

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
    if ((system_tick % 3) == TaskList[0].interval)
    {
        TaskList[0].ReadyFlag = 1;
    }

    if ((system_tick % 5) == TaskList[1].interval)
    {
        TaskList[1].ReadyFlag = 1;
    }

    if ((system_tick % 10) == TaskList[2].interval)
    {
        TaskList[2].ReadyFlag = 1;
    }
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}
void Os_Init(void)
{
    TaskList[0].OsStackPointer = PrepareTaskStack(&OS_TASK_0[127], Task_3ms);
    TaskList[1].OsStackPointer = PrepareTaskStack(&OS_TASK_1[127], Task_5ms);
    TaskList[2].OsStackPointer = PrepareTaskStack(&OS_TASK_2[127], Task_10ms);
}
void Os_Start(void)
{
    current_psp = TaskListWithPriority[0]->OsStackPointer;
    SysTick->CTRL = 0x07;
    __asm volatile("SVC #0");
}

void SVC_Handler(void)
{
    __asm__ __volatile__(
        "LDR     R0, =current_psp     \n"
        "LDR     R2, [R0]             \n"
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
    TaskListWithPriority[current_task_index]->OsStackPointer = current_psp;
    for (int i = 0; i < 3; i++)
    {
        if (TaskListWithPriority[i]->ReadyFlag == 1)
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