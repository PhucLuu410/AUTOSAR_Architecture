#include "OsAlarm.h"
#include "OsTask.h"
#include "OsCounter.h"

OsAlarmType AlarmTable[] = {
    {
        .ExpireValue = 100,
        .TaskID = 0,
    },
    {
        .ExpireValue = 200,
        .TaskID = 1,
    },
    {
        .ExpireValue = 300,
        .TaskID = 2,
    },
};

void Alarm_Check(void)
{
    for (uint8 i = 0; i < 3; i++)
    {
        if (Counter_GetValue() == AlarmTable[i].ExpireValue)
        {
            ActivateTask(AlarmTable[i].TaskID);
        }
    }
}