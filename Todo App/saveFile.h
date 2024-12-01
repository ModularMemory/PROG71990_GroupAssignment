// James Payne - prog71990 - group assignment - fall24

#pragma once

#include "todoList.h"

#include <stdbool.h>

bool saveFileExists();

bool saveListToFile(ptodo_list_t list);

bool loadListFromFile(ptodo_list_t* list);