#include <stdio.h>
#include <stdlib.h>
#include "arlist.h"

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

void* reallocate_list_data(ArrayList* lPtr, const unsigned int sizeBytes) {
	void* newDataPtr = realloc(lPtr->data, sizeBytes);
	if (newDataPtr == NULL && sizeBytes > 0) {
		nullPointerExit();
		return NULL;
	}
	lPtr->allocatedBytes = sizeBytes;
	lPtr->data = newDataPtr;
	return newDataPtr;
}

ArrayList* ar_create(const unsigned int bytes) {
	ArrayList* lPtr = (ArrayList*) malloc(sizeof(ArrayList));
	if (lPtr != NULL) {
		lPtr->bytes = bytes;
		lPtr->lenght = 0;
		lPtr->allocatedBytes = DEFAULT_CAPACITY * bytes;
		lPtr->data = malloc(lPtr->allocatedBytes);
	}
	return lPtr;
}

void* ar_get(const ArrayList* lPtr, const unsigned int index) {
	if (lPtr == NULL) {
		nullPointerExit();
		return NULL;
	}
	if (index >= lPtr->lenght) {
		indexOutOfBoundsExit();
		return NULL;
	}
	ar_BYTE* bytePtr = (ar_BYTE*) lPtr->data;
	return &bytePtr[index * lPtr->bytes];
}

void ar_set(const ArrayList* lPtr, const ar_BYTE value[], const unsigned int index) {
	ar_BYTE* dataPtr = (ar_BYTE*) lPtr->data;
	for (unsigned int i = 0; i < lPtr->bytes; i++) {
		ar_BYTE* indexPtr = &dataPtr[index * lPtr->bytes + i];
		*indexPtr = (&(ar_BYTE) value)[i];
	}
}

void ar_add(ArrayList* lPtr, const ar_BYTE value[]) {
	if (lPtr == NULL) {
		nullPointerExit();
		return;
	}
	const unsigned int bytesNeeded = lPtr->lenght * lPtr->bytes + lPtr->bytes;
	if (bytesNeeded > lPtr->allocatedBytes) {
		reallocate_list_data(lPtr, lPtr->allocatedBytes * GROWTH_FACTOR);
	}
	ar_set(lPtr, value, lPtr->lenght);
	lPtr->lenght++;
}

void ar_remove(ArrayList* lPtr, unsigned int index) {
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
			ar_set(lPtr, *(int*) ar_get(lPtr, index + 1), index);
		}
	}
	lPtr->lenght--;
}

void ar_clear(ArrayList* lPtr) {
	if (lPtr == NULL) {
		nullPointerExit();
		return;
	}
	lPtr->lenght = 0;
	reallocate_list_data(lPtr, lPtr->bytes);
}

unsigned int ar_size(const ArrayList* lPtr) {
	if (lPtr == NULL) {
		nullPointerExit();
		return 0;
	}
	return lPtr->lenght;
}

bool ar_empty(const ArrayList* lPtr) {
	if (lPtr == NULL) {
		nullPointerExit();
		return true;
	}
	return lPtr->lenght == 0;
}

bool ar_contains(const ArrayList* lPtr, ar_BYTE value[]) {
	if (lPtr == NULL) {
		return false;
	}
	return ar_indexof(lPtr, value) >= 0;
}

unsigned int ar_indexof(const ArrayList* lPtr, ar_BYTE value[]) {
	if (lPtr == NULL) {
		return -1;
	}
	for (unsigned int index = 0; index < lPtr->lenght; index++) {
		ar_BYTE* valuePtr = (ar_BYTE*) ar_get(lPtr, index);
		for (unsigned int i = 0; i < lPtr->bytes; i++) {
			if (valuePtr[i] != (&(ar_BYTE) value)[i]) {
				break;
			}
			if (i == lPtr->bytes - 1) {
				return index;
			}
		}
	}
	return -1;
}
