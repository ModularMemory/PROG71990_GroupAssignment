// James Payne - prog71990 - group assignment - fall24

#include "saveFile.h"

#include <stdio.h>

#define SAVE_FILE_NAME "todo.dat"

bool saveFileExists() {
    FILE* fp = fopen(SAVE_FILE_NAME, "r");
    if (!fp) {
        return false;
    }

    fclose(fp);
    return true;
}

bool saveListToFile(ptodo_list_t list) {
    FILE* fp = fopen(SAVE_FILE_NAME, "w");
    if (!fp) {
        fprintf(stderr, "Error: Failed to open save file for writing.\n");
        return false;
    }

    if (!writeTodoListToStream(fp, list)) {
        return false;
    }

    return true;
}

bool loadListFromFile(ptodo_list_t* list) {
    FILE* fp = fopen(SAVE_FILE_NAME, "r");
    if (!fp) {
        fprintf(stderr, "Error: Failed to open save file for reading.\n");
        return false;
    }

    if (!readTodoListFromStream(fp, list)) {
        return false;
    }

    return true;
}