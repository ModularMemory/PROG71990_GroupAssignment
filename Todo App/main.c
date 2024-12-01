// James Payne - prog71990 - group assignment - fall24

#include "main.h"
#include "loop.h"
#include "todoList.h"
#include "saveFile.h"

#include <stdio.h>

int main(void) {
    ptodo_list_t todoList = NULL;
    initTodoList(&todoList);

    if (runLoop(&todoList) != 0) {
        return 1;
    }

    saveTodoList(todoList);

    destroyTodoList(todoList);

    return 0;
}

void initTodoList(ptodo_list_t* todoList) {
    if (!saveFileExists()) {
        return;
    }

    printf("Loading list from file...\n");

    if (!loadListFromFile(todoList)) {
        fprintf(stderr, "Error: Failed to read list from file.\n");
        *todoList = NULL;
    }

    printf("\n");
}

void saveTodoList(ptodo_list_t todoList) {
    printf("Saving list to file...");

    if (!saveListToFile(todoList)) {
        fprintf(stderr, "Error: Failed to save list to file.\n");
    }
}