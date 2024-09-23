#include "../src/compression.c"
#include "../src/encoding.c"
#include "../src/fileio.c"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // Check for correct number of arguments
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
    return 1;
  }

  const char *input_file = argv[1];
  const char *output_file = argv[2];

  // Read input file
  FILE *input = openFile(input_file, "rb");
  if (!input) {
    fprintf(stderr, "Error: Could not open input file %s\n", input_file);
    return 1;
  }

  // Get file size
  fseek(input, 0, SEEK_END);
  long file_size = ftell(input);
  fseek(input, 0, SEEK_SET);

  // Allocate memory for file content
  uint8_t *file_content = (uint8_t *)malloc(file_size);
  if (!file_content) {
    fprintf(stderr, "Error: Memory allocation failed\n");
    closeFile(input);
    return 1;
  }

  // Read file content
  if (readFile(input, file_content, file_size) != file_size) {
    fprintf(stderr, "Error: Failed to read input file\n");
    free(file_content);
    closeFile(input);
    return 1;
  }
  closeFile(input);

  // Compress data
  uint8_t *compressed_data =
      (uint8_t *)malloc(file_size * 2); // Worst case scenario
  size_t compressed_size =
      compressRLE(file_content, file_size, compressed_data, file_size * 2);

  // Encode compressed data
  size_t encoded_size =
      (compressed_size * 4 / 3) + 4; // Base64 encoding size estimation
  char *encoded_data = (char *)malloc(encoded_size);
  size_t actual_encoded_size = encode_base64(compressed_data, compressed_size,
                                             encoded_data, encoded_size);

  // Write encoded data to output file
  FILE *output = openFile(output_file, "w");
  if (!output) {
    fprintf(stderr, "Error: Could not open output file %s\n", output_file);
    free(file_content);
    free(compressed_data);
    free(encoded_data);
    return 1;
  }

  if (writeFile(output, encoded_data, actual_encoded_size) !=
      actual_encoded_size) {
    fprintf(stderr, "Error: Failed to write output file\n");
    closeFile(output);
    free(file_content);
    free(compressed_data);
    free(encoded_data);
    return 1;
  }
  closeFile(output);

  // Clean up
  free(file_content);
  free(compressed_data);
  free(encoded_data);

  printf("File successfully encoded and saved to %s\n", output_file);
  return 0;
}
