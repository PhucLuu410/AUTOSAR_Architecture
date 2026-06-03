#include "LinIf.h"
#include "LinIf_Cfg.h"
#include "stm32f103xb.h"
#include "Std_Types.h"

static const LinIf_ConfigType *LinIf_LocalConfig;
static const LinTp_ConfigType *LinTp_LocalConfig;

void LinIf_Init(const LinIf_ConfigType *ConfigPtr)
{
    LinIf_LocalConfig = ConfigPtr;
}

void LinTp_Init(const LinTp_ConfigType *ConfigPtr)
{
    LinTp_LocalConfig = ConfigPtr;
}