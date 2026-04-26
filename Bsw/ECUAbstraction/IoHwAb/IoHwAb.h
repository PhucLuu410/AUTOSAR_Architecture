#ifndef __IoHwAb_H
#define __IoHwAb_H

#include "Std_Types.h"
#include "Adc.h"
#include "Dio.h"
#include "Pwm.h"

typedef uint8 SensorType;
typedef uint8 ActuatorType;
typedef boolean ButtonType;

typedef struct
{
    SensorType Voltage;
    SensorType Range;
    SensorType Resolution;
    SensorType Accuracy;
    SensorType Synchronization;
    SensorType Lifetime;
    SensorType Filtering;
    SensorType SamplingRate;
} IoHwAbSensor_ConfigType;

typedef struct
{

} IoHwAbActuator_ConfigType;

typedef struct
{
    ButtonType Range;
    ButtonType Synchronization;
} IoHwAbButton_ConfigType;

void IoHwAb_Init<Init_Id>(const IoHwAbSensor_ConfigType *ConfigPtr);
void IoHwAb_Init<Init_Id>(const IoHwAbActuator_ConfigType *ConfigPtr);
void IoHwAb_Init<Init_Id>(const IoHwAbButton_ConfigType *ConfigPtr);

#endif