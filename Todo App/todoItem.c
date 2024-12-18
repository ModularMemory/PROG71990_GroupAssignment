// James Payne - prog71990 - group assignment - fall24

#include "todoItem.h"
#include "utils.h"

#include <stdlib.h>
#include <string.h>

todo_item_t createTodoItem(void) {
    todo_item_t item = { 0 };

    return item;
}

void destroyTodoItem(todo_item_t item) {
    if (item.name) {
        free(item.name);
    }

    if (item.description) {
        free(item.description);
    }
}

todo_item_t copyTodoItem(const todo_item_t origin) {
    todo_item_t newItem = createTodoItem();

    changeTodoItemName(&newItem, origin.name);
    changeTodoItemDescription(&newItem, origin.description);

    return newItem;
}

bool changeTodoItemName(todo_item_t* item, const char* name) {
    char* newName = cloneString(name);
    if (!newName && name) { // If name is NULL then cloneString will return NULL, but we still want to update item.name
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
    if (!newDesc && description) { // If description is NULL then cloneString will return NULL, but we still want to update item.description
        return false;
    }

    if (item->description) {
        free(item->description);
    }

    item->description = newDesc;
    return true;
}

bool writeTodoItemToStream(FILE* fp, const todo_item_t item) {
    if (!writeStringToStream(fp, item.name)) {
        fprintf(stderr, "Error: Failed to write todo item name.\n");
    }

    if (!writeStringToStream(fp, item.description)) {
        fprintf(stderr, "Error: Failed to write todo item description.\n");
    }

    return true;
}

bool readTodoItemFromStream(FILE* fp, todo_item_t* item) {
    char* name = readStringFromStream(fp);
    if (!name) {
        fprintf(stderr, "Error: Failed to read todo item name.\n");
        return false;
    }

    char* desc = readStringFromStream(fp);
    if (!desc) {
        fprintf(stderr, "Error: Failed to read todo item description.\n");
        free(name);
        return false;
    }

    *item = createTodoItem();

    if (!changeTodoItemName(item, name)) {
        fprintf(stderr, "Error: Failed to set todo item name.\n");
        free(name);
        free(desc);
        destroyTodoItem(*item);
        return false;
    }

    free(name);

    if (!changeTodoItemDescription(item, desc)) {
        fprintf(stderr, "Error: Failed to set todo item description.\n");
        free(desc);
        destroyTodoItem(*item);
        return false;
    }

    free(desc);
    return true;
}

const char* getTodoItemName(const todo_item_t* item) {
    return item->name;
}

const char* getTodoItemDescription(const todo_item_t* item) {
    return item->description;
}

bool compareTodoItems(const todo_item_t a, const todo_item_t b) {
    if (strcmp(a.name, b.name) != 0) {
        return false;
    }

    return strcmp(a.description, b.description) == 0;
}

void printTodoItem(todo_item_t item) {
    printf("%s", item.name);

    if (item.description) {
        printf(" - %s", item.description);
    }

    printf("\n");
}