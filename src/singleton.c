#include <stdlib.h>
#include "singleton.h"

static void* instance;

void sl_init(const unsigned int bytes) {
	instance = malloc(bytes);
}

void* sl_instance() {
	return instance;
}

void sl_destroy() {
	free(instance);
	instance = NULL;
}
