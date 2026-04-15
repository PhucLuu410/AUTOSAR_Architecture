#include "Dio_Cfg.h"
#include "Std_Types.h"

void delay(volatile uint32_t t)
{
    while (t--)
        ;
}

int main(void)
{
    RCC->APB2ENR |= (1 << 2); // GPIOA
    RCC->APB2ENR |= (1 << 4); // GPIOC

    RCC->APB2ENR |= (1 << 0);

    GPIOA->CRL &= ~(0xF << (0 * 4));
    GPIOA->CRL |= (0x4 << (0 * 4));
    GPIOC->CRH &= ~(0xF << (5 * 4));
    GPIOC->CRH |= (0x2 << (5 * 4));

    while (1)
    {
        Dio_WriteChannel(LED, 1);
    }
}