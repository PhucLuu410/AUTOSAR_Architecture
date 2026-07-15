#include "Det.h"

volatile uint16 Det_LastModuleId;
volatile uint8 Det_LastApiId;
volatile uint8 Det_LastErrorId;

Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId)
{
    Det_LastModuleId = ModuleId;
    Det_LastApiId = ApiId;
    Det_LastErrorId = ErrorId;
    while (1)
        ;

    return E_OK;
}