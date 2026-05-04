#ifndef CAN_H
#define CAN_H

#include "Std_Types.h"
#include "ComStack_Types.h"
#include "Can_GeneralTypes.h"
typedef struct
{
    uint32 CanPropagationDelay;
    uint8 CanTseg1;
    uint8 CanTseg2;
    uint8 CanSjw;
    uint8 TxProcessing;
    uint8 RxProcessing;
    uint8 BusOffProcessing;
    uint8 ErrorProcessing;
} Can_ControllerConfigType;

typedef struct
{
    uint8 CanHohHandle;
    uint8 CanIdType;
    uint32 CanFilterId;
    uint32 CanFilterMask;
    uint8 CanMultiplexTransmission;
    uint8 CanObjectType;
} Can_HardwareObjectConfigType;
typedef struct
{
    const Can_ControllerConfigType *ControllerConfig;
    const Can_HardwareObjectConfigType *HardwareConfig;
} Can_ConfigType;

void Can_Init(const Can_ConfigType *ConfigPtr);
void Can_DeInit(void);

Std_ReturnType Can_SetBaudrate(uint8 Controller, uint16 BaudRateConfigID);
Std_ReturnType Can_SetControllerMode(uint8 Controller, Can_ControllerStateType Transition);

#endif