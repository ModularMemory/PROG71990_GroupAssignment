// James Payne, Brandon Carr-Ansah, Nifemi Olapoju - prog71990 - group assignment - fall24

#include "loop.h"
#include "userInput.h"

#include <ctype.h>
#include <stdbool.h>

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
        break;
    case 'b': // Update a task
        break;
    case 'c': // Delete a task
        break;
    case 'd': // Show a task
        break;
    case 'e': // Show a range of tasks
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
        fprintf(stderr, "Error: invalid option '%c'\n", option);
        break;
    }

    return 0;
}