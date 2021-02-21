#pragma once
#include <stdbool.h>
#include "arlist.h"

typedef ar_BYTE st_BYTE;

typedef ArrayList Stack;

Stack* st_create(const unsigned int bytes);

void st_push(Stack*, const st_BYTE value[]);

void* st_pop(Stack*);

void* st_peek(Stack*);

bool st_empty(Stack*);
