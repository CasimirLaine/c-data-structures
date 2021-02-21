#pragma once
#include <stdbool.h>

typedef unsigned char ar_BYTE;

typedef struct {
	unsigned int bytes;
	unsigned int lenght;
	unsigned int allocatedBytes;
	void* data;
} ArrayList;

ArrayList* ar_create(const unsigned int bytes);

void* ar_get(const ArrayList*, const unsigned int index);

void ar_set(const ArrayList*, const ar_BYTE value[], const unsigned int index);

void ar_add(ArrayList*, const ar_BYTE value[]);

void ar_remove(ArrayList*, unsigned int index);

void ar_clear(ArrayList*);

unsigned int ar_size(const ArrayList*);

bool ar_empty(const ArrayList*);

bool ar_contains(const ArrayList*, const ar_BYTE value[]);

unsigned int ar_indexof(const ArrayList*, const ar_BYTE value[]);
