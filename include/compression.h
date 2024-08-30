#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <stddef.h>
#include <stdint.h>

size_t compressRLE(const uint8_t *input, size_t inputSize, uint8_t *output,
                   size_t outputSize);
size_t decompressRLE(const uint8_t *input, size_t inputSize, uint8_t *output,
                     size_t outputSize);

#endif
