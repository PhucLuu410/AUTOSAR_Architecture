#include "Crypto_Cfg.h"

Crypto_DriverObjectType Crypto_DriverObject[] = {
    {.Crypto_DriverObjectId = CRYPTO_OBJ_ID_SW_HASH},
    {.Crypto_DriverObjectId = CRYPTO_OBJ_ID_SW_SIGNATURE},
    {.Crypto_DriverObjectId = CRYPTO_OBJ_ID_SW_AES},
};

Crypto_ConfigType Crypto_Config = {
    1,
    Crypto_DriverObject,
};