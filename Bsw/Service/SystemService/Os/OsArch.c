#include "OsArch.h"

__attribute__((naked)) void SVC_RestoreContext(uint32 *sp)
{
    __asm volatile(
        "msr psp, r0          \n"
        "ldmia r0!, {r4-r11}  \n"
        "msr psp, r0          \n"

        "mov r0, #2           \n"
        "msr control, r0      \n"
        "isb                  \n"
        "LDR     LR, =0xFFFFFFFD      \n"
        "BX      LR                   \n");
}