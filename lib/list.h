/* 
 *
 */

/****** LIST ******/

#if !defined(LIST_H)
#define LIST_H

#include "common.h"

/* The list contains only pointers to the elements, not the elements themselves */

typedef struct list_s List;
typedef struct list_node_s ListNode;

extern bool list_init(List *list);
extern void list_destroy(List *list);

extern bool list_empty(List *list);
extern size_t list_size(List *list);

extern bool list_add(List *list, void *element);
extern bool list_remove(List *list, void *element);

extern void list_map(List *list, void (*map_function)(void *));
extern void list_reduce(List *list, void (*reduce_function)(void *, void *, void *), void *result);

#endif