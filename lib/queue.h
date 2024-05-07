
/****** QUEUE ******/

/* The queue contains only pointers to the elements, not the elements themselves */

typedef struct {
	int front;
	int count;
	int max_elements;
	void **contents;
} Queue;

extern void queue_init(Queue *queue, int max_elements);
extern void queue_destroy(Queue *queue);
extern int queue_empty(Queue *queue);
extern int queue_full(Queue *queue);
extern void queue_enter(Queue *queue, void *element);
extern void *queue_delete(Queue *queue);
