#include "Dio.h"
#include "Dio_Cfg.h"
#include "Port.h"
#include "Port_Cfg.h"
#include "Pwm.h"
#include "Pwm_Cfg.h"
#include "ADC/Adc.h"
#include "ADC/Adc_Cfg.h"
#include "Mcu.h"
#include "Mcu_Cfg.h"
#include "Os.h"
#include "IoHwAb.h"
#include "IoHwAb_Cfg.h"

void delay(volatile uint32_t t)
{
    while (t--)
        ;
}

int main(void)
{
    Mcu_Init(&Mcu_Configuration[0]);
    Mcu_InitClock(Mcu_Configuration[0].ClockConfig->ClockSrc);

    Port_Init(Port_Configuration);

    IoHwAb_InitIoHwAbSensor(&SensorConfigType[ADC_VOLTAGE]);
    IoHwAb_InitIoHwAbActuator(&ActuatorConfigType[PWM_MOTOR]);

    IoHwAb_Dcm_Sensor(IoHwAb_Read, SensorConfigType[ADC_VOLTAGE]);
    while (1)
    {
        if (adcValue0[0] > 3500)
        {
            ActuatorConfigType[PWM_MOTOR].DutyCycle = 50;
            IoHwAb_Dcm_Actuator(IoHwAb_Write, ActuatorConfigType[PWM_MOTOR]);
        }
        else
        {
            ActuatorConfigType[PWM_MOTOR].DutyCycle = 0;
            IoHwAb_Dcm_Actuator(IoHwAb_Write, ActuatorConfigType[PWM_MOTOR]);
        }
    }
}
