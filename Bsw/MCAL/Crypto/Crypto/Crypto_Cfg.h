#ifndef CRYPTO_CFG_H
#define CRYPTO_CFG_H

#include "Crypto.h"

#define DECRYPT 0
#define ENCRYPT 1

#define SHA2 0
#define SHA3 1
#define AES 2

#define AES_ECB 0
#define AES_CBC 1
#define AES_GCM 2

#define SHA256 0
#define SHA512 1

extern Crypto_ConfigType Crypto_Config;

#endif