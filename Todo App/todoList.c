// James Payne, Brandon Carr-Ansah, Nifemi Olapoju - prog71990 - group assignment - fall24

#include "todoList.h"

#include <stdio.h>
#include <stdlib.h>

bool addTodoItem(ptodo_list_t* list, todo_item_t item) {
    if (!list) {
        return false;
    }

    todo_list_t* newNode = (todo_list_t*)malloc(sizeof(todo_list_t));
    if (!newNode) {
        fprintf(stderr, "Failed to allocate new todo list node.\n");
        return false;
    }

    newNode->item = copyTodoItem(item);
    newNode->next = *list;
    *list = newNode;

    return true;
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
        destroyTodoItem(current->item);

        *list = current->next;
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

bool copyTodoItemAtIndex(const ptodo_list_t list, size_t index, todo_item_t* item) {
    ptodo_list_t current = list;
    size_t i = 0;

    while (current != NULL) {
        if (i == index) {
            *item = copyTodoItem(current->item);
            return true;
        }

        current = current->next;
        i++;
    }

    return false;
}

void printTodoList(ptodo_list_t list) {
    ptodo_list_t current = list;
    size_t i = 1;

    while (current != NULL) {
        printf("%zu. ", i);
        printTodoItem(current->item);

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
        free(temp);
    }
}