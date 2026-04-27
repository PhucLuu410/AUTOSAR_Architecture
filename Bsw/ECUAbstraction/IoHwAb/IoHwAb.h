#ifndef __IoHwAb_H
#define __IoHwAb_H

#include "Std_Types.h"
#include "ADC/Adc.h"
#include "ADC/Adc_Cfg.h"
#include "Dio.h"
#include "Dio_Cfg.h"
#include "Pwm.h"
#include "Pwm_Cfg.h"

#define IoHwAb_Read 0
#define IoHwAb_Write 1

typedef uint8 SensorType;
typedef uint16 ActuatorType16;
typedef uint8 ActuatorType;
typedef boolean ButtonType;

typedef struct
{
    SensorType ID;
} IoHwAbSensor_ConfigType;

typedef struct
{
    ActuatorType ID;
    uint16 DutyCycle;
} IoHwAbActuator_ConfigType;

typedef struct
{
    ActuatorType ID;
} IoHwAbButton_ConfigType;

void IoHwAb_InitIoHwAbSensor(const IoHwAbSensor_ConfigType *ConfigPtr);
void IoHwAb_InitIoHwAbActuator(const IoHwAbActuator_ConfigType *ConfigPtr);
void IoHwAb_InitIoHwAbButton(const IoHwAbButton_ConfigType *ConfigPtr);
void IoHwAb_Dcm_Sensor(uint8 action, IoHwAbSensor_ConfigType signal);
void IoHwAb_Dcm_Actuator(uint8 action, IoHwAbActuator_ConfigType signal);
void IoHwAb_Dcm_Button(uint8 action, IoHwAbButton_ConfigType signal);

#endif