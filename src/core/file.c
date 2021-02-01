#include <stdio.h>
#include <malloc.h>

#include "file.h"

extern char* file_read_all(const char* path) {
    char* content = NULL;
    FILE* file = fopen(path, "r");

    if (file) {
        fseek(file, 0, SEEK_END);
        size_t size = ftell(file);
        rewind(file);

        content = (char*) malloc(sizeof(char) * size);
        fread(content, 1, size, file);
        fclose(file);
    }
    return content;
}
