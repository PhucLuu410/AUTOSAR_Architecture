.global Arch_StartFirstTask
.global SVC_Handler

Arch_StartFirstTask:
    svc #0


SVC_Handler:
    msr psp, r0 
    ldmia r0!, {r4-r11}
    msr psp, r0                       