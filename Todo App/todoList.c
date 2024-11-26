// James Payne - prog71990 - group assignment - fall24
//Brandon - prog71990 - group assignment - fall24
//Nifemi Olapoju - prog71990 - group assignment - fall24


#include "todoList.h"

#include <stdio.h>
#include <stdlib.h>

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

bool updateTodoItem(ptodo_list_t* list, const char* taskName, const char* newName, const char* newDescription) {
    if (!list || !*list || !taskName || !newName || !newDescription) {
        return false;
    }

    ptodo_list_t current = *list;

    while (current != NULL) {
        if (strcmp(current->item.name, taskName) == 0) {
            if (!changeTodoItemName(&current->item, newName)) {
                return false;
            }
            if (!changeTodoItemDescription(&current->item, newDescription)) {
                return false;
            }
            return true;
        }
        current = current->next;
    }

    fprintf(stderr, "Error: No task found with the name '%s'.\n", taskName);
    return false;
}

bool deleteTodoItem(ptodo_list_t* list, const char* taskName) {
    if (!list || !*list || !taskName) {
        return false;
    }

    ptodo_list_t current = *list, prev = NULL;

    while (current != NULL) {
        if (strcmp(current->item.name, taskName) == 0) {
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

    fprintf(stderr, "Error: No task found with the name '%s'.\n", taskName);
    return false;
}

bool insertTodoitem(ptodo_list_t* list, todo_item_t item, size_t index) {
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

