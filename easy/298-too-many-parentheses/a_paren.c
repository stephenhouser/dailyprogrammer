#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "read_line.h"

/* start points to opening '(' */
char *find_match(char *start) {
    char *p;
    char *end = start + strlen(start);
    int depth = 1;
    for (p = start + 1; p < end; p++) {
        if (*p == '(') {
            depth++;
         } else if (*p == ')') {
            depth--;
            if (depth <= 0) {
                break;;
            }
        }
    }

    return p; /* not found */
}

int main(int argc, char *argv[]) {
	char line[256];
	while (read_line(line, 255, stdin)) {

        char buffer[256];
        char prev = '\0';

        strncpy(buffer, line, 256);
        for (int i = 0; i < strlen(line); i++) {
            if (line[i] == '(') {
                int match = find_match(&line[i]) - &line[0];
                if ((prev == '(' && line[match + 1] == ')') || (i + 1 == match)) {
                    buffer[i] = buffer[match] = ' '; // replace with space
                }
            }

            prev = line[i];
        }

        printf("%s\n", buffer);
	}
}
