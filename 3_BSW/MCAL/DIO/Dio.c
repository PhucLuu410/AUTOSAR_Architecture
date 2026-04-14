#include "Dio.h"
#include "Dio_Cfg.h"
#include "stm32f103xb.h"

typedef struct
{
    GPIO_TypeDef *port;
    uint16 pin;
} Dio_ChannelConfigType;

extern const Dio_ChannelConfigType Dio_ChannelConfig[];
extern GPIO_TypeDef *Dio_PortConfig[];

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
    if (Dio_ChannelConfig[ChannelId].port->IDR &
        Dio_ChannelConfig[ChannelId].pin)
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
        Dio_ChannelConfig[ChannelId].port->ODR |=
            Dio_ChannelConfig[ChannelId].pin;
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
    uint16 value = Dio_PortConfig[ChannelGroupIdPtr->port]->IDR;

    value &= ChannelGroupIdPtr->mask;
    value >>= ChannelGroupIdPtr->offset;

    return value;
}

void Dio_WriteChannelGroup(const Dio_ChannelGroupType *ChannelGroupIdPtr,
                           Dio_PortLevelType Level)
{
    uint16 reg = Dio_PortConfig[ChannelGroupIdPtr->port]->ODR;

    reg &= ~(ChannelGroupIdPtr->mask);
    reg |= ((Level << ChannelGroupIdPtr->offset) &
            ChannelGroupIdPtr->mask);

    Dio_PortConfig[ChannelGroupIdPtr->port]->ODR = reg;
}

void Dio_GetVersionInfo(Std_VersionInfoType *VersionInfo)
{
    if (VersionInfo != 0)
    {
        VersionInfo->vendorID = 1000;
        VersionInfo->moduleID = 120;
        VersionInfo->sw_major_version = 1;
        VersionInfo->sw_minor_version = 0;
        VersionInfo->sw_patch_version = 0;
    }
}

Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
{
    Dio_ChannelConfig[ChannelId].port->ODR ^=
        Dio_ChannelConfig[ChannelId].pin;

    if (Dio_ChannelConfig[ChannelId].port->ODR &
        Dio_ChannelConfig[ChannelId].pin)
    {
        return STD_HIGH;
    }
    else
    {
        return STD_LOW;
    }
}

void Dio_MaskedWritePort(Dio_PortType PortId,
                         Dio_PortLevelType Level,
                         Dio_PortLevelType Mask)
{
    uint16 reg = Dio_PortConfig[PortId]->ODR;

    reg &= ~Mask;
    reg |= (Level & Mask);

    Dio_PortConfig[PortId]->ODR = reg;
}