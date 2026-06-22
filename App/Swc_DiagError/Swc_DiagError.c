#include "Swc_DiagError.h"
#include "stm32f103xb.h"

uint16 RPM_Data = 0;
uint8 Temp_Data = 0;

void Swc_Diag_MainFunction(void)
{
    Rte_Read_Diag_RPM(&RPM_Data);
    Rte_Read_Diag_Temp(&Temp_Data);
    if (RPM_Data > 3000)
    {
        GPIOC->ODR ^= GPIO_ODR_ODR13;
    }
}
