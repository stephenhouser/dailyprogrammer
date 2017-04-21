
/****** ARRAY ******/

/* The array contains only pointers to the elements, not the elements themselves */

typedef struct {
	void **contents;
	int size;
} array_t;

extern void array_init(array_t *array, int size);
extern void array_destroy(array_t *array);

extern int array_set(array_t *array, int index, void *element);
extern void *array_get(array_t *array, int index);

// number of elements in the array
extern int array_size(array_t *array);

// extern int array_is_empty(array *array);
// extern int array_is_full(array *array);
// extern void array_add(array *array, void *element);

extern void array_dump(array_t *array, void (*dump_func)(void *));
