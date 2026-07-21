#include "OsCounter.h"
#include "stm32f103xb.h"

static OsCounterType OsCounter;

void Counter_Init(void)
{
    OsCounter.Value = 0;
    OsCounter.MaxValue = 1000;
    SysTick->CTRL = 0x07;
}

void Counter_Tick(void)
{
    if (OsCounter.Value >= OsCounter.MaxValue)
    {
        OsCounter.Value = 0;
    }
    else
    {
        OsCounter.Value++;
    }
}

uint32 Counter_GetValue(void)
{
    return OsCounter.Value;
}