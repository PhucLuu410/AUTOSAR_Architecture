#include "Dio.h"

#define PIN0 (1 << 0)
#define PIN1 (1 << 1)
#define PIN2 (1 << 2)
#define PIN3 (1 << 3)
#define PIN4 (1 << 4)
#define PIN5 (1 << 5)
#define PIN6 (1 << 6)
#define PIN7 (1 << 7)
#define PIN8 (1 << 8)
#define PIN9 (1 << 9)
#define PIN10 (1 << 10)
#define PIN11 (1 << 11)
#define PIN12 (1 << 12)
#define PIN13 (1 << 13)
#define PIN14 (1 << 14)
#define PIN15 (1 << 15)
#define PIN16 (1 << 16)

#define PORTA GPIOA
#define PORTB GPIOB
#define PORTC GPIOC
#define PORTD GPIOD

typedef struct
{
    GPIO_TypeDef *port;
    Dio_ChannelType pin;
} Dio_ConfigTypeDef;

#define BUTTON 0
#define LED 1
