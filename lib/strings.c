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

/* Trim leading spaces in string */
int ltrim(char *string) {
    char *s = string;
    char *d = string;
    int count = 0;

    /* don't copy anything if the first char is non-space */
    if (isspace(*s)) {
        /* advance s to first non-space */
        while(*s != '\0' && isspace(*s)) {
            s++;
            count++;
        }

        /* copy non-spaces to start of string */
        while(*s != '\0') {
            *d++ = *s++;
        }

        *d = *s; // '\0'
    }

    return count;    
}

/* Trim trailing spaces in string */
int rtrim(char *string) {
    char *s = string + strlen(string) - 1;
    int count = 0;

    while(isspace(*s)) {
        *s-- = '\0';
        count++;
    }

    return count;    
}

/* Trim leading and trailing spaces from string */
int trim(char *string) {
    int count = rtrim(string) + ltrim(string);
    return count;
}
