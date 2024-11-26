// James Payne - prog71990 - group assignment - fall24

#include "main.h"
#include "loop.h"
#include "todoList.h"

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
    // TODO: Check if save file exists. If it does, load todo list from save file.
}

void saveTodoList(ptodo_list_t todoList) {
    // TODO: Save todo list to file.
}