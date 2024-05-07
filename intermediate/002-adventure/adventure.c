#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <strings.h>

#define TRUE (1==1)
#define FALSE !TRUE

#define MAX_ACTIONS 10
#define MAX_NODES	100

typedef enum _storyactiontype {
	ACTION_UNKNOWN = 0,
	ACTION_PRINT,
	ACTION_CALL,
	ACTION_OPTION
} StoryActionType;

typedef struct _storyaction {
	StoryActionType type;
	char *message;
	char key;
	char *node_name;
} StoryAction;

void storyaction_set_message(StoryAction *action, char *message) {
	action->message = malloc(strlen(message) + 1);
	if (!action->message) {
		fprintf(stderr, "Could not allocate memory for message [%s].\n", message);
		exit(1);
	}

	strcpy(action->message, message);
	trim(action->message);
}

void storyaction_set_call(StoryAction *action, char *node_name) {
	action->node_name = malloc(strlen(node_name) + 1);
	if (!action->node_name) {
		fprintf(stderr, "Could not allocate memory for call_node [%s].\n", node_name);
		exit(1);
	}

	strcpy(action->node_name, node_name);
	trim(action->node_name);	
}

void storyaction_init_print(StoryAction *action, char *story_line) {
	action->type = ACTION_PRINT;
	storyaction_set_message(action, story_line);
	//printf("\t\tadding message display [%s].\n", action->message);
}

void storyaction_init_call(StoryAction *action, char *story_line) {
	action->type = ACTION_CALL;
	storyaction_set_call(action, story_line);
	//printf("\t\tadding node call [%s].\n", action->call_node);
}

void storyaction_init_option(StoryAction *action, char *story_line) {
	char *saveptr;

	action->type = ACTION_OPTION;

	char *key = strtok_r(story_line, " -", &saveptr);
	if (!key || !isalnum(*key)) {
		fprintf(stderr, "Error parsing option key [%s] in story.\n", story_line);
		exit(1);
	}

	action->key = toupper(*key);

	char *message = strtok_r(NULL, "-", &saveptr);
	if (!message) {
		fprintf(stderr, "Error parsing option message [%s] in story.\n", story_line);
		exit(1);
	}
	
	storyaction_set_message(action, message);

	char *call_node = strtok_r(NULL, " -", &saveptr);
	if (!call_node) {
		fprintf(stderr, "Error parsing option node [%s] in story.\n", story_line);
		exit(1);
	}

	storyaction_set_call(action, call_node);
	//printf("\t\tadding menu option [%c], [%s], [%s].\n", action->option_char, action->message, action->call_node);
}

StoryAction *storyaction_create(char *story_line) {
	StoryAction *action = malloc(sizeof(StoryAction));
	if (action == NULL) {
		fprintf(stderr, "Could not allocate memory for story action.\n");
		exit(1);
	}

	action->message = NULL;
	action->key = '\0';
	action->node_name = NULL;

	switch (story_line[0]) {
		case '-':	// Option action
			// - [KEY] - [DESCRIPTION] - [FUNCTION NAME]
			storyaction_init_option(action, &story_line[1]);
			break;

		case '>': 	// print action
			// > Text to print...
			storyaction_init_print(action, &story_line[1]);
			break;

		case '=':	// call node action
			// = NODE_TO_CALL
			storyaction_init_call(action, &story_line[1]);
			break;
	}

	return action;
}

void storyaction_destroy(StoryAction *action) {
	action->type = ACTION_UNKNOWN;
	action->key = '\0';

	if (action->message) {
		free(action->message);
		action->message = NULL;
	}

	if (action->node_name) {
		free(action->node_name);
		action->node_name = NULL;
	}

	free(action);
}

typedef struct _storynode {
	char *name;
	int action_count;
	int max_actions;
	StoryAction *actions[];
} StoryNode;

StoryNode *storynode_create(char *node_line) {
	StoryNode *node = malloc(sizeof(StoryNode) + (sizeof(StoryAction) * MAX_ACTIONS));
	if (node == NULL) {
		fprintf(stderr, "Could not allocate memory for story node [%s].\n", node_line);
		exit(1);
	}

	node->max_actions = MAX_ACTIONS;
	node->action_count = 0;

	node->name = malloc(strlen(node_line) + 1);
	strcpy(node->name, node_line + 1);	// skip '@' at start
	trim(node->name);

	return node;
}

