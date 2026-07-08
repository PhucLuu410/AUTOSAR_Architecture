#include "Crypto_Cfg.h"

Crypto_DriverObjectType Crypto_DriverObject = {CRYPTO_OBJ_ID_HASH};

Crypto_ConfigType Crypto_Config = {
    1,
    &Crypto_DriverObject,
};