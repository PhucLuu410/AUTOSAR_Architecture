#ifndef OS_ARCH_H
#define OS_ARCH_H

#include "Std_GeneralTypes.h"

__attribute__((naked)) void SVC_RestoreContext(uint32 *sp);

#endif