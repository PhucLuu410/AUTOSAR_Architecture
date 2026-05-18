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
    Can_MainFunction_Read();
    count1 = 0;
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
    __ISB();
    while (1)
        ;
}
TASK(Task_5ms)
{
    Rte_Write_RobotControl(&RobotControlData1);
    count1 = 1;
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
    __ISB();
    while (1)
        ;
}

TASK(Task_10ms)
{
    Rte_Write_RobotSafety(&RobotSafetyData2);
    count1 = 2;
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
    while (1)
        ;
}

Task_ConfigType TaskList[] = {
    {.OsStackPointer = &OS_TASK_0[127], .pTask = Task_3ms, .interval = 3, .timer = &system_tick, .ReadyFlag = 0},
    {.OsStackPointer = &OS_TASK_1[127], .pTask = Task_5ms, .interval = 5, .timer = &system_tick, .ReadyFlag = 0},
    {.OsStackPointer = &OS_TASK_2[127], .pTask = Task_10ms, .interval = 10, .timer = &system_tick, .ReadyFlag = 0}};

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
    *stack_pointer = 0x11111111;
    stack_pointer--;
    *stack_pointer = 0x10101010;
    stack_pointer--;
    *stack_pointer = 0x09090909;
    stack_pointer--;
    *stack_pointer = 0x08080808;
    stack_pointer--;
    *stack_pointer = 0x07070707;
    stack_pointer--;
    *stack_pointer = 0x06060606;
    stack_pointer--;
    *stack_pointer = 0x05050505;
    stack_pointer--;
    *stack_pointer = 0x04040404;

    return stack_pointer;
}

void SysTick_Handler(void)
{
    // system_tick++;
    // if (system_tick % 3 == 0)
    // {
    //     SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
    //     TaskList[2].ReadyFlag = 1;
    // }
    // if (system_tick % 5 == 0)
    // {
    //     SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
    //     TaskList[0].ReadyFlag = 1;
    // }
    // if (system_tick % 10 == 0)
    // {
    //     SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
    //     TaskList[1].ReadyFlag = 1;
    // }
}

void Os_Init(void)
{
    TaskList[0].OsStackPointer = PrepareTaskStack(&OS_TASK_0[127], Task_3ms);
    TaskList[1].OsStackPointer = PrepareTaskStack(&OS_TASK_1[127], Task_5ms);
    TaskList[2].OsStackPointer = PrepareTaskStack(&OS_TASK_2[127], Task_10ms);
}
void Os_Start(void)
{
    current_psp = TaskList[0].OsStackPointer;
    __set_PSP((uint32_t)current_psp);
    __set_CONTROL(0x02);
    __ISB();
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

void Os_Scheduler(void)
{
    TaskList[current_task_index].OsStackPointer = current_psp;

    current_task_index++;
    if (current_task_index >= 3)
    {
        current_task_index = 0;
    }
    current_psp = TaskList[current_task_index].OsStackPointer;
}

__attribute__((naked)) void PendSV_Handler(void)
{
    __asm__ __volatile__(
        "MRS     R0, PSP \n"
        "STMDB   R0!, {R4-R11} \n"
        "LDR     R1, =current_psp \n"
        "STR     R0, [R1] \n"
        "PUSH    {LR} \n"
        "BL      Os_Scheduler \n"
        "POP     {LR} \n"
        "LDR     R1, =current_psp \n"
        "LDR     R0, [R1] \n"
        "LDMIA   R0!, {R4-R11} \n"
        "MSR     PSP, R0 \n"
        "BX      LR \n");
}