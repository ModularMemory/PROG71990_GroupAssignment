// James Payne - prog71990 - group assignment - fall24
// Brandon - prog71990 - group assignment - fall24
// Nifemi Olapoju - prog71990 - group assignment - fall24


#include "todoList.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static ptodo_list_t createTodoListNode(todo_item_t item) {
    ptodo_list_t newNode = (ptodo_list_t)malloc(sizeof(todo_list_t));
    if (!newNode) {
        fprintf(stderr, "Failed to allocate new todo list node.\n");
        return NULL;
    }

    newNode->item = copyTodoItem(item);

    return newNode;
}

bool addTodoItem(ptodo_list_t* list, todo_item_t item) {
    if (!list) {
        return false;
    }

    ptodo_list_t newNode = createTodoListNode(item);
    if (!newNode) {
        return false;
    }

    ptodo_list_t current = *list;
    if (current == NULL) {
        // List is empty, new node becomes the head
        newNode->next = current;
        *list = newNode;
    }
    else {
        // List has contents, add node to the end
        while (current->next != NULL) {
            current = current->next;
        }

        current->next = newNode;
        newNode->next = NULL;
    }

    return true;
}

bool updateTodoItemByIndex(ptodo_list_t* list, size_t index, const char* newName, const char* newDescription) {
    if (!list || !*list || !newName || !newDescription) {
        return false;
    }

    ptodo_list_t current = *list;
    size_t i = 0;

    while (current != NULL) {
        if (i == index) {
            if (!changeTodoItemName(&current->item, newName) ||
                !changeTodoItemDescription(&current->item, newDescription)) {
                return false;
            }
            return true;
        }
        current = current->next;
        i++;
    }

    fprintf(stderr, "Error: No task at index %zu\n", index);
    return false;
}

bool updateTodoItemByName(ptodo_list_t* list, const char* name, const char* newName, const char* newDescription) {
    if (!list || !*list || !name || !newName || !newDescription) {
        return false;
    }

    ptodo_list_t current = *list;

    while (current != NULL) {
        if (strcmp(current->item.name, name) == 0) {
            if (!changeTodoItemName(&current->item, newName) ||
                !changeTodoItemDescription(&current->item, newDescription)) {
                return false;
            }
            return true;
        }
        current = current->next;
    }

    fprintf(stderr, "Error: No task with name '%s'\n", name);
    return false;
}

bool deleteTodoItemByIndex(ptodo_list_t* list, size_t index) {
    if (!list || !*list) {
        return false;
    }

    ptodo_list_t current = *list, prev = NULL;
    size_t i = 0;

    while (current != NULL) {
        if (i == index) {
            if (prev == NULL) {
                *list = current->next; //Deleting head
            }
            else {
                prev->next = current->next;
            }
            destroyTodoItem(current->item);
            free(current);
            return true;
        }
        prev = current;
        current = current->next;
        i++;
    }

    fprintf(stderr, "Error: No task at index %zu\n", index);
    return false;
}

bool deleteTodoItemByName(ptodo_list_t* list, const char* name) {
    if (!list || !*list || !name) {
        return false;
    }

    ptodo_list_t current = *list, prev = NULL;

    while (current != NULL) {
        if (strcmp(current->item.name, name) == 0) {
            if (prev == NULL) {
                *list = current->next; //Deleting head
            }
            else {
                prev->next = current->next;
            }
            destroyTodoItem(current->item);
            free(current);
            return true;
        }
        prev = current;
        current = current->next;
    }

    fprintf(stderr, "Error: No task with name '%s'\n", name);
    return false;
}

bool insertTodoItem(ptodo_list_t* list, todo_item_t item, size_t index) {
    return false;
}

bool removeTodoItem(ptodo_list_t* list, todo_item_t item) {
    if (!list || !*list) {
        return false;
    }

    // Check list head
    ptodo_list_t current = *list;
    if (compareTodoItems(current->item, item)) {
        *list = current->next;

        destroyTodoItem(current->item);
        free(current);
        
        return true;
    }

    // Check rest of list
    ptodo_list_t prev = current;
    current = current->next;
    while (current != NULL) {
        if (compareTodoItems(current->item, item)) {
            prev->next = current->next;

            destroyTodoItem(current->item);
            free(current);

            return true;
        }

        prev = current;
        current = current->next;
    }

    return false;
}

todo_item_t* getTodoItemAtIndex(ptodo_list_t list, size_t index) {
    ptodo_list_t current = list;
    size_t i = 0;

    while (current != NULL) {
        if (i == index) {
            return &current->item;
        }

        current = current->next;
        i++;
    }

    return NULL;
}

void printTodoList(ptodo_list_t list) {
    ptodo_list_t current = list;
    size_t i = 0;

    while (current != NULL) {
        printf("%zu. ", i + 1);
        printTodoItem(current->item);

        current = current->next;
        i++;
    }
}

void printTodoListRange(ptodo_list_t list, size_t rangeStart, size_t rangeLength) {
    ptodo_list_t current = list;
    size_t i = 0;
    size_t rangeEnd = rangeStart + rangeLength;

    while (current != NULL) {
        if (i >= rangeStart) {
            printf("%zu. ", i + 1);
            printTodoItem(current->item);

            if (i >= rangeEnd) {
                break;
            }
        }

        current = current->next;
        i++;
    }
}

void clearTodoList(ptodo_list_t* list) {
    if (!list) {
        return;
    }

    destroyTodoList(*list);
    *list = NULL;
}

void destroyTodoList(ptodo_list_t list) {
    ptodo_list_t current = list;
    while (current != NULL) {
        ptodo_list_t temp = current;
        current = temp->next;

        destroyTodoItem(temp->item);
        free(temp);
    }
}

bool searchTodoItem(ptodo_list_t list, const char* name) {
    if (!list || !name) {
        return false;
    }

    ptodo_list_t current = list;
    size_t index = 0;

    while (current != NULL) {
        if (strcmp(current->item.name, name) == 0) {
            printf("Task found at position %zu:\n", index + 1);
            printTodoItem(current->item);
            return true;
        }
        current = current->next;
        index++;
    }

    return false;
}

size_t getListLength(ptodo_list_t list) {
    size_t len = 0;
    for (ptodo_list_t current = list; current != NULL; current = current->next) {
        len++;
    }

    return len;
}

bool writeTodoListToStream(FILE* fp, ptodo_list_t list) {
    size_t listLen = getListLength(list);
    if (fprintf(fp, "%zu\n", listLen) == 0) {
        fprintf(stderr, "Error: Failed to write list length.\n");
        return false;
    }

    for (ptodo_list_t current = list; current != NULL; current = current->next) {
        if (!writeTodoItemToStream(fp, current->item)) {
            fprintf(stderr, "Error: Failed to write todo item.\n");
            return false;
        }
    }

    return true;
}

bool readTodoListFromStream(FILE* fp, ptodo_list_t* list) {
    size_t listLen = 0;
    if (fscanf_s(fp, "%zu\n", &listLen) != 1) {
        fprintf(stderr, "Error: Failed to read list length.\n");
        return false;
    }

    for (size_t i = 0; i < listLen; i++) {
        todo_item_t item;
        if (!readTodoItemFromStream(fp, &item)) {
            fprintf(stderr, "Error: Failed to read todo item.\n");
            return false;
        }

        if (!addTodoItem(list, item)) {
            fprintf(stderr, "Error: Failed to add todo item.\n");
            destroyTodoItem(item);
            return false;
        }

        destroyTodoItem(item);
    }

    return true;
}