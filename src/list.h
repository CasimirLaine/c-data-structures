#pragma once

typedef struct {
	unsigned int bytes;
	unsigned int lenght;
	unsigned int allocatedBytes;
	void* data;
} List;

List* l_create(unsigned int bytes);

void* l_get(List* lPtr, unsigned int index);

void l_add(List* lPtr, void* value);

void l_remove(List* lPtr, unsigned int index);

void l_clear(List* lPtr);

unsigned int l_size(List* lPtr);
