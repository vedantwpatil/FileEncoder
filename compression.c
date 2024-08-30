#include "compression.h"
#include <string.h>

size_t compressRLE(const uint8_t *input, size_t inputSize, uint8_t *output,
                   size_t outputSize) {

  if (input == NULL || output == NULL || inputSize == 0 || outputSize == 0) {
    return 0; // Error handling
  }

  size_t inIndex = 0;
  size_t outIndex = 0;

  while (inIndex < inputSize) {
    uint8_t currentByte = input[inIndex];
    uint8_t count = 1;

    // Making sure that we are not bigger than the input size and that the
    // current and next byte are both the same type
    while (inIndex + 1 < inputSize && input[inIndex + 1] == currentByte &&
           count < 255) {
      inIndex++;
      count++;
    }

    // Write out to the output
    if (outIndex + 2 > outputSize) {
      return 0; // Output buffer fail
    }

    output[outIndex++] = count;
    output[outIndex++] = currentByte;

    inIndex++;
  }
  return outIndex;
};

size_t decompressRLE(const uint8_t *input, size_t inputSize, uint8_t *output,
                     size_t outputSize) {
  size_t inIndex = 0;
  size_t outIndex = 0;

  while (inIndex < inputSize) {

    // Checks to see if we have 2 bytes to read from
    if (inIndex + 1 >= inputSize) {
      break;
    }

    uint8_t count = input[inIndex++];
    uint8_t value = input[inIndex++];

    // Check to see if we have space
    if (count + outIndex > outputSize) {
      break;
    }

    for (uint8_t i = 0; i < count; i++) {
      output[outIndex++] = value;
    }
  }
  return outIndex;
};
