#include "Dio_Cfg.h"
#include "Std_Types.h"
#include "Dio.h"
#include "Port.h"

void delay(volatile uint32_t t)
{
    while (t--)
        ;
}

Port_ConfigType Port_Configuration = {
    .port = PORT_C,
    .pin = 13,
    .mode = PORT_MODE_OUTPUT_10MHz,
    .cfg = PORT_CNF_GP_OUTPUT_PP
};

int main(void)
{
    RCC->APB2ENR |= (1 << 2); // GPIOA
    RCC->APB2ENR |= (1 << 4); // GPIOC

    RCC->APB2ENR |= (1 << 0);

    Port_Init(&Port_Configuration);

    while (1)
    {
        Dio_WriteChannel(LED, 1);
        delay(1000000);
        Dio_WriteChannel(LED, 0);
        delay(1000000);
    }
}