void storynode_add_action(StoryNode *node, StoryAction *action) {
	if (node->action_count >= node->max_actions) {
		fprintf(stderr, "Too many actions for node [%s].\n", node->name);
		exit(1);
	}

	node->actions[node->action_count++] = action;
}

void storynode_destroy(StoryNode *node) {
	for (int i = 0; i < node->action_count; i++) {
		storyaction_destroy(node->actions[i]);
	}

	free(node->name);
	node->name = NULL;
	node->action_count = 0;
	free(node);
}


/* The story as an array */
StoryNode *story[MAX_NODES];
int story_node_count = 0;

void story_init() {
	for (int i = 0; i < story_node_count; i++) {
		story[i] = NULL;
	}
}

void story_add_node(StoryNode *node) {
	if (story_node_count >= MAX_NODES) {
		fprintf(stderr, "Too many story nodes when adding [%s].\n", node->name);
		exit(1);	
	}

	story[story_node_count++] = node;
}

StoryNode *story_find_node(char *node_name) {
	for (int i = 0; i < story_node_count; i++) {
		if (!strcmp(node_name, story[i]->name)) {
			return story[i];
		}
	}

	return NULL;
}

void story_destroy() {
	for (int i = 0; i < story_node_count; i++) {
		storynode_destroy(story[i]);
		story[i] = NULL;
	}

	story_node_count = 0;
}

int load_story(char *story_file) {
	char *line = NULL;
    size_t len = 0;
    ssize_t read;
	FILE *fp;

	StoryNode *sn = NULL;
	StoryAction *sa = NULL;

	//printf("Loading %s...\n", story_file);

	fp = fopen(story_file, "r");
	if (!fp) {
		fprintf(stderr, "Could not open story file [%s].\n", story_file);
		exit(1);
	}

    while ((read = getline(&line, &len, fp)) != -1) {
        chomp(line);
		trim(line);
		switch (*line) {
			case '@':	// Start a new node
				sn = storynode_create(line);
				//printf("\tadding node [%s].\n", sn->name);
				story_add_node(sn);
				break;
			
			case '>': 	// print action
			case '-':	// Option action
			case '=':	// call node action
				sa = storyaction_create(line);
				//printf("\t\tadding action [%s].\n", sn->name);
				if (sn) {
					storynode_add_action(sn, sa);
				}
				break;

			default:	// other/unknown/comment
				break;
		}
	}

	free(line);
	fclose(fp);
	printf("Story %s loaded, %d nodes.\n", story_file, story_node_count);
	return 0;
}

void show_node(StoryNode *node) {
	StoryNode *sn = NULL;

	for (int i = 0; i < node->action_count; i++) {
		StoryAction *action = node->actions[i];
		switch (action->type) {
			case ACTION_OPTION:
				printf("(%c): ", action->key);
				// fall-through

			case ACTION_PRINT:
				printf("%s\n", action->message);
				break;

			case ACTION_CALL:
				sn = story_find_node(action->node_name);
				if (sn) {
					// run the called node recursively
					show_node(sn);
				}
				break;

			default:
				break;
		}
	}
}

char get_action(StoryNode *node) {
	char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, stdin)) != -1) {
        chomp(line);
		trim(line);
		if (isalnum(*line)) {
			char option = *line;

			free(line);
			return toupper(option);
		}
	}

	return '\0';
}

StoryNode *take_action(char action_key, StoryNode *node) {
	//printf("Take Action [%c].\n", action_key);

	for (int i = 0; i < node->action_count; i++) {
		StoryAction *action = node->actions[i];
		if (action->type == ACTION_OPTION && action->key == action_key) {
			printf("%s\n", action->message);
			StoryNode *action_node = story_find_node(action->node_name);
			return action_node;
		}

		if (action->type == ACTION_CALL) {
			StoryNode *action_node = story_find_node(action->node_name);
			StoryNode *call_node = take_action(action_key, action_node);
			if (call_node) {
				return call_node;
			}
		}
	}

	/* Invalid action, stay on the same node */
	return node;
}

void game_loop() {
	int player_action = 0;
	StoryNode *node = story[0];	// always start at the first node

	while (node) {
		show_node(node);
		player_action = get_action(node);
		printf("\n");
		node = take_action(player_action, node);
		printf("\n");
	}
}

int main(int argc, char *argv[]) {
	load_story("houser.story");
	game_loop();
}

