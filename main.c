#include "Dio.h"
#include "Dio_Cfg.h"
#include "Port.h"
#include "Port_Cfg.h"

void delay(volatile uint32_t t)
{
    while (t--)
        ;
}

int main(void)
{
    RCC->APB2ENR |= (1 << 2);
    RCC->APB2ENR |= (1 << 4);
    RCC->APB2ENR |= (1 << 0);

    Port_Init(Port_Configuration);

    while (1)
    {
        Dio_WriteChannel(LED, 1);
        delay(1000000);
    }
}