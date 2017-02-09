#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "read_line.h"


((a((:wq
vi subc)(de)))f)
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






typedef enum {
	ATOM,
	LIST,
	UNKNOWN
} Node_Type;

typedef struct {
	node_type type;	
	char *char_value;
	unsigned int children_count;
	node *children[];
} Node;

Node *make_node(Node_type type) {
	Node *node = malloc(sizeof(Node));
	if (node) {
		node->type = type;
		node->char_value = '\0';
		node->children_count = 0;
		node->children = NULL;
	}

	return Node;
}

void parse(Node *root, char *start, char *end) {
	char *p = start;
	Node *node;

	for (p = start; p < end; p++) {
		switch (*p) {
			case '(':
				Node *node = make_node(LIST);
				break;
			case ')':
				node_add_child(root, node);
				return node;
			default:
				Node *node = make_node(ATOM);
				node->char_value = *p;
				return node;
		}
	}
}

char *find_open(char *start, char *end) {
	char *expr = start;

	for (; expr < end; expr++) {
		if (*expr == '(') {
			break;
		}
	}

	return expr;
}

char *find_close(char *start, char *end) {
	char *expr = start;
	int level = 1;

	for (; expr < end; expr++) {
		if (*expr == '(') {
			level++;
		} else if (*expr == ')') {
	 		level--;	
			if (level == 0) {
				break;
			}
		}
	}

	return expr;
}

void balance_parens(char *start, char *end) {
	char *p_open;
	char *p_close;
	char *p;

	/* starting case, end == NULL */
	if (end == NULL) {
		end = start + strlen(start);
	}

	/* Bottom of descent */
	if (start >= end) {
		return;
	}

	//printf("start=%c, end=%c\n", *start, *end);
	//printf("start=%p, end=%p\n", start, end);

	/* print anything before an opening paren */
	p_open = find_open(start, end);

	for (p = start; p < p_open; p++) {
		printf("%c", *p);
	}

	/* If we reached the end, there are no parens at this level */
	if (p_open == end) {
		return;
	}

	/* find matching closing paren */
	p_close = find_close(p_open + 1, end);
	
	//printf("open=%c, close=%c\n", *p_open, *p_close);
	balance_parens(p_open + 1, p_close);

	if (p_close < end) {
		balance_parens(p_close + 1, end);
	}
	/* print anything after closing paren */
	/*for (p = p_close + 1; p < end; p++) {
		printf("%c", *p);
	}
	*/
}

int main(int argc, char *argv[]) {
	char line[256];
	while (read_line(line, 255, stdin)) {
		balance_parens(line, NULL);	
		printf("\n");
	}
}
