#include <math.h>
#include <string.h>
#include "Std_GeneralTypes.h"

#define AES128_BLOCK_SIZE 16

void AES128_MAC_Generate(const uint8 *InputData, uint16_t InputLen, const uint8 *Key, uint8 *OutputMac);
uint8_t AES128_MAC_Verify(const uint8 *InputData, uint16_t InputLen, const uint8 *Key, const uint8 *ExpectedMac);