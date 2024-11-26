// James Payne - prog71990 - group assignment - fall24
//Brandon - prog71990 - group assignment - fall24
//Nifemi Olapoju - prog71990 - group assignment - fall24


#include "userInput.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>

#define STR_BUFFER_LEN 256

// https://stackoverflow.com/a/7898516
static void flushStdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int getUserInt(int* userInt) {
    if (scanf_s("%d", userInt) != 1) {
        fprintf(stderr, "Error: Invalid input.\n");
        return 1;
    }

    flushStdin();

    return 0;
}

int getUserSizePair(size_t* userSizeA, size_t* userSizeB) {
    if (scanf_s("%zu%*[, ]%zu", userSizeA, userSizeB) != 2) {
        fprintf(stderr, "Error: Invalid input.\n");
        return 1;
    }

    flushStdin();

    return 0;
}

int getUserChar(char* userChar) {
    int c = getchar();
    if (c == EOF) {
        fprintf(stderr, "Error: Unexpected EOF.\n");
        return 1;
    }

    // If we got a newline, then flushing will require reading another newline,
    // which means the user will need to press enter again, which is not ideal.
    if (c != '\n') {
        flushStdin();
    }

    *userChar = (char)c;
    return 0;
}

char* getUserString(void) {
    char buff[STR_BUFFER_LEN] = { 0 };
    if (fgets(buff, STR_BUFFER_LEN, stdin) == NULL) {
        return NULL;
    }

    buff[strcspn(buff, "\n")] = '\0'; // Trim newline

    return cloneString(buff);
}