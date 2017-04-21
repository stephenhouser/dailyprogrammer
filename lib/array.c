
#include <stdio.h>
#include <stdlib.h>

#include "array.h"

/****** ARRAY ******/

/* The array contains only pointers to the elements, not the elements themselves */

array_t *array_create() {
    return NULL;
}

void array_init(array_t *array, int size) {
	void *array_contents = malloc(sizeof(void *) * size);
	if (array_contents != NULL) {
		array->contents = array_contents;
		array->size = size;
	} else {
		fprintf(stderr, "Cannot allocate %d contents for queue %p\n", size, array);
		exit(1);
	}
}

void array_destroy(array_t *array) {

	free(array->contents);
	array->contents = NULL;
	array->size = 0;
}

int array_set(array_t *array, int index, void *element) {
	if (index < array->size) {
		array->contents[index] = element;
		return index;
	} else {
		// expand the array?
		return -1;
	}
}

void *array_get(array_t *array, int index) {
	if (index < array->size) {
		return array->contents[index];
	}

	return NULL;
}

int array_size(array_t *array) {
	return array->size;
}

void array_dump(array_t *array, void (*dump_func)(void *)) {
	for (int i = 0; i <= array->size; i++) {
		dump_func(array->contents[i]);
	}
}
