#include "Dio.h"
#include "Dio_Cfg.h"

Dio_ConfigTypeDef Config[] =
    {
        [BUTTON] = {PORTA, PIN0},
        [LED] = {PORTC, PIN13},
};

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
    if (Config[ChannelId].port->IDR & Config[ChannelId].pin)
        return STD_HIGH;
    else
        return STD_LOW;
}

void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
    if (Level == STD_HIGH)
        Config[ChannelId].port->ODR |= Config[ChannelId].pin;
    else
        Config[ChannelId].port->ODR &= ~(Config[ChannelId].pin);
}

Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId)
{
    return Config[PortId].port->ODR;
}

void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level)
{
    Config[PortId].port->ODR = Level;
    
}

Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType *ChannelGroupIdPtr)
{
    return 0;
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
    return 0;
}

void Dio_MaskedWritePort(Dio_PortType PortId,
                         Dio_PortLevelType Level,
                         Dio_PortLevelType Mask)
{

}