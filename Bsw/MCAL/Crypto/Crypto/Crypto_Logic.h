#include "stdio.h"
#include "stdlib.h"

void SHA256_Add_Padding(uint8 *DataIn, uint8 Length, uint8 *DataOut);
void SHA256_Message_Expansion(uint8 *DataIn, uint32 *W);
void SHA256_Compression_Function(uint32 *W, uint32 *HashOut);
void SHA256_Compute(uint8_t *DataIn, uint8_t Length, uint32_t *HashOut);