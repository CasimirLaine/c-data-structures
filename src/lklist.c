#include <stdio.h>
#include <stdlib.h>
#include "lklist.h"

LinkedList* lk_create(const unsigned int bytes) {
	LinkedList* lPtr = (LinkedList*) malloc(sizeof(LinkedList));
	if (lPtr != NULL) {
		lPtr->lenght = 0;
		lPtr->bytes = bytes;
		lPtr->head = NULL;
	}
	return lPtr;
}

lk_Node* allocateNode(unsigned int bytes) {
	lk_Node* ptr = malloc(sizeof(lk_Node));
	if (ptr != NULL) {
		ptr->value = malloc(bytes);
		ptr->next = NULL;
	}
	return ptr;
}

lk_Node* findNode(lk_Node* ptr, unsigned int index, unsigned int iter) {
	if (ptr == NULL) {
		return NULL;
	}
	if (index == iter) {
		return ptr;
	}
	return findNode(ptr->next, index, ++iter);
}

lk_Node* findLastNode(lk_Node* ptr) {
	if (ptr == NULL) {
		return NULL;
	}
	if (ptr->next != NULL) {
		return findLastNode(ptr->next);
	} else {
		return ptr;
	}
}

void assignToNode(lk_Node* ptr, const lk_BYTE value[], const unsigned int bytes) {
	for (unsigned int i = 0; i < bytes; i++) {
		*((lk_BYTE*) ptr->value + i) = (&(lk_BYTE) value)[i];
	}
}

void* lk_get(const LinkedList* lPtr, const unsigned int index) {
	if (lPtr == NULL) {
		return NULL;
	}
	if (index >= lPtr->lenght) {
		return NULL;
	}
	lk_Node* node = NULL;
	if (index == 0) {
		node = lPtr->head;
	} else {
		node = findNode(lPtr->head, index, 0);
	}
	if (node != NULL) {
		return node->value;
	}
	return NULL;
}

void lk_set(LinkedList* lPtr, const lk_BYTE value[], const unsigned int index) {
	if (lPtr == NULL) {
		return;
	}
	if (index >= lPtr->lenght) {
		return;
	}
	lk_Node* ptr = findNode(lPtr->head, index, 0);
	assignToNode(ptr, value, lPtr->bytes);
}

void lk_add(LinkedList* lPtr, const lk_BYTE value[]) {
	if (lPtr == NULL) {
		return;
	}
	if (lPtr->head == NULL) {
		lPtr->head = allocateNode(lPtr->bytes);
		assignToNode(lPtr->head, value, lPtr->bytes);
	} else {
		lk_Node* lastNode = findLastNode(lPtr->head);
		lastNode->next = allocateNode(lPtr->bytes);
		assignToNode(lastNode->next, value, lPtr->bytes);
	}
	lPtr->lenght++;
}

void lk_remove(LinkedList* lPtr, const unsigned int index) {
	if (lPtr == NULL) {
		return;
	}
	if (index >= lPtr->lenght) {
		return;
	}
	lk_Node* removed;
	if (index == 0) {
		removed = lPtr->head;
		lPtr->head = removed->next;
	} else {
		removed = findNode(lPtr->head, index, 0);
		lk_Node* previous = findNode(lPtr->head, index - 1, 0);
		previous->next = removed->next;
	}
	free(removed->value);
	free(removed);
	lPtr->lenght--;
}

void lk_clear(LinkedList* lPtr) {
	if (lPtr == NULL) {
		return;
	}
	while (lPtr->lenght > 0) {
		lk_remove(lPtr, 0);
	}
}

unsigned int lk_size(const LinkedList* lPtr) {
	if (lPtr == NULL) {
		return 0;
	}
	return lPtr->lenght;
}

bool lk_empty(const LinkedList* lPtr) {
	if (lPtr == NULL) {
		return true;
	}
	return lPtr->lenght == 0;
}

bool lk_contains(const LinkedList* lPtr, const lk_BYTE value[]) {
	if (lPtr == NULL) {
		return false;
	}
	return lk_indexof(lPtr, value) >= 0;
}

unsigned int lk_indexof(const LinkedList* lPtr, const lk_BYTE value[]) {
	if (lPtr == NULL) {
		return false;
	}
	for (unsigned int index = 0; index < lPtr->lenght; index++) {
		lk_BYTE* valuePtr = (lk_BYTE*) lk_get(lPtr, index);
		for (unsigned int i = 0; i < lPtr->bytes; i++) {
			if (valuePtr[i] != (&(lk_BYTE) value)[i]) {
				break;
			}
			if (i == lPtr->bytes - 1) {
				return index;
			}
		}
	}
	return -1;
}
