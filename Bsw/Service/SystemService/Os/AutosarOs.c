#include "AutosarOs.h"
#include "OsAlarm.h"
#include "OsArch.h"
#include "OsCounter.h"
#include "OsSchedule.h"
#include "OsTask.h"
#include "OsResource.h"

void TestFunction1(void)
{
    uint8 a = 0;
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

OsTaskType OsTaskTable[] = {
    {
        .Activation = 0,
        .Entry = TestFunction1,
        .Id = 0,
        .Priority = 1,
        .State = SUSPENDED,
    },
    {
        .Activation = 0,
        .Entry = TestFunction2,
        .Id = 1,
        .Priority = 2,
        .State = SUSPENDED,
    },
    {
        .Activation = 0,
        .Entry = TestFunction3,
        .Id = 2,
        .Priority = 0,
        .State = SUSPENDED,
    },
};