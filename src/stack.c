#include <stdlib.h>
#include "stack.h"

Stack* st_create(const unsigned int bytes) {
	return ar_create(bytes);
}

void st_push(Stack* sPtr, const st_BYTE value[]) {
	ar_add(sPtr, value);
}

void* st_pop(Stack* sPtr) {
	if (sPtr == NULL || st_empty(sPtr)) {
		return NULL;
	}
	void* valuePtr = st_peek(sPtr);
	ar_remove(sPtr, sPtr->lenght - 1);
	return valuePtr;
}

void* st_peek(Stack* sPtr) {
	if (sPtr == NULL || st_empty(sPtr)) {
		return NULL;
	}
	void* valuePtr = ar_get(sPtr, sPtr->lenght - 1);
	return valuePtr;
}

bool st_empty(Stack* sPtr) {
	if (sPtr == NULL) {
		return true;
	}
	return sPtr->lenght == 0;
}
