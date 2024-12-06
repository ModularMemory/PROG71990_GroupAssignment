// James Payne - prog71990 - group assignment - fall24

#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NULL_TERMINATOR_LEN 1

char* allocateString(size_t length) {
    size_t allocSize = length + NULL_TERMINATOR_LEN;
    char* str = (char*)calloc(allocSize, sizeof(char));
    if (!str) {
        fprintf(stderr, "Error: Failed to allocate string of size %zu.\n", allocSize * sizeof(char));
        return NULL;
    }

    return str;
}

char* cloneString(const char* origin) {
    if (!origin) {
        return NULL;
    }

    size_t len = strlen(origin);
    size_t allocSize = len + NULL_TERMINATOR_LEN;

    char* str = (char*)calloc(allocSize, sizeof(char));
    if (!str) {
        fprintf(stderr, "Error: Failed to allocate string of size %zu.\n", allocSize * sizeof(char));
        return NULL;
    }

    strncpy_s(str, allocSize, origin, len);

    return str;
}

char* readStringFromStream(FILE* fp) {
    size_t len = 0;
    if (fscanf_s(fp, "%zu\n", &len) != 1) {
        fprintf(stderr, "Failed to read string size.\n");
        return NULL;
    }

    char* str = allocateString(len);
    if (!str) {
        return NULL;
    }

    if (fread(str, sizeof(char), len, fp) != len) {
        fprintf(stderr, "Failed to read string.\n");
        free(str);
        return NULL;
    }

    return str;
}

bool writeStringToStream(FILE* fp, const char* str) {
    size_t len = strlen(str);
    if (fprintf(fp, "%zu\n", len) == 0) {
        fprintf(stderr, "Failed to write string length.\n");
        return false;
    }

    if (fwrite(str, sizeof(char), len, fp) != len) {
        fprintf(stderr, "Failed to write string.\n");
        return false;
    }

    return true;
}