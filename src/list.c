#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef char BYTE;

static const unsigned int DEFAULT_CAPACITY = 10;

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
	BYTE* bytePtr = (BYTE*) lPtr->data;
	return &bytePtr[index * lPtr->bytes];
}

void set(List* lPtr, void* value, unsigned int index) {
	BYTE* bytePtr = (BYTE*) lPtr->data;
	BYTE* valueBytePtr = (BYTE*) value;
	for (unsigned int i = 0; i < lPtr->bytes; i++) {
		BYTE* indexPtr = &bytePtr[index * lPtr->bytes + i];
		*indexPtr = *(valueBytePtr + i);
	}
}

void l_add(List* lPtr, void* value) {
	if (lPtr == NULL) {
		nullPointerExit();
		return;
	}
	const unsigned int bytesNeeded = lPtr->lenght * lPtr->bytes + lPtr->bytes;
	if (bytesNeeded > lPtr->allocatedBytes) {
		reallocate_list_data(lPtr, bytesNeeded + DEFAULT_CAPACITY * lPtr->bytes);
	}
	set(lPtr, value, lPtr->lenght);
	lPtr->lenght += 1;
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
			set(lPtr, l_get(lPtr, index + 1), index);
		}
	}
	lPtr->lenght -= 1;
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
