/* 
 *
 */

/****** ARRAY ******/

#if !defined(ARRAY_H)
#define ARRAY_H

#include "common.h"

/* The array contains only pointers to the elements, not the elements themselves */
typedef struct array_s Array;

// Create an array structure
extern Array *array_create();

// Initialize the array to hold size elements
extern bool array_init(Array *array, size_t size);
// Reinitialize the array (keeping/removing old elements) to hold size elements
extern bool array_reinit(Array *array, size_t size);
// Delete the array (does not free the elements)
extern void array_destroy(Array *array);
// Delete the array and free all "owned" elements
//extern void array_destroy_deep(Array *array);

// number of elements in the array
extern int array_size(Array *array);
// Set an array element (does not free previous element)
extern bool array_set(Array *array, size_t index, void *element);
// Get an array element
extern void *array_get(Array *array, size_t index);

// Call map_function(element) for each element in array
extern void array_map(Array *array, void (*map_funcion)(void *));
// Call reduce_function(element1, element2, result) across all elements.
extern void array_reduce(Array *array, void (*reduce_function)(void *, void *, void *), void *result);
#endif