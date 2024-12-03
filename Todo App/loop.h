// James Payne - prog71990 - group assignment - fall24
// Brandon - prog71990 - group assignment - fall24
// Nifemi Olapoju - prog71990 - group assignment - fall24

#pragma once

#include "todoList.h"

int runLoop(ptodo_list_t* todoList);

void printMenu(void);

int parseOption(char option, ptodo_list_t* todoList);

int addTask(ptodo_list_t* list);

void updateTask(ptodo_list_t* todoList);

void deleteTask(ptodo_list_t* todoList);

int printTaskRange(ptodo_list_t list);

