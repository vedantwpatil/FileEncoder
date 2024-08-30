#include "fileio.c"
#include <assert.h>
#include <stdio.h>
#include <string.h>

// Create global variables which are used for testing
const char *testFileName = "";
const char *testContent = "This is a text file for testing file I/O functions.";

void testOpenFile() {
  FILE *file = openFile(testFileName, "r");
  assert(file != NULL);
  closeFile(file);

  file = openFile("non_existent_file.txt", "r");
  assert(file == NULL);
}

void testWriteFile() {
  FILE *file = openFile(testFileName, "w");
  assert(file != NULL);

  size_t bytesWritten = writeFile(file, testContent, strlen(testContent));
  assert(bytesWritten == strlen(testContent));

  closeFile(file);
}

void testReadFile() {
  FILE *file = openFile(testFileName, "r");
  assert(file != NULL);

  char buffer[100];
  size_t bytesRead = readFile(file, buffer, strlen(testContent));
  assert(bytesRead == strlen(testContent));
  assert(strncmp(buffer, testContent, bytesRead) == 0);

  closeFile(file);
}

int main() {
  testOpenFile();
  testWriteFile();
  testReadFile();
  printf("All tests passed successfully!\n");
  return 0;
}
