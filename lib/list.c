#include <stdlib.h>
#include <stdbool.h>

#include "list.h"

/****** LIST ******/

/* The list contains only pointers to the elements, not the elements themselves */

struct list_node_s {
	ListNode *next;
	ListNode *prev;
	void *contents;
};

struct list_s {
	int size;
	ListNode *head;
	ListNode *tail;
};

bool list_is_valid(List *list) {
	if (list != NULL) {
		return true;
	}

	return false;
}

List *list_create() {
	List *list = malloc(sizeof(List));
	return list;
}

bool list_init(List *list) {
	if (!list_is_valid(list)) {
		return false;
	}

	list->size = 0;
	list->head = NULL;
	list->tail = NULL;
	return true;
}

void list_destroy(List *list) {
	if (!list_is_valid(list)) {
		return;
	}

	ListNode *current = list->head;
	while (current != NULL) {
		ListNode *next = current->next;
		free(current);
		current = next;
	}
}

bool list_empty(List *list) {
	if (!list_is_valid(list)) {
		return false;
	}

	return list_size(list) == 0;
}

size_t list_size(List *list) {
	if (!list_is_valid(list)) {
		return 0;
	}

	return list->size;
}

bool list_add(List *list, void *element) {
	if (!list_is_valid(list)) {
		return false;
	}

	return true;
}

bool list_remove(List *list, void *element) {
	if (!list_is_valid(list)) {
		return false;
	}

	return true;
}

void list_map(List *list, void (*map_function)(void *)) {
	if (!list_is_valid(list)) {
		return;
	}

	ListNode *current = list->head;
	while (current != NULL) {
		map_function(current);
		current = current->next;
	}
}

void list_reduce(List *list, void (*reduce_function)(void *, void *, void *), void *result) {
	if (!list_is_valid(list)) {
		return;
	}

	if (list->size <= 0) {
		return;
	}

	if (list->size == 1) {
		return;
	}

	// first item
	ListNode *current = list->head;
	reduce_function(current, NULL, result);

	// all subsequent items	
	while ((current = current->next) != NULL) {
		reduce_function(result, current->contents, result);
	}
}


