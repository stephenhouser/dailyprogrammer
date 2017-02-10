#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Chomp off trailing control characters (e.g. newline) from string. */
int chomp(char *string) {
    int count = 0;
    char *p = string + strlen(string) - 1;
    while (p > string && iscntrl(*p)) {
        *p = '\0';
        p--;
        count++;
    }

    return count;
}

/* Strip spaces from string (in-place). */
int strip(char *string) {
    char *s = string;
    char *d = string;
    int count = 0;
    do {
        while(isspace(*s)) {
            s++;
            count++;
        }
    } while((*d++ = *s++) != '\0');

    return count;
}
