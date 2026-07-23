#ifndef OS_ARCH_H
#define OS_ARCH_H

#include "Std_GeneralTypes.h"

void SVC_RestoreContext(uint32 *sp);
void Arch_StartFirstTask(void);

#endif