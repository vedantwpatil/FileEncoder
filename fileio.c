#include "fileio.h"
#include <stdio.h>

// Used to open a file and returns a FILE pointer
FILE *openFile(const char *filename, const char *mode) {
  // Implementing error handling
  FILE *file = fopen(filename, mode);
  if (file == NULL) {
    printf("The file is null and unable to be opened");
  }
  return file;
};

// Closes an open file
void closeFile(FILE *file) {
  if (file != NULL) {
    if (fclose(file) != 0) {
      printf("The file is unable to be closed ");
    }
  }
}

// Reads data from a file into memory
size_t readFile(FILE *file, void *buffer, size_t size) {
  return fread(buffer, 1, size, file);
};

// Writes data from memory into the file
size_t writeFile(FILE *file, const void *buffer, size_t size) {
  return fwrite(buffer, 1, size, file);
};
