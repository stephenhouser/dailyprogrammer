#include <stdio.h>
#include <string.h>

#define MIN_NUMBER	1
#define MAX_NUMBER	100

char *read_line (char *buf, size_t length, FILE *f)
  /**** Read at most 'length'-1 characters from the file 'f' into
        'buf' and zero-terminate this character sequence. If the
        line contains more characters, discard the rest.
   */
{
  char *p;

  if (p = fgets (buf, length, f)) {
    size_t last = strlen (buf) - 1;

    if (buf[last] == '\n') {
      /**** Discard the trailing newline */
      buf[last] = '\0';
    } else {
      /**** There's no newline in the buffer, therefore there must be
            more characters on that line: discard them!
       */
      fscanf (f, "%*[^\n]");
      /**** And also discard the newline... */
      (void) fgetc (f);
    } /* end if */
  } /* end if */
  return p;
} /* end read_line */

int yes_no(char *prompt) {
	char answer[10];

	while (1==1) {
		printf("%s", prompt);
		read_line(answer, 10, stdin);

		switch (answer[0]) {
			case 'Y':
			case 'y':
				return 1;
			case 'N':
			case 'n':
				return 0;
			default:
				printf("invalid [%s]\n", answer);
				break;
		}
	}
}

int high_low_equal(char *prompt) {
	char answer[10];

	while (1==1) {
		printf("%s", prompt);
		read_line(answer, 10, stdin);

		switch (answer[0]) {
			case 'H':
			case 'h':
				return 1;
			case 'E':
			case 'e':
				return 0;
			case 'L':
			case 'l':
				return -1;
			default:
				printf("invalid [%s]\n", answer);
				break;
		}
	}
}


int main(int argc, char *argv[]) {
	int min = MIN_NUMBER;
	int max = MAX_NUMBER;
	int guess;
	char prompt[255];
	int found = 0;

	printf("Think of a number between %d and %d.\n", min, max);
	max++;
	while (!found) {
		guess = (max + min) / 2;
		sprintf(prompt, "Is it (h)igher than, (l)ower than, or (e)qual to %d (h/l/e)? ", guess);
		switch (high_low_equal(prompt)) {
			case -1:
				max = guess;
				break;	
			case 0:
				printf("Wonderful! %d is a great number!\n", guess);
				found = 1;
				break;
			case 1:
				min = guess;
				break;
		}
	}
	
	return 0;
}
