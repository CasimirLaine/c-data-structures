#pragma once
#include <stdbool.h>

typedef unsigned char lk_BYTE;

typedef struct Node {
	void* value;
	struct Node* next;
} Node;

typedef struct {
	unsigned int bytes;
	Node* head;
} LinkedList;


LinkedList* lk_create(unsigned int bytes);

void* lk_get(LinkedList*, unsigned int index);

void lk_add(LinkedList*, lk_BYTE value[]);