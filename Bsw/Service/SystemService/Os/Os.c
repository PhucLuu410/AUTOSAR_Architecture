#include "OS.h"

uint32 system_tick = 0;
volatile uint32_t execution_cycles = 0;

Robot_Control_PDU_Type RobotControlData1 = {
    .SteeringAngle = 2,
    .Speed = 2,
    .Mode = 2,
    .BrakeForce = 2,
    .Reserved = 2,
    .AliveCounter = 2,
    .Checksum = 2};

Robot_Control_PDU_Type RobotControlData2 = {
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
    Rte_Write_RobotControl(&RobotControlData2);
}

Task_ConfigType TaskList[] = {
    {.pTask = Task_5ms, .interval = 5, .timer = &system_tick, .ReadyFlag = 0},
    {.pTask = Task_10ms, .interval = 10, .timer = &system_tick, .ReadyFlag = 0}};

void SysTick_Handler(void)
{
    system_tick++;
    if (system_tick % 5 == 0)
    {
        TaskList[0].ReadyFlag = 1;
    }
    if (system_tick % 10 == 0)
    {
        TaskList[1].ReadyFlag = 1;
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
                uint32_t start_time = DWT->CYCCNT;
                TaskList[i].pTask();
                uint32_t end_time = DWT->CYCCNT;
                execution_cycles = end_time - start_time;
                TaskList[i].ReadyFlag = 0;
            }
        }
    }
}
