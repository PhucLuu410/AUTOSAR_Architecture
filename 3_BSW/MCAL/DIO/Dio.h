#ifndef __DIO_H
#define __DIO_H

#include "Std_Types.h"

typedef uint8 Dio_ChannelType;
typedef uint8 Dio_PortType;
typedef struct
{
    Dio_PortType port;
    uint16 mask;
    uint8 offset;
} Dio_ChannelGroupType;
typedef uint8 Dio_LevelType;
typedef uint16 Dio_PortLevelType;

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level);
Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType *ChannelGroupIdPtr);
void Dio_WriteChannelGroup(const Dio_ChannelGroupType *ChannelGroupIdPtr, Dio_PortLevelType Level);
void Dio_GetVersionInfo(Std_VersionInfoType *VersionInfo);
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId);
void Dio_MaskedWritePort(Dio_PortType PortId, Dio_PortLevelType Level, Dio_PortLevelType Mask);

#endif