#ifndef ENCODING_H
#define ENCODING_H

#include <stdint.h>
#include <stdio.h>

size_t encode_base64(const uint8_t *binary_data, size_t input_size,
                     char *output, size_t output_size);
size_t decode_base64(const char *text_data, size_t input_size, uint8_t *output,
                     size_t output_size);

#endif // !
