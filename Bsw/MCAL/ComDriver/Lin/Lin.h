#ifndef __LIN_H
#define __LIN_H

#include "Std_Types.h"
#include "ComStack_Types.h"
#include "Lin_GeneralTypes.h"

typedef struct
{
    uint8 LinUartEn;
    uint8 LinTx;
    uint8 LinRx;
    uint8 LinEn;
} Lin_HardwareConfig;

typedef struct
{
    uint8 LinChannel;
    uint8 LinBreakDetect;
    uint32 LinBaud;
    uint8 LinIsr;
    uint8 LinMasterSlave;
} Lin_ChannelConfig;

typedef struct
{
    const Lin_HardwareConfig *LinHardware;
    const Lin_ChannelConfig *LinChannel;
} Lin_ConfigType;

void Lin_Init(const Lin_ConfigType *Config);
void Lin_MainFunction_Read(void);

#endif