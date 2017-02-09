#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "read_line.h"

#include "stack.h"
#include "queue.h"


/*
((a((bc)(de)))f)
12x34xx44xx432x1
12x34xx45xx532x1
( (a((bc)(de)))f ) 
  

                ( )
	( )               f
   a         ()
          ()   ()
         b  c d  e


(((zbcd)(((e)fg))))
123xxxx3345x5xx4321

123xxxx3456x6xx5421
 ((zbcd) ((e)fg))

ab((c))
xx12x21
ab (c)
*/

/* The grammar 
 * E -> L | A 
 * L -> "(" E ")"
 * A -> [a-z]
 */


typedef enum {
	UNKNOWN_NODE = 0,
	CHAR_NODE,
	INT_NODE,
	FLOAT_NODE,
	LIST_NODE
} NodeType;

typedef

typedef struct node_t {
	NodeType type;
	union {
		void *p;
		char c;
		int i;
		float f;
	} value;

	Node *parent;
	unsigned int children_count;
	unsigned int max_children;
	struct node_t *children[];
} Node;

Node *node_create_list(int max_children) {
	Node *node = malloc(sizeof(Node) + sizeof(Node *) * max_children);
	if (node == NULL) {
		fprintf(stderr, "Could not allocate memory for list node with %d children\n", max_children);
		exit(1);
	}

	node->parent = NULL;
	node->max_children = max_children;
	node->children_count = 0;
	node->type = LIST_NODE;
	return node;
}

Node *node_create(char char_value) {
	Node *node = malloc(sizeof(Node));
	if (node == NULL) {
		fprintf(stderr, "Could not allocate memory for character node [%c].\n", char_value);
		exit(1);
	}

	node->parent = NULL;
	node->max_children = 0;
	node->children_count = 0;
	node->type = CHAR_NODE;
	node->value.c = char_value;
	return node;
}

void node_destroy(Node *node) {
	if (node->type == LIST_NODE) {
		free(node->children);
		node->max_children = 0;
		node->children_count = 0;	
	}

	node->parent = NULL;
	node->type = UNKNOWN_NODE;
}

void node_add_child(Node *node, Node *child) {
	if (node->type != LIST_NODE) {
		fprintf(stderr, "Cannot add child %p to non-list node %p\n", child, node);
		exit(1);
	}

	if (node->children_count >= node->max_children) {
		fprintf(stderr, "Cannot add child %p to full list node %p\n", child, node);
		exit(1);		
	}

	node->children[node->children_count++] = child;
	child->parent = node;
}

void node_remove_child(Node *node, Node *child) {

}

int node_list_empty(Node *node) {
	if (node->type == LIST_NODE) {
		return node->children == 0;
	}

	return 0;	// non-list nodes are never empty
}

/*
current_node = root

if *p == '(':
	if current_node
		push current_node onto stack
	current note = new node
else if *p == ')'
	if stack empty error
	this_node = current_node
	current_node = pop from stack
	add this_node to current_node
else
	add node to current_node
*/
Node *parse_expression(char *expression) {
	char *end = expression + strlen(expression);
	Node *current = node_create_list(10);	// root is a list
	Node *child;

	Stack stack;
	stack_init(&stack, 100);

	for (char *p = expression; p < end; p++) {
		switch (*p) {
			case '(':
				if (current) {
					stack_push(&stack, current);
				}

				current = node_create_list(10);
				break;

			case ')':
				if (stack_empty(&stack)) {
					fprintf(stderr, "Invalid expression!\n");
					exit(1);
				}

				child = current;
				current = stack_pop(&stack);
				node_add_child(current, child);
				break;

			default:
				child = node_create(*p);
				node_add_child(current, child);
				break;
		}

		child = NULL;
	}

	return current;
}

void print_node(void *p_node) {
	Node *node = (Node *)p_node;
	switch (node->type) {
		case CHAR_NODE:
			printf("%c", node->value.c);
			break;

		case LIST_NODE:
			printf("(");
			for (int c = 0; c < node->children_count; c++) {
				print_node(node->children[c]);
			}
			printf(")");
			break;

		case UNKNOWN_NODE:
		default:
			printf("*");
			break;
	}
}

void print_tree(Node *root) {
	for (int c = 0; c < root->children_count; c++) {
		print_node(root->children[c]);
	}

	printf("\n");
}

void simplify_node(Node *node) {
	if (node->type == LIST_NODE) {
		
		while (node->children_count == 1 && node->children[0]->type == LIST_NODE) {
			// attach grandchildren to me, rather rudely I might add
			Node *only_child = node->children[0];
			node->children_count = only_child->children_count;
			for (int gc = 0; gc < only_child->children_count; gc++) {
				node->children[gc] = only_child->children[gc];
			}
		}
	}
}

void simplify_tree(Node *root) {
	for (int c = 0; c < root->children_count; c++) {
		simplify_node(root->children[c]);
	}
}

int main(int argc, char *argv[]) {
	char line[256];
	while (read_line(line, 255, stdin)) {
		Node *root = parse_expression(line);
		print_tree(root);

		simplify_tree(root);
		print_tree(root);
	}
}
