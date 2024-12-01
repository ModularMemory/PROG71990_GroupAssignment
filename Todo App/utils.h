// James Payne - prog71990 - group assignment - fall24

#pragma once

#include <stdbool.h>
#include <stdio.h>

char* allocateString(size_t length);

char* cloneString(const char* origin);

char* readStringFromStream(FILE* fp);

bool writeStringToStream(FILE* fp, const char* str);