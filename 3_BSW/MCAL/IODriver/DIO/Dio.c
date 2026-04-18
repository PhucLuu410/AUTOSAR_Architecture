#include "Dio.h"
#include "Dio_Cfg.h"

static GPIO_TypeDef *Dio_Port[] = {GPIOA, GPIOB, GPIOC, GPIOD};
static Dio_TypeConfig TypeConfig[] = {0};

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
    if ((Dio_LevelType)(Dio_Port[TypeConfig[ChannelId].Port]->IDR & TypeConfig[ChannelId].Pin))
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
    if (Level)
    {
        Dio_Port[TypeConfig[ChannelId].Port]->ODR |= TypeConfig[ChannelId].Pin;
    }
    else
    {
        Dio_Port[TypeConfig[ChannelId].Port]->ODR &= ~TypeConfig[ChannelId].Pin;
    }
}
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId)
{
    return (Dio_PortLevelType)Dio_Port[PortId]->IDR;
}

void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level)
{
    Dio_Port[PortId]->ODR = Level;
}

Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType *ChannelGroupIdPtr)
{
    Dio_PortType __mask = Dio_Port[ChannelGroupIdPtr->port]->IDR & (ChannelGroupIdPtr->mask);
    return (Dio_PortLevelType)(__mask >> ChannelGroupIdPtr->offset);
}

void Dio_WriteChannelGroup(const Dio_ChannelGroupType *ChannelGroupIdPtr,
                           Dio_PortLevelType Level)
{
    Dio_PortType __mask = Dio_Port[ChannelGroupIdPtr->port]->ODR & ~(ChannelGroupIdPtr->mask);
    Dio_Port[ChannelGroupIdPtr->port]->ODR = __mask | ((Level << ChannelGroupIdPtr->offset) & ChannelGroupIdPtr->mask);
}

void Dio_GetVersionInfo(Std_VersionInfoType *VersionInfo)
{
    if (VersionInfo == NULL)
    {
        return;
    }
    VersionInfo->vendorID = DIO_VENDOR_ID;
    VersionInfo->moduleID = DIO_MODULE_ID;
    VersionInfo->sw_major_version = DIO_SW_MAJOR_VERSION;
    VersionInfo->sw_minor_version = DIO_SW_MINOR_VERSION;
    VersionInfo->sw_patch_version = DIO_SW_PATCH_VERSION;
}

Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
{
    Dio_Port[TypeConfig[ChannelId].Port]->ODR ^=
        TypeConfig[ChannelId].Pin;

    if (Dio_Port[TypeConfig[ChannelId].Port]->ODR &
        TypeConfig[ChannelId].Pin)
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
    Dio_PortType __mask = Dio_Port[PortId]->ODR & ~Mask;
    Dio_Port[PortId]->ODR = __mask | (Level & Mask);
}