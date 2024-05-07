/* Dailyprogrammer [easy] challenge #1
 * https://www.reddit.com/r/dailyprogrammer/comments/pih8x/easy_challenge_1/
 * 2017/02/02 Stephen Houser
 */

#include <stdio.h>

int main(int argc, char *argv[]) {
	char name[256];
	int age;
	char username[256];
	int count = 0;

	printf("Hello,\n");

	printf("What is your name? ");
	scanf("%[^'\n']s:255%*s", name);

	printf("How old are you? ");
	scanf("%d", &age);

	printf("And what is your reddit username? ");
	scanf("%s:255%*s", username);

	/* Print the output string... */
	printf("your name is %s, you are %d years old, and your username is %s\n",
		name, age, username);
	return 0;
}
