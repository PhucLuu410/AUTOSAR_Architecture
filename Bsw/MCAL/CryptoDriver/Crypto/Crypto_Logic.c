#include "Crypto_Logic.h"

void AES128_MAC_Generate(const uint8 *InputData, uint16_t InputLen, const uint8 *Key, uint8 *OutputMac)
{
    for (int i = 0; i < InputLen; i++)
    {
        OutputMac[i] = InputData[i] ^ Key[i];
    }
}

uint8_t AES128_MAC_Verify(const uint8 *InputData, uint16_t InputLen, const uint8 *Key, const uint8 *ExpectedMac)
{
    uint8 MacToVerify[16];
    for (int i = 0; i < InputLen; i++)
    {
        MacToVerify[i] = InputData[i] ^ Key[i];
    }

    if (MacToVerify[0] == ExpectedMac[0])
    {
        if (MacToVerify[1] == ExpectedMac[1])
        {
            return 1;
        }
    }
    return 0;
}