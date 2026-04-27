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

uint32_t Count = 0;
uint16_t *adcValue;
Adc_StatusType status;

void delay(volatile uint32_t t)
{
    while (t--)
        ;
}
MCU_PrehiralConfigType PrehiralConfig = {
    MCU_PREHIRAL_AHB,
    MCU_PREHIRAL_APB2,
    MCU_PREHIRAL_APB1};

Mcu_ClockConfigType Mcu_Clock_Configuration = {
    MCU_PLL_CLOCK_HSE,
    MCU_AHB_PRESCALE_1,
    MCU_APB2_PRESCALE_1,
    MCU_APB1_PRESCALE_1,
    &PrehiralConfig};

Mcu_ConfigType Mcu_Configuration[] = {
    {&Mcu_Clock_Configuration,
     NULL_PTR}};

const Port_ConfigType Port_Configuration[] = {
    {PORT_A,
     0,
     PORT_MODE_OUTPUT,
     PORT_OUTPUT_SPEED_50MHz,
     PORT_CNF_AF_OUTPUT_PP},

    {PORT_A,
     1,
     PORT_MODE_INPUT,
     PORT_OUTPUT_SPEED_50MHz,
     PORT_CNF_ANALOG_INPUT},

    {PORT_A,
     2,
     PORT_MODE_OUTPUT,
     PORT_OUTPUT_SPEED_50MHz,
     PORT_CNF_AF_OUTPUT_PP},

    {PORT_A,
     3,
     PORT_MODE_INPUT,
     PORT_OUTPUT_SPEED_50MHz,
     PORT_CNF_ANALOG_INPUT},

    {PORT_A,
     8,
     PORT_MODE_OUTPUT,
     PORT_OUTPUT_SPEED_50MHz,
     PORT_CNF_AF_OUTPUT_PP},
    {PORT_C,
     13,
     PORT_MODE_OUTPUT,
     PORT_OUTPUT_SPEED_50MHz,
     PORT_CNF_GP_OUTPUT_PP}};

Dio_TypeConfig Dio_Configuration = {PORT_C, PIN_13};

IoHwAbSensor_ConfigType SensorConfigType[] = {
    [ADC_VOLTAGE] = {.ID = ADC_VOLTAGE},
    [ADC_CURRENT] = {.ID = ADC_CURRENT}};

IoHwAbActuator_ConfigType ActuatorConfigType[] = {
    [PWM_MOTOR] = {.ID = PWM_MOTOR, .DutyCycle = 50}};

int main(void)
{
    Mcu_Init(&Mcu_Configuration[0]);
    Mcu_InitClock(Mcu_Configuration[0].ClockConfig->ClockSrc);

    Port_Init(Port_Configuration);
    IoHwAb_InitIoHwAbSensor(&SensorConfigType[ADC_VOLTAGE]);
    IoHwAb_InitIoHwAbActuator(ActuatorConfigType);
    IoHwAb_Dcm_Sensor(IoHwAb_Read, SensorConfigType[ADC_VOLTAGE]);
    while (1)
    {
        if (adcValue0[0] > 2000)
        {
            IoHwAb_Dcm_Actuator(IoHwAb_Write, ActuatorConfigType[PWM_MOTOR]);
        }
        else
        {
            ActuatorConfigType[PWM_MOTOR].DutyCycle = 0;
            IoHwAb_Dcm_Actuator(IoHwAb_Write, ActuatorConfigType[PWM_MOTOR]);
        }
    }
}
