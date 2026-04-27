#include "IoHwAb.h"
#include "IoHwAb_Cfg.h"

void IoHwAb_InitIoHwAbSensor(const IoHwAbSensor_ConfigType *ConfigPtr)
{
    Adc_Init(&Adc_Configuration[ConfigPtr->ID]);
}

void IoHwAb_InitIoHwAbActuator(const IoHwAbActuator_ConfigType *ConfigPtr)
{
    Pwm_Init(&Pwm_Configuration[ConfigPtr->ID]);
}

void IoHwAb_Dcm_Sensor(uint8 action, IoHwAbSensor_ConfigType signal)
{
    if (action == IoHwAb_Read)
    {
        Adc_SetupResultBuffer(signal.ID, adcValue0);
        Adc_EnableGroupNotification(signal.ID);
        Adc_StartGroupConversion(signal.ID);
    }
}

void IoHwAb_Dcm_Actuator(uint8 action, IoHwAbActuator_ConfigType signal)
{
    if (action == IoHwAb_Write)
    {
        Pwm_SetDutyCycle(signal.ID, signal.DutyCycle);
    }
}