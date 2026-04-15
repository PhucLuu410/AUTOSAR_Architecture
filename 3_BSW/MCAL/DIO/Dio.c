#include "Dio.h"
#include "Dio_Cfg.h"
#include "stm32f103xb.h"


Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
    if (Dio_ChannelConfig[ChannelId].port->IDR & Dio_ChannelConfig[ChannelId].pin)
    {
        return STD_HIGH;
    }
    else
    {
        return STD_LOW;
    }
}

void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
    if (Level == STD_HIGH)
    {
        Dio_ChannelConfig[ChannelId].port->ODR |= Dio_ChannelConfig[ChannelId].pin;
    }
    else
    {
        Dio_ChannelConfig[ChannelId].port->ODR &=
            ~(Dio_ChannelConfig[ChannelId].pin);
    }
}

Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId)
{
    return Dio_PortConfig[PortId]->IDR;
}

void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level)
{
    Dio_PortConfig[PortId]->ODR = Level;
}

Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType *ChannelGroupIdPtr)
{

}

void Dio_WriteChannelGroup(const Dio_ChannelGroupType *ChannelGroupIdPtr,
                           Dio_PortLevelType Level)
{

}

void Dio_GetVersionInfo(Std_VersionInfoType *VersionInfo)
{

}

Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
{

}

void Dio_MaskedWritePort(Dio_PortType PortId,
                         Dio_PortLevelType Level,
                         Dio_PortLevelType Mask)
{

}