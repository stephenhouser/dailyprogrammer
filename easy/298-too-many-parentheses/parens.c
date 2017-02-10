#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <strings.h>

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

// works
int remove_parens1(char *line) {
    char prev = '\0';
    int count = 0;
    char buffer[strlen(line) + 1];

    strcpy(buffer, line);
    for (int i = 0; i < strlen(line); i++) {
        if (line[i] == '(') {
            int match = find_match(&line[i]) - &line[0];
            if ((prev == '(' && line[match + 1] == ')') || (i + 1 == match)) {
                buffer[i] = buffer[match] = ' '; // replace with space
                count++;
            }
        }

        prev = line[i];
    }

    strip(buffer);

    // bonus hack
    if (strlen(buffer) == 0 || !strcmp(buffer, "()")) {
        strcpy(buffer, "NULL");
    }

    strcpy(line, buffer);
    return count;
}

int remove_parens2(char *line) {
    char prev = 0;
    int count = 0;
    char *match;
    char *buffer = malloc(strlen(line) + 1);

    strcpy(buffer, line);
    for (char *p = buffer; p < buffer + strlen(buffer); p++) {
        switch (*p) {
            case ' ':   // ignore spaces -- we put these here
                //*line++ = *p;
                break;

            case '(':   // 
                match = find_match(p);
                if ((prev == '(' && *(match + 1) == ')') || ((p + 1) == match)) {
                    *p = *match = ' ';   // replace with space so we won't copy it
                    count++;
                    break;          // don't copy this open paren
                }
                // fall through and copy this open paren to cleaned string

            default:    // copy to cleaned string
                *line++ = *p;
                break;
        }

        prev = *p;
    }    

    *line = '\0';
    free(buffer);
    return count;
}

int remove_parens3(char *line) {
    char prev = 0;
    int count = 0;
    char *match;
    char buffer[strlen(line) + 1];

    strcpy(buffer, line);
    for (char *p = line; p < line + strlen(line); p++) {
        switch (*p) {
            case ' ':   // ignore spaces -- we put these here
                //*line++ = *p;
                break;

            case '(':   // 
                match = find_match(p);
                if ((prev == '(' && *(match + 1) == ')') || ((p + 1) == match)) {
                    *p = *match = ' ';   // replace with space so we won't copy it
                    count++;
                    break;          // don't copy this open paren
                }
                // fall through and copy this open paren to cleaned string

            default:    // copy to cleaned string
                //*line++ = *p;
                break;
        }

        prev = *p;
    }    

    return count;
}

int main(int argc, char *argv[]) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, stdin)) != -1) {
        chomp(line);
        char buffer[strlen(line) + 1];

        //printf("<:%s\n", line);

        strcpy(buffer, line);
        remove_parens1(buffer);
        printf("%s\n", buffer);
        //printf("1:%s\n", buffer);

        /*
        strcpy(buffer, line);
        remove_parens2(buffer);
        printf("2:%s\n", buffer);

        strcpy(buffer, line);
        remove_parens3(buffer);
        printf("3:%s\n", buffer);

        printf("\n");
        */
	}

    free(line);
}
