

#undef stack_t

typedef struct {
	int top;
	int max_elements;
	void **contents;
} Stack;

extern void stack_init(Stack *stack, int max_elements);
extern void stack_destroy(Stack *stack);
extern int stack_empty(Stack *stack);
extern int stack_full(Stack *stack);
extern void stack_push(Stack *stack, void *element);
extern void *stack_pop(Stack *stack);

void stack_dump(Stack *stack, void (*dump_func)(void *));
