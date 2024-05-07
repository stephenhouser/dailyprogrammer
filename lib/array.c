#include <stdlib.h>
#include <stdbool.h>

#include "array.h"

/****** ARRAY ******/

struct array_s {
	size_t size;
	void **contents;
};

/* The array contains only pointers to the elements, not the elements themselves */

Array *array_create() {
	Array *array = malloc(sizeof(Array));
	array->size = 0;
	array->contents = NULL;
    return array;
}

bool array_init(Array *array, size_t size) {
	void *array_contents = malloc(sizeof(void *) * size);
	if (array_contents == NULL) {
		return false;
	}
	array->contents = array_contents;
	array->size = size;
	return true;
}

void array_destroy(Array *array) {
	if (array != NULL) {
		array->size = 0;
		if (array->contents != NULL) {
			free(array->contents);
			array->contents = NULL;
		}
	}
}

// TODO: check that zero sized array fails with index of 0
bool array_valid_index(Array *array, size_t index) {
	if (index < array->size) {
		return true;
	}
	return false;
}

bool array_is_valid(Array *array) {
	if (array == NULL) {
		return false;
	}

	if (array->contents == NULL) {
		return false;
	}

	return true;
}
 
bool array_set(Array *array, size_t index, void *element) {
	if (!array_is_valid(array) || !array_valid_index(array, index)) {
		return false;
	}

	array->contents[index] = element;
	return true;
}

void *array_get(Array *array, size_t index) {
	if (!array_is_valid(array) || !array_valid_index(array, index)) {
		return false;
	}

	return array->contents[index];
}

int array_size(Array *array) {
	if (!array_is_valid(array)) {
		return 0;
	}

	return array->size;
}

void array_map(Array *array, void (*map_function)(void *)) {
	if (!array_is_valid(array)) {
		return;
	}

	for (int i = 0; i <= array->size; i++) {
		map_function(array->contents[i]);
	}
}

void array_reduce(Array *array, void (*reduce_function)(void *, void *, void *), void *result) {
	if (!array_is_valid(array)) {
		return;
	}

	if (array->size <= 0) {
		return;
	}

	if (array->size == 1) {
		reduce_function(array->contents[1], NULL, result);
		return;
	}

	reduce_function(array->contents[0], array->contents[1], result);
	for (int i = 2; i <= array->size; i++) {
		reduce_function(result, array->contents[i], result);
	}
}
