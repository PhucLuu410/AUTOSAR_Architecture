#include "stm32f103xb.h"
#include "Dio.h"

typedef struct
{
    GPIO_TypeDef *port;
    uint16 pin;
} Dio_ChannelConfigType;

const Dio_ChannelConfigType Dio_ChannelConfig[] =
    {
        {GPIOA, (1 << 5)}, // LED
        {GPIOB, (1 << 3)}  // BUTTON
};

GPIO_TypeDef *Dio_PortConfig[] =
    {
        GPIOA,
        GPIOB};