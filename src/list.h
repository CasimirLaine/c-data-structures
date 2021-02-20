#pragma once
#include <stdbool.h>

typedef unsigned char l_BYTE;

typedef struct {
	unsigned int bytes;
	unsigned int lenght;
	unsigned int allocatedBytes;
	void* data;
} List;

List* l_create(unsigned int bytes);

void* l_get(List*, unsigned int index);

void l_set(List*, l_BYTE value[], unsigned int index);

void l_add(List*, l_BYTE value[]);

void l_remove(List*, unsigned int index);

void l_clear(List*);

unsigned int l_size(List*);

bool l_empty(List*);

bool l_contains(List*, l_BYTE value[]);

unsigned int l_indexof(List*, l_BYTE value[]);
