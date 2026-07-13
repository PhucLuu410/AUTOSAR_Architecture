#include "Crypto_Cfg.h"

Crypto_DriverObjectType Crypto_DriverObject[] = {
    {.Crypto_DriverObjectId = CRYPTO_OBJ_ID_SW},
    {.Crypto_DriverObjectId = CRYPTO_OBJ_ID_HW},
};

Crypto_ConfigType Crypto_Config = {
    1,
    Crypto_DriverObject,
};