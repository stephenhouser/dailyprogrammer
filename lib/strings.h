

/* Chomp off trailing control characters (e.g. newline) from string. */
extern int strip(char *string);

/* Strip spaces from string (in-place). */
extern int chomp(char *string);

/* Trim leading spaces in string */
int ltrim(char *string);
/* Trim trailing spaces in string */
int rtrim(char *string);
/* Trim leading and trailing spaces from string */
int trim(char *string);