// James Payne, Brandon Carr-Ansah, Nifemi Olapoju - prog71990 - group assignment - fall24

#include "userInput.h"

#include <stdio.h>

// https://stackoverflow.com/a/7898516
static void flushStdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int getUserInt(int* userInt) {
    if (scanf_s("%d", userInt) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return 1;
    }

    flushStdin();

    return 0;
}

int getUserChar(char* userChar) {
    int c = getchar();
    if (c == EOF) {
        fprintf(stderr, "Error: unexpected EOF.\n");
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
    return NULL; // TODO
}