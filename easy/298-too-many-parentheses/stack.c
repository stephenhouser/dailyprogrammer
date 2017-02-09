

#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

 /* The stack contains only pointers to the elements, not the elements themselves */

void stack_init(Stack *stack, int max_elements) {
	void *stack_contents = malloc(sizeof(void *) * max_elements);
	if (stack_contents == NULL) {
		fprintf(stderr, "Cannot allocate %d contents for stack %p\n", max_elements, stack);
		exit(1);
	}

	stack->contents = stack_contents;
	stack->max_elements = max_elements;
	stack->top = -1; /* empty */
}

void stack_destroy(Stack *stack) {
	free(stack->contents);
	stack->contents = NULL;
	stack->max_elements = 0;
	stack->top = -1;
}

int stack_empty(Stack *stack) {
	return stack->top < 0;
}

int stack_full(Stack *stack) {
	return stack->top >= stack->max_elements - 1;
}

void stack_push(Stack *stack, void *element) {
	if (stack_full(stack)) {		
		fprintf(stderr, "Push %p to full stack %p\n", element, stack);
		exit(1);
	}

	stack->top++;
	stack->contents[stack->top] = element;
}

void *stack_pop(Stack *stack) {
	if (stack_empty(stack)) {
		fprintf(stderr, "Pop from empty stack %p\n", stack);
		exit(1);
	}

	void *element = stack->contents[stack->top];
	stack->top--;
	return element;
}

void stack_dump(Stack *stack, void (*dump_func)(void *)) {
    if (!stack_empty(stack)) {
        for (int i = 0; i <= stack->top; i++) {
            dump_func(stack->contents[i]);
        }
    }    
}
