
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

/****** QUEUE ******/

/* The queue contains only pointers to the elements, not the elements themselves */

Queue *queue_create() {
    return NULL;
}

void queue_init(Queue *queue, int max_elements) {
	void *queue_contents = malloc(sizeof(void *) * max_elements);
	if (queue_contents != NULL) {
		queue->contents = queue_contents;
		queue->max_elements = max_elements;
		queue->front = 0;
		queue->count = 0;
	} else {
		fprintf(stderr, "Cannot allocate %d contents for queue %p\n", max_elements, queue);
		exit(1);
	}
}

void queue_destroy(Queue *queue) {
	free(queue->contents);
	queue->contents = NULL;
	queue->max_elements = 0;
	queue->front = 0;
	queue->count = 0;
}

int queue_empty(Queue *queue) {
	return queue->count <= 0;
}

int queue_full(Queue *queue) {
	return queue->count >= queue->max_elements;
}

void queue_enter(Queue *queue, void *element) {
	if (queue_full(queue)) {
		fprintf(stderr, "Enter element %p to full queue %p\n", element, queue);
		exit(1);
	}

	int queue_index = (queue->front + queue->count) % queue->max_elements;
	queue->contents[queue_index] = element;
	queue->count++;
}

void *queue_delete(Queue *queue) {
	if (queue_empty(queue)) {
		fprintf(stderr, "Delete from empty queue %p\n", queue);
		exit(1);
	}

	void *element = queue->contents[queue->front];

	queue->front = ++queue->front % queue->max_elements;
	queue->count--;
	return element;
}

void queue_dump(Queue *queue) {
	int q_count = queue->count;
	int q_index = queue->front;
	while (q_count--) {
		// print out void *
		q_index = (q_index + 1) % queue->max_elements;
	}
}
