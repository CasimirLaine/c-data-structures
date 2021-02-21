#include <stdio.h>
#include <stdlib.h>
#include "list.h"

static const unsigned int DEFAULT_CAPACITY = 10;
static const float GROWTH_FACTOR = 1.5;

void nullPointerExit() {
	printf("Null pointer exception\n");
	exit(1);
}

void indexOutOfBoundsExit() {
	printf("Index out of bounds\n");
	exit(1);
}

void* reallocate_list_data(List* lPtr, unsigned int sizeBytes) {
	void* newDataPtr = realloc(lPtr->data, sizeBytes);
	if (newDataPtr == NULL && sizeBytes > 0) {
		nullPointerExit();
		return NULL;
	}
	lPtr->allocatedBytes = sizeBytes;
	lPtr->data = newDataPtr;
	return newDataPtr;
}

List* l_create(unsigned int bytes) {
	List* lPtr = (List*) malloc(sizeof(List));
	if (lPtr != NULL) {
		lPtr->bytes = bytes;
		lPtr->lenght = 0;
		lPtr->allocatedBytes = DEFAULT_CAPACITY * bytes;
		lPtr->data = malloc(lPtr->allocatedBytes);
	}
	return lPtr;
}

void* l_get(List* lPtr, unsigned int index) {
	if (lPtr == NULL) {
		nullPointerExit();
		return NULL;
	}
	if (index >= lPtr->lenght) {
		indexOutOfBoundsExit();
		return NULL;
	}
	l_BYTE* bytePtr = (l_BYTE*) lPtr->data;
	return &bytePtr[index * lPtr->bytes];
}

void l_set(List* lPtr, l_BYTE value[], unsigned int index) {
	l_BYTE* dataPtr = (l_BYTE*) lPtr->data;
	for (unsigned int i = 0; i < lPtr->bytes; i++) {
		l_BYTE* indexPtr = &dataPtr[index * lPtr->bytes + i];
		*indexPtr = (&(l_BYTE) value)[i];
	}
}

void l_add(List* lPtr, l_BYTE value[]) {
	if (lPtr == NULL) {
		nullPointerExit();
		return;
	}
	const unsigned int bytesNeeded = lPtr->lenght * lPtr->bytes + lPtr->bytes;
	if (bytesNeeded > lPtr->allocatedBytes) {
		reallocate_list_data(lPtr, lPtr->allocatedBytes * GROWTH_FACTOR);
	}
	l_set(lPtr, value, lPtr->lenght);
	lPtr->lenght++;
}

void l_remove(List* lPtr, unsigned int index) {
	if (lPtr == NULL) {
		nullPointerExit();
		return;
	}
	if (index >= lPtr->lenght) {
		indexOutOfBoundsExit();
		return;
	}
	if (lPtr->lenght > 1) {
		for (; index < lPtr->lenght - 1; index++) {
			l_set(lPtr, *(int*) l_get(lPtr, index + 1), index);
		}
	}
	lPtr->lenght--;
}

void l_clear(List* lPtr) {
	if (lPtr == NULL) {
		nullPointerExit();
		return;
	}
	lPtr->lenght = 0;
	reallocate_list_data(lPtr, lPtr->bytes);
}

unsigned int l_size(List* lPtr) {
	if (lPtr == NULL) {
		nullPointerExit();
		return 0;
	}
	return lPtr->lenght;
}

bool l_empty(List* lPtr) {
	if (lPtr == NULL) {
		nullPointerExit();
		return 0;
	}
	return lPtr->lenght == 0;
}

bool l_contains(List* lPtr, l_BYTE value[]) {
	return l_indexof(lPtr, value) >= 0;
}

unsigned int l_indexof(List* lPtr, l_BYTE value[]) {
	for (unsigned int index = 0; index < lPtr->lenght; index++) {
		l_BYTE* valuePtr = (l_BYTE*) l_get(lPtr, index);
		for (unsigned int i = 0; i < lPtr->bytes; i++) {
			if (valuePtr[i] != (&(l_BYTE) value)[i]) {
				break;
			}
			if (i == lPtr->bytes - 1) {
				return index;
			}
		}
	}
	return -1;
}
