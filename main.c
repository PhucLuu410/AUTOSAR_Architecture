// #include "stm32f103xb.h"
#include "Dio_Cfg.h"

#define DIO_LED     DIO_LED
#define DIO_BUTTON  DIO_BUTTON

void delay(volatile uint32_t t)
{
    while(t--);
}

int main(void)
{
    //Init clock
    //Config && Mode
    while (1)
    {
        if(Dio_ReadChannel(DIO_BUTTON))
        {
            Dio_WriteChannel(DIO_LED, 1);
        }
        else
        {
            Dio_WriteChannel(DIO_LED, 0);
        }

        delay(100000);
    }
}