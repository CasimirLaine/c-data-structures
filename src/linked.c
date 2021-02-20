#include <stdio.h>
#include <stdlib.h>
#include "linked.h"

LinkedList* lk_create(unsigned int bytes) {
	LinkedList* lPtr = (LinkedList*) malloc(sizeof(LinkedList));
	if (lPtr != NULL) {
		lPtr->bytes = bytes;
		lPtr->head = NULL;
	}
	return lPtr;
}

Node* allocateNode(unsigned int bytes) {
	Node* ptr = malloc(sizeof(Node));
	if (ptr != NULL) {
		ptr->value = malloc(bytes);
		ptr->next = NULL;
	}
	return ptr;
}

Node* findNode(Node* ptr, unsigned int index, unsigned int iter) {
	if (ptr == NULL) {
		return NULL;
	}
	if (index == iter) {
		return ptr;
	}
	return findNode(ptr->next, index, ++iter);
}

Node* findLastNode(Node* ptr) {
	if (ptr == NULL) {
		return NULL;
	}
	if (ptr->next != NULL) {
		return findLastNode(ptr->next);
	} else {
		return ptr;
	}
}

void assignToNode(Node* ptr, lk_BYTE value[], unsigned int bytes) {
	for (unsigned int i = 0; i < bytes; i++) {
		*((lk_BYTE*) ptr->value + i) = (&(lk_BYTE) value)[i];
	}
}

void* lk_get(LinkedList* lPtr, unsigned int index) {
	if (lPtr == NULL) {
		return NULL;
	}
	Node* node = NULL;
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

void lk_add(LinkedList* lPtr, lk_BYTE value[]) {
	if (lPtr == NULL) {
		return;
	}
	if (lPtr->head == NULL) {
		lPtr->head = allocateNode(lPtr->bytes);
		assignToNode(lPtr->head, value, lPtr->bytes);
	} else {
		Node* lastNode = findLastNode(lPtr->head);
		lastNode->next = allocateNode(lPtr->bytes);
		assignToNode(lastNode->next, value, lPtr->bytes);
	}
}
