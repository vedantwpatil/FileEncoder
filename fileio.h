#ifndef FILEIO_H
#define FILEIO_H

#include <stdint.h>
#include <stdio.h>

FILE *openFile(const char *filename, const char *mode);
void closeFile(FILE *file);
size_t readFile(FILE *file, void *buffer, size_t size);
size_t writeFile(FILE *file, const void *buffer, size_t size);

#endif // FILEIO_H
