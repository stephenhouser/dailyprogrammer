#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <read_line.h>

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


/*

int main(int argc, char *argv[]) {
	char line[256];
	char buffer[256];

	while (read_line(line, 255, stdin)) {

        int match;
        char prev = '\0';

        strncpy(buffer, line, 256);
        for (int i = 0; i < strlen(buffer); i++) {
            switch (buffer[i]) {
                case '(':
                    match = find_match(&buffer[i]) - &buffer[0];
                    if ((prev == '(' && buffer[match + 1] == ')') || (i + 1 == match)) {
                        buffer[match] = ' ';
                        break;
                    }
                    // fall through

                default:
                    printf("%c", buffer[i]);
                    break;

                case ' ':
                    break;

            }

            prev = line[i];
        }

        printf("\n");
	}
}
*/
/*

void remove_parens(char *clean, char *src) {
    char prev = 0;
    char *match;
    char *buffer = malloc(strlen(src) + 1);

    strncpy(buffer, src, 256);
    for (char *p = buffer; p < buffer + strlen(buffer); p++) {
        switch (*p) {
            case ' ':   // ignore spaces -- we put these here
                *clean++ = *p;
                break;

            case '(':   // 
                match = find_match(p);
                if ((prev == '(' && *(match + 1) == ')') || ((p + 1) == match)) {
                    *p = *match = ' ';   // replace with space so we won't copy it
                    //break;          // don't copy this open paren
                }
                // fall through and copy this open paren to cleaned string

            default:    // copy to cleaned string
                *clean++ = *p;
                break;

        }

        prev = *p;
    }    
}


int main(int argc, char *argv[]) {
	char line[256];
	char buffer[256];

	while (read_line(line, 255, stdin)) {
        remove_parens(buffer, line);
        printf("%s\n", buffer);
	}
}
*/