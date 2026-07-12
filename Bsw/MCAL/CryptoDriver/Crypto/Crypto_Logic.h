#include <math.h>
#include <string.h>
#include "Std_GeneralTypes.h"

void AES128_CBC_MAC_Generate(const uint8 *InputData, uint8 InputLen, const uint8 *Key, uint8 *OutputMac);
