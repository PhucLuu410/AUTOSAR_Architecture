#ifndef __PORT_H    
#define __PORT_H

#include "Std_Types.h"
#include "stm32f103xb.h"

#define PORT_CNF_ANALOG_INPUT 0
#define PORT_CNF_FLOATING_INPUT 1
#define PORT_CNF_PULL_UP_INPUT 2

#define PORT_CNF_GP_OUTPUT_PP 0
#define PORT_CNF_GP_OUTPUT_OD 1
#define PORT_CNF_AF_OUTPUT_PP 2
#define PORT_CNF_AF_OUTPUT_OD 3


#define PORT_MODE_INPUT 0
#define PORT_MODE_OUTPUT_10MHz 1
#define PORT_MODE_OUTPUT_2MHz 2
#define PORT_MODE_OUTPUT_50MHz 3

#define PORT_A 0
#define PORT_B 1
#define PORT_C 2
#define PORT_D 3

typedef uint8_t Port_PortType;
typedef uint8_t Port_PinModeType;
typedef uint8_t Port_PinCfgType;
typedef uint8_t Port_PinType;
typedef struct
{
    Port_PortType port;
    Port_PinType pin;
    Port_PinModeType mode;
    Port_PinCfgType cfg;
} Port_ConfigType;


typedef enum{
    PORT_PIN_IN,
    PORT_PIN_OUT
} Port_PinDirectionType;

void Port_Init(const Port_ConfigType* ConfigPtr);
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction);
void Port_RefreshPortDirection(void);
void Port_GetVersionInfo (Std_VersionInfoType* versioninfo);
void Port_SetPinMode (Port_PinType Pin, Port_PinModeType Mode);


#endif