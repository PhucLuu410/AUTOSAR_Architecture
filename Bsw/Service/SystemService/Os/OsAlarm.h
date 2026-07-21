#ifndef OS_ALARM_H
#define OS_ALARM_H

#include "AutosarOs.h"
#include "Std_GeneralTypes.h"
typedef struct
{
    uint32 ExpireValue;
    TaskType TaskID;
} OsAlarmType;

extern OsAlarmType AlarmTable[];

void Alarm_Check(void);

#endif