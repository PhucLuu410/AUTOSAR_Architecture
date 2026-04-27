#include "IoHwAb.h"
#include "IoHwAb_Cfg.h"

IoHwAbSensor_ConfigType SensorConfigType[] = {
    [ADC_VOLTAGE] = {.ID = ADC_VOLTAGE},
    [ADC_CURRENT] = {.ID = ADC_CURRENT}};

IoHwAbActuator_ConfigType ActuatorConfigType[] = {
    [PWM_MOTOR] = {.ID = PWM_MOTOR, .DutyCycle = 50}};