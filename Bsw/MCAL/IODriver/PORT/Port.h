#ifndef __PORT_H    
#define __PORT_H

#include "Std_Types.h"
#include "stm32f103xb.h"

typedef uint8_t Port_PortType;
typedef uint8_t Port_PinModeType;
typedef uint8_t Port_PinCfgType;
typedef uint8_t Port_PinType;
typedef struct
{
    Port_PortType port;
    Port_PinType pin;
    Port_PortType speed;
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

extern const Port_ConfigType Port_Configuration[];

#endif