// James Payne, Brandon Carr-Ansah, Nifemi Olapoju - prog71990 - group assignment - fall24

#pragma once

#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NULL_TERMINATOR_LEN 1

char* cloneString(const char* origin) {
    if (!origin) {
        return NULL;
    }

    size_t len = strlen(origin);
    size_t allocSize = len + NULL_TERMINATOR_LEN;

    char* str = (char*)calloc(allocSize, sizeof(char));
    if (!str) {
        fprintf(stderr, "Failed to allocate string of size %zd.\n", allocSize);
        return NULL;
    }

    strncpy_s(str, allocSize, origin, len);

    return str;
}