// James Payne - prog71990 - group assignment - fall24

#include "loop.h"
#include "userInput.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int runLoop(ptodo_list_t* todoList) {
    char option;
    bool loop = true;
    do {
        printMenu();

        if (getUserChar(&option) != 0) {
            continue;
        }

        loop = parseOption(option, todoList) == 0;

        printf("\n");
    } while (loop);

    return 0;
}

void printMenu(void) {
    printf("To choose a function, enter its letter label:\n"
    "a) Add a new task\n"
    "b) Update an existing task\n"
    "c) Delete an existing task\n"
    "d) Show a task\n"
    "e) Show a range of tasks\n"
    "f) Show all tasks\n"
    "g) Search for a task\n"
    "h) Clear all tasks\n"
    "i) Quit\n");
}

int parseOption(char option, ptodo_list_t* todoList) {
    switch (tolower(option)) {
    case 'a': // Add a task
        addTask(todoList);
        break;
    case 'b': // Update a task
        break;
    case 'c': // Delete a task
        break;
    case 'd': // Show a task
        break;
    case 'e': // Show a range of tasks
        if (printTaskRange(*todoList) != 0) {
            return 1;
        }
        break;
    case 'f': // Show all tasks
        printTodoList(*todoList);
        break;
    case 'g': // Search for a task
        break;
    case 'h': // Clear all tasks
        clearTodoList(todoList);
        break;
    case 'i': // Quit
        return 1;
    default:
        fprintf(stderr, "Error: Invalid option '%c'\n", option);
        break;
    }

    return 0;
}

int addTask(ptodo_list_t* todoList) {
    printf("Enter the name of your new task, or '-' to cancel: ");
    char* name = getUserString();
    if (!name) {
        return 1;
    }

    if (strcmp(name, "-") == 0) {
        free(name);
        return 0;
    }

    printf("Enter the description of your new task, or '-' to cancel: ");
    char* desc = getUserString();
    if (!desc) {
        free(name);
        return 1;
    }

    if (strcmp(desc, "-") == 0) {
        free(name);
        free(desc);
        return 0;
    }

    todo_item_t item = createTodoItem();
    if (!changeTodoItemName(&item, name)) {
        free(name);
        free(desc);
        destroyTodoItem(item);
        return 1;
    }

    if (!changeTodoItemDescription(&item, desc)) {
        free(name);
        free(desc);
        destroyTodoItem(item);
        return 1;
    }

    if (!addTodoItem(todoList, item)) {
        free(name);
        free(desc);
        destroyTodoItem(item);
        return 1;
    }

    free(name);
    free(desc);
    destroyTodoItem(item);
    return 0;
}

int printTaskRange(ptodo_list_t list) {
    printf("Enter the first and last task numbers you would like to print (a, b): ");
    size_t first, last;
    if (getUserSizePair(&first, &last) != 0) {
        return 1;
    }

    if (last < first) {
        fprintf(stderr, "Error: Invalid range.\n");
        return 0;
    }
    
    printTodoListRange(list, first - 1, last - first);

    return 0;
}