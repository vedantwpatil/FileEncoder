#include "../include/encoding.h"
#include <string.h>

size_t encode_base64(const uint8_t *input, size_t input_length, char *output,
                     size_t output_size) {
  size_t i = 0, j = 0;
  uint32_t octet_a, octet_b, octet_c, triple;

  static const char base64_chars[] =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

  if (output_size == 0) {
    return 0;
  }

  while (i < input_length) {

    // Check to see for output buffer overflow
    if (j + 4 > output_size) {
      return 0;
    }

    octet_a = i < input_length ? input[i++] : 0;
    octet_b = i < input_length ? input[i++] : 0;
    octet_c = i < input_length ? input[i++] : 0;

    triple = (octet_a << 16) + (octet_b << 8) + octet_c;

    output[j++] = base64_chars[(triple >> 18) & 0x3f];
    output[j++] = base64_chars[(triple >> 12) & 0x3f];
    output[j++] = base64_chars[(triple >> 6) & 0x3f];
    output[j++] = base64_chars[triple & 0x3f];
  }

  // Padding
  if (input_length % 3 > 0) {
    for (int k = 0; k < 3 - (input_length % 3); k++) {
      output[j - k - 1] = '=';
    }
  }

  // Null terminate if there's space
  if (j < output_size) {
    output[j] = '\0';
  }

  return j;
}

size_t decode_base64(const char *input, size_t input_length, uint8_t *output,
                     size_t output_size) {

  // First, create a lookup table for quick conversion
  // of Base64 characters to their 6-bit values
  static uint8_t lookup[256] = {0};
  static int table_initialized = 0;

  if (!table_initialized) {
    const char *base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    for (int i = 0; i < 64; i++) {
      lookup[(unsigned char)base64_chars[i]] = i;
    }
    table_initialized = 1;
  }

  size_t i = 0, j = 0;
  uint32_t sextet_a, sextet_b, sextet_c, sextet_d, triple;

  while (i < input_length) {
    // Ensure we have enough space in the output buffer
    if (j + 3 > output_size)
      return 0; // Not enough space

    // Get 4 characters and their respective 6-bit values
    sextet_a = input[i] == '=' ? 0 & i++ : lookup[(unsigned char)input[i++]];
    sextet_b = input[i] == '=' ? 0 & i++ : lookup[(unsigned char)input[i++]];
    sextet_c = input[i] == '=' ? 0 & i++ : lookup[(unsigned char)input[i++]];
    sextet_d = input[i] == '=' ? 0 & i++ : lookup[(unsigned char)input[i++]];

    // Combine 6-bit values into a 24-bit number
    triple = (sextet_a << 18) + (sextet_b << 12) + (sextet_c << 6) + sextet_d;

    // Extract and store the original bytes
    if (j < output_size)
      output[j++] = (triple >> 16) & 0xFF;
    if (j < output_size)
      output[j++] = (triple >> 8) & 0xFF;
    if (j < output_size)
      output[j++] = triple & 0xFF;
  }

  return j; // Return the number of bytes written
}
