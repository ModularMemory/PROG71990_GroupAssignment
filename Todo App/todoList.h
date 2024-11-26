// James Payne - prog71990 - group assignment - fall24
//Brandon - prog71990 - group assignment - fall24

#pragma once

#include "todoItem.h"

typedef struct todo_list {
    todo_item_t item;
    struct todo_list* next;
} todo_list_t, *ptodo_list_t;

bool addTodoItem(ptodo_list_t* list, todo_item_t item);

bool updateTodoItem(ptodo_list_t* list, const char* taskName, const char* newName, const char* newDescription);

bool deleteTodoItem(ptodo_list_t* list, const char* taskName);

bool insertTodoitem(ptodo_list_t* list, todo_item_t item, size_t index);

bool removeTodoItem(ptodo_list_t* list, todo_item_t item);

todo_item_t* getTodoItemAtIndex(ptodo_list_t list, size_t index);

void printTodoList(ptodo_list_t list);

void printTodoListRange(ptodo_list_t list, size_t rangeStart, size_t rangeLength);

void clearTodoList(ptodo_list_t* list);

void destroyTodoList(ptodo_list_t list);