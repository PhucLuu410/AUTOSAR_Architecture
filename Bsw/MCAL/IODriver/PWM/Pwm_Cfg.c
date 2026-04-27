#include "Pwm.h"
#include "Pwm_Cfg.h"

Pwm_ConfigType Pwm_Configuration[] = {
    [PWM_MOTOR] = {0, 1000, 50, 0, 0, PWM_VARIABLE_PERIOD}};
