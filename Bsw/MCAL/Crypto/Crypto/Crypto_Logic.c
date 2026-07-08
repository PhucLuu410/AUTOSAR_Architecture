#include "Std_GeneralTypes.h"
#include "Crypto_GeneralTypes.h"
#include "Crypto_Logic.h"

void SHA256_Add_Padding(uint8 *DataIn, uint8 Length, uint8 *DataOut)
{
    for (uint8 i = 0; i < 64; i++)
    {
        DataOut[i] = 0;
    }

    for (uint8 i = 0; i < Length; i++)
    {
        DataOut[i] = DataIn[i];
    }

    DataOut[Length] = 0x80;
    uint64 total_bits = (uint64)Length * 8;
    DataOut[63] = (uint8)(total_bits & 0xFF);
}

void SHA256_Message_Expansion(uint8 *DataIn, uint32 *W)
{
    for (uint8 i = 0; i < 16; i++)
    {
        W[i] = (DataIn[i * 4] << 24) | (DataIn[i * 4 + 1] << 16) | (DataIn[i * 4 + 2] << 8) | DataIn[i * 4 + 3];
    }

    for (uint8 i = 16; i < 64; i++)
    {
        uint32 W0 = W[i - 15];
        uint32 W1 = W[i - 2];

        uint32 sigma0 = ((W0 >> 7) | (W0 << (32 - 7))) ^ ((W0 >> 18) | (W0 << (32 - 18))) ^ (W0 >> 3);
        uint32 sigma1 = ((W1 >> 17) | (W1 << (32 - 17))) ^ ((W1 >> 19) | (W1 << (32 - 19))) ^ (W1 >> 10);
        W[i] = W[i - 16] + sigma0 + W[i - 7] + sigma1;
    }
}

void SHA256_Compression_Function(uint32 *W, uint32 *HashOut)
{
    static const uint32 K[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

    uint32 H0 = 0x6a09e667;
    uint32 H1 = 0xbb67ae85;
    uint32 H2 = 0x3c6ef372;
    uint32 H3 = 0xa54ff53a;
    uint32 H4 = 0x510e527f;
    uint32 H5 = 0x9b05688c;
    uint32 H6 = 0x1f83d9ab;
    uint32 H7 = 0x5be0cd19;

    uint32 a = H0;
    uint32 b = H1;
    uint32 c = H2;
    uint32 d = H3;
    uint32 e = H4;
    uint32 f = H5;
    uint32 g = H6;
    uint32 h = H7;

    for (uint8 i = 0; i < 64; i++)
    {
        uint32 BIG_SIGMA0 = ((a >> 2) | (a << (32 - 2))) ^
                            ((a >> 13) | (a << (32 - 13))) ^
                            ((a >> 22) | (a << (32 - 22)));

        uint32 BIG_SIGMA1 = ((e >> 6) | (e << (32 - 6))) ^
                            ((e >> 11) | (e << (32 - 11))) ^
                            ((e >> 25) | (e << (32 - 25)));

        uint32 ch = (e & f) ^ (~e & g);
        uint32 maj = (a & b) ^ (a & c) ^ (b & c);

        uint32 T1 = h + BIG_SIGMA1 + ch + K[i] + W[i];
        uint32 T2 = BIG_SIGMA0 + maj;

        h = g;
        g = f;
        f = e;
        e = d + T1;
        d = c;
        c = b;
        b = a;
        a = T1 + T2;
    }

    HashOut[0] = H0 + a;
    HashOut[1] = H1 + b;
    HashOut[2] = H2 + c;
    HashOut[3] = H3 + d;
    HashOut[4] = H4 + e;
    HashOut[5] = H5 + f;
    HashOut[6] = H6 + g;
    HashOut[7] = H7 + h;
}

void SHA256_Compute(uint8_t *DataIn, uint8_t Length, uint32_t *HashOut)
{
    uint8_t DataOut[64];
    uint32_t W[64];

    SHA256_Add_Padding(DataIn, Length, DataOut);
    SHA256_Message_Expansion(DataOut, W);
    SHA256_Compression_Function(W, HashOut);
}