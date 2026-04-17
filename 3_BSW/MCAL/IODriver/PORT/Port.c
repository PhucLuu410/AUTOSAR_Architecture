#include "Port.h"

static GPIO_TypeDef *Dio_Port[] = {GPIOA, GPIOB, GPIOC, GPIOD};

void Port_Init(const Port_ConfigType* ConfigPtr)
{
    if(ConfigPtr->pin < 8)
        Dio_Port[ConfigPtr->port]->CRL |= ((ConfigPtr->cfg) << 2 | ConfigPtr->mode) << (ConfigPtr->pin * 4);
    else
        Dio_Port[ConfigPtr->port]->CRH |= ((ConfigPtr->cfg) << 2 | ConfigPtr->mode) << ((ConfigPtr->pin - 8) * 4);
}
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction)
{

}
void Port_RefreshPortDirection(void)
{

}
void Port_GetVersionInfo (Std_VersionInfoType* versioninfo)
{

}
void Port_SetPinMode (Port_PinType Pin, Port_PinModeType Mode)
{

}