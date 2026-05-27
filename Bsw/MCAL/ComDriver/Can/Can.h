#ifndef CAN_H
#define CAN_H

#include "ComStack_Types.h"
#include "EcuM.h"
// #include "Icu.h"
#include "Os.h"
#include "Std_Types.h"

typedef struct
{

} Can_ConfigType;

void Can_Init(const Can_ConfigType *Config);
Std_ReturnType Can_SetControllerMode(uint8 Controller, Can_ControllerStateType Transition);
void Can_DisableControllerInterrupts(uint8 Controller);
void Can_EnableControllerInterrupts(uint8 Controller);
Std_ReturnType Can_SetBaudrate(uint8 Controller, uint16 BaudRateConfigID);
Std_ReturnType Can_Write(Can_HwHandleType Hth, const Can_PduType *PduInfo);

#endif