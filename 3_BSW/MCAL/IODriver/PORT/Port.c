#include "Port.h"
#include "Port_Cfg.h"

static GPIO_TypeDef *Dio_Port[] = {GPIOA, GPIOB, GPIOC, GPIOD};

const Port_ConfigType Port_Configuration[NUMBER_OF_CHANNEL] = {
    [LED] = {.port = PORT_C,
             .pin = 13,
             .mode = PORT_MODE_OUTPUT,
             .speed = PORT_OUTPUT_SPEED_10Mhz,
             .cfg = PORT_CNF_GP_OUTPUT_PP},
    [BUTTON] = {.port = PORT_A,
                .pin = 0,
                .mode = PORT_MODE_INPUT,
                .cfg = PORT_CNF_PULL_UP_INPUT}};

void Port_Init(const Port_ConfigType* ConfigPtr)
{
    for (int i = 0; i < NUMBER_OF_CHANNEL; i++)
    {

        if (ConfigPtr[i].pin < 8)
            Dio_Port[ConfigPtr[i].port]->CRL |= ((ConfigPtr[i].cfg) << 2 | ConfigPtr[i].mode * ConfigPtr[i].speed) << (ConfigPtr[i].pin * 4);
        else
            Dio_Port[ConfigPtr[i].port]->CRH |= ((ConfigPtr[i].cfg) << 2 | ConfigPtr[i].mode * ConfigPtr[i].speed) << ((ConfigPtr[i].pin - 8) * 4);
    }
}

void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction)
{
    if (Direction == PORT_PIN_IN)
    {
        if (Port_Configuration[Pin].pin < 8)
            Dio_Port[Port_Configuration[Pin].port]->CRL &= ~((0xF) << (Port_Configuration[Pin].pin * 4));
        else
            Dio_Port[Port_Configuration[Pin].port]->CRH &= ~((0xF) << ((Port_Configuration[Pin].pin - 8) * 4));
    }
    else
    {
        if (Port_Configuration[Pin].pin < 8)
        {
            Dio_Port[Port_Configuration[Pin].port]->CRL &=
                ~((0xF) << (Port_Configuration[Pin].pin * 4));
            Dio_Port[Port_Configuration[Pin].port]->CRL |=
                ((Port_Configuration[Pin].cfg) << 2 | (Port_Configuration[Pin].mode * Port_Configuration[Pin].speed)) << (Port_Configuration[Pin].pin * 4);
        }

        else
        {
            Dio_Port[Port_Configuration[Pin].port]->CRL &=
                ~((0xF) << (Port_Configuration[Pin].pin * 4));
            Dio_Port[Port_Configuration[Pin].port]->CRH |=
                ((Port_Configuration[Pin].cfg) << 2 | (Port_Configuration[Pin].mode * Port_Configuration[Pin].speed)) << ((Port_Configuration[Pin].pin - 8) * 4);
        }
    }
}

void Port_RefreshPortDirection(void)
{
    for (int i = 0; i < NUMBER_OF_CHANNEL; i++)
    {
        if (Port_Configuration[i].pin < 8)
        {
            Dio_Port[Port_Configuration[i].port]->CRL &= ~0xF << (Port_Configuration[i].pin * 4);
            Dio_Port[Port_Configuration[i].port]->CRL |= (Port_Configuration[i].cfg << 2 | (Port_Configuration[i].mode * Port_Configuration[i].speed)) << (Port_Configuration[i].pin * 4);
        }
        else
        {
            Dio_Port[Port_Configuration[i].port]->CRH &= ~0xF << (Port_Configuration[i].pin * 4);
            Dio_Port[Port_Configuration[i].port]->CRH |= (Port_Configuration[i].cfg << 2 | (Port_Configuration[i].mode * Port_Configuration[i].speed)) << ((Port_Configuration[i].pin - 8) * 4);
        }
    }
}
void Port_GetVersionInfo (Std_VersionInfoType* versioninfo)
{

}
void Port_SetPinMode (Port_PinType Pin, Port_PinModeType Mode)
{
    if (Port_Configuration[Pin].pin < 8)
    {
        Dio_Port[Port_Configuration[Pin].port]->CRL &= 
        ~((0x10) << (Port_Configuration[Pin].pin * 4));
        Dio_Port[Port_Configuration[Pin].port]->CRL |= Mode << ((Port_Configuration[Pin].pin * 4) + 2);
    }
    else
    {
        Dio_Port[Port_Configuration[Pin].port]->CRH &= ~((0x10) << ((Port_Configuration[Pin].pin - 8) * 4));
        Dio_Port[Port_Configuration[Pin].port]->CRH |= Mode << (((Port_Configuration[Pin].pin - 8) * 4) + 2);
    }
}