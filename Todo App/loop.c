// James Payne - prog71990 - group assignment - fall24
// Brandon - prog71990 - group assignment - fall24
// Nifemi Olapoju - prog71990 - group assignment - fall24

#include "loop.h"
#include "userInput.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int runLoop(ptodo_list_t* todoList) {
    bool loop = true;
    do {
        printMenu();

        char option;
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
        if (addTask(todoList) != 0) {
            return 1;
        }
        break;
    case 'b': // Update a task
        updateTask(todoList);
        break;
    case 'c': // Delete a task
        deleteTask(todoList);
        break;
    case 'd': // Show a task
      /*  printf("Enter the name of the task to show: ");
        char* taskName = getUserString();
        if (!taskName) {
            fprintf(stderr, "Failed to read the task name.\n");
            break;
        }

        if (!searchTodoItem(*todoList, taskName)) {
            printf("Task '%s' not found.\n", taskName);
        }

        free(taskName);*/

        if (showTaskByName(todoList) != 0) {
            return 1;
        }
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

        printf("Enter the name of the task to search: ");
        char* searchName = getUserString();
        if (!searchName) {
            fprintf(stderr, "Failed to read the task name.\n");
            break;
        }
        if (!searchTodoItem(*todoList, searchName)) {
            printf("Task '%s' not found.\n", searchName);
        }
        free(searchName);

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

    free(name);

    if (!changeTodoItemDescription(&item, desc)) {
        free(desc);
        destroyTodoItem(item);
        return 1;
    }

    free(desc);

    if (!addTodoItem(todoList, item)) {
        destroyTodoItem(item);
        return 1;
    }

    destroyTodoItem(item);
    return 0;
}

void updateTask(ptodo_list_t* todoList) {
    if (!todoList) {
        fprintf(stderr, "Error: todoList is NULL.\n");
        return;
    }

    printf("Do you want to update by index or name? (type 'index' or 'name' to choose): ");
    char updateChoice;
    if (getUserChar(&updateChoice) == 0) {
        if (updateChoice == 'i') {
            printf("Enter the index of the task to update: ");
            size_t index;
            if (getUserSizePair(&index, NULL) == 0) {
                printf("Enter the new name: ");
                char* newName = getUserString();
                printf("Enter the new description: ");
                char* newDesc = getUserString();

                if (updateTodoItemByIndex(todoList, index - 1, newName, newDesc)) {
                    printf("Task updated successfully.\n");
                }
                else {
                    fprintf(stderr, "Failed to update the task.\n");
                }

                free(newName);
                free(newDesc);
            }
        }
        else if (updateChoice == 'n') {
            printf("Enter the name of the task to update: ");
            char* taskName = getUserString();
            printf("Enter the new name: ");
            char* newName = getUserString();
            printf("Enter the new description: ");
            char* newDesc = getUserString();

            if (updateTodoItemByName(todoList, taskName, newName, newDesc)) {
                printf("Task updated successfully.\n");
            }
            else {
                fprintf(stderr, "Failed to update the task.\n");
            }

            free(taskName);
            free(newName);
            free(newDesc);
        }
    }
}

void deleteTask(ptodo_list_t* todoList) {
    if (!todoList) {
        fprintf(stderr, "Error: todoList is NULL.\n");
        return;
    }

    printf("Do you want to delete by index or name? (type 'index' or 'name' to choose): ");
    char deleteChoice;
    if (getUserChar(&deleteChoice) == 0) {
        if (deleteChoice == 'i') {
            printf("Enter the index of the task to delete: ");
            size_t index;
            if (getUserSizePair(&index, NULL) == 0) {
                if (deleteTodoItemByIndex(todoList, index - 1)) {
                    printf("Task deleted successfully.\n");
                }
                else {
                    fprintf(stderr, "Failed to delete the task.\n");
                }
            }
        }
        else if (deleteChoice == 'n') {
            printf("Enter the name of the task to delete: ");
            char* taskName = getUserString();
            if (deleteTodoItemByName(todoList, taskName)) {
                printf("Task deleted successfully.\n");
            }
            else {
                fprintf(stderr, "Failed to delete the task.\n");
            }
            free(taskName);
        }
    }
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

int showTaskByName(ptodo_list_t* todoList) {
    if (!todoList || !*todoList) {
        fprintf(stderr, "Error: todoList is NULL or empty.\n");
        return 1;
    }

    printf("Enter the name of the task to show: ");
    char* taskName = getUserString();
    if (!taskName) {
        fprintf(stderr, "Failed to read the task name.\n");
        return 1;
    }

    if (!searchTodoItem(*todoList, taskName)) {
        printf("Task '%s' not found.\n", taskName);
    }

    free(taskName);
    return 0;
}

