#include "Dio.h"

#define PIN_0 1 << 0
#define PIN_1 1 << 1
#define PIN_2 1 << 2
#define PIN_3 1 << 3
#define PIN_4 1 << 4
#define PIN_5 1 << 5
#define PIN_6 1 << 6
#define PIN_7 1 << 7
#define PIN_8 1 << 8
#define PIN_9 1 << 9
#define PIN_10 1 << 10
#define PIN_11 1 << 11
#define PIN_12 1 << 12
#define PIN_13 1 << 13
#define PIN_14 1 << 14
#define PIN_15 1 << 15

#define PORT_A 0
#define PORT_B 1
#define PORT_C 2
#define PORT_D 3

typedef struct
{
    Dio_PortType Port;
    Dio_ChannelType Pin;
} Dio_TypeConfig;