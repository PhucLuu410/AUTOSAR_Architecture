#include "Crypto_Cfg.h"

Crypto_DriverObjectType Crypto_DriverObject[] = {
    {.Crypto_DriverObjectId = CRYPTO_OBJ_ID_SW},
    {.Crypto_DriverObjectId = CRYPTO_OBJ_ID_HW},
};

static uint8 Key0[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};

Crypto_ConfigType Crypto_Config = {
    1,
    Crypto_DriverObject,
};

KeyIdConfig KeyId[] = {
    {.KeyId = 0, .KeyLength = 16, .KeyData = Key0},
};
