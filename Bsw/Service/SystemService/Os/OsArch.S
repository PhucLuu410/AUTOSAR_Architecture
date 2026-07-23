.syntax unified
.cpu cortex-m3
.thumb

.global Arch_StartFirstTask
.global SVC_Handler
.extern CurrentTask

Arch_StartFirstTask:
    svc #0

SVC_Handler:
    ldr r0, =CurrentTask    
    ldr r0, [r0]   
    ldr r0, [r0]                 
    ldmia r0!, {r4-r11}
    msr psp, r0
    ldr lr, =0xFFFFFFFD
    bx lr                   