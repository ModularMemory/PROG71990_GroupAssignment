// James Payne, Brandon Carr-Ansah, Nifemi Olapoju - prog71990 - group assignment - fall24

#include "todoItem.h"
#include "utils.h"

#include <stdlib.h>
#include <string.h>

todo_item_t* createTodoItem() {
    todo_item_t* item = (todo_item_t*)calloc(1, sizeof(todo_item_t));
    if (!item) {
        fprintf(stderr, "Faile to allocate new todo item.");
        return NULL;
    }

    return item;
}

void destroyTodoItem(todo_item_t* item) {
    if (item->name) {
        free(item->name);
    }

    if (item->description) {
        free(item->description);
    }

    free(item);
}

bool changeTodoItemName(todo_item_t* item, const char* name) {
    char* newName = cloneString(name);
    if (!newName) {
        return false;
    }

    if (item->name) {
        free(item->name);
    }

    item->name = newName;
    return true;
}

bool changeTodoItemDescription(todo_item_t* item, const char* description) {
    char* newDesc = cloneString(description);
    if (!newDesc) {
        return false;
    }

    if (item->description) {
        free(item->description);
    }

    item->description = newDesc;
    return true;
}

bool writeTodoItemToStream(FILE* fp, const todo_item_t item) {
    return false;
}

todo_item_t* readTodoItemFromStream(FILE* fp) {
    return NULL;
}

const char* getTodoItemName(const todo_item_t* item) {
    return item->name;
}

const char* getTodoItemDescription(const todo_item_t* item) {
    return item->description;
}