#include "stm32f103xb.h"
#include "Dio_Cfg.h"

const Dio_ChannelConfigType Dio_ChannelConfig[] =
{
    [DIO_LED]    = {PORTA_ID, PIN_0},
    [DIO_BUTTON] = {PORTB_ID, PIN_3}
};
