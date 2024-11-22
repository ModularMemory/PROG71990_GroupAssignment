// James Payne, Brandon Carr-Ansah, Nifemi Olapoju - prog71990 - group assignment - fall24

#pragma once

#include "todoItem.h"

typedef struct todo_list {
    todo_item_t item;
    struct todo_list* next;
} todo_list_t, *ptodo_list_t;

bool addTodoItem(ptodo_list_t* list, todo_item_t item);

bool insertTodoitem(ptodo_list_t* list, todo_item_t item, size_t index);

bool removeTodoItem(ptodo_list_t* list, todo_item_t item);

bool copyTodoItemAtIndex(const ptodo_list_t list, size_t index, todo_item_t* item);

void printTodoList(ptodo_list_t list);

void clearTodoList(ptodo_list_t* list);

void destroyTodoList(ptodo_list_t list);