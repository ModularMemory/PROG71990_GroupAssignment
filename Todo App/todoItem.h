// James Payne - prog71990 - group assignment - fall24

#pragma once

#include <stdbool.h>
#include <stdio.h>

typedef struct todo_item {
    char* name;
    char* description;
} todo_item_t;

todo_item_t createTodoItem(void);

void destroyTodoItem(todo_item_t item);

todo_item_t copyTodoItem(const todo_item_t origin);

bool changeTodoItemName(todo_item_t* item, const char* name);

bool changeTodoItemDescription(todo_item_t* item, const char* description);

bool writeTodoItemToStream(FILE* fp, todo_item_t item);

bool readTodoItemFromStream(FILE* fp, todo_item_t* item);

/// <summary>
/// Gets the name of the todo item. The return value may be NULL.
/// </summary>
const char* getTodoItemName(const todo_item_t* item);

/// <summary>
/// Gets the description of the todo item. The return value may be NULL.
/// </summary>
const char* getTodoItemDescription(const todo_item_t* item);

bool compareTodoItems(todo_item_t a, todo_item_t b);

void printTodoItem(todo_item_t item);