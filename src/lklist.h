#pragma once
#include <stdbool.h>

typedef unsigned char lk_BYTE;

typedef struct lk_Node {
	void* value;
	struct lk_Node* next;
} lk_Node;

typedef struct {
	unsigned int lenght;
	unsigned int bytes;
	struct lk_Node* head;
} LinkedList;


LinkedList* lk_create(const unsigned int bytes);

void* lk_get(const LinkedList*, const unsigned int index);

void lk_set(LinkedList*, const lk_BYTE value[], const unsigned int index);

void lk_add(LinkedList*, const lk_BYTE value[]);

void lk_remove(LinkedList*, const unsigned int index);

void lk_clear(LinkedList*);

unsigned int lk_size(const LinkedList*);

bool lk_empty(const LinkedList*);

bool lk_contains(const LinkedList*, const lk_BYTE value[]);

unsigned int lk_indexof(const LinkedList*, const lk_BYTE value[]);
