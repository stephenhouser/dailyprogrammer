#include <stdio.h>
#include <math.h>

/*
 * This function converts an unsigned binary
 * number to reflected binary Gray code.
 *
 * The operator >> is shift right. The operator ^ is exclusive or.
 */
unsigned int binaryToGray(unsigned int num) {
    return num ^ (num >> 1);
}

/*
 * This function converts a reflected binary
 * Gray code number to a binary number.
 * Each Gray code bit is exclusive-ored with all
 * more significant bits.
 */
unsigned int grayToBinary(unsigned int num) {
    unsigned int mask;
    for (mask = num >> 1; mask != 0; mask = mask >> 1) {
        num = num ^ mask;
    }
    return num;
}

int main(int argc, char **argv) {
	//unsigned int base = 2;	
	unsigned int digits = 4;
	unsigned int max_num = pow(digits, 2);	// max int in 'base'

	for (unsigned int i = 0; i < max_num; i++) {
		unsigned int g = binaryToGray(i);

		// print binary digits
		// from highest to least significant digit
		for (int j = digits - 1; j >= 0; j--) {
			char bit = ((g >> j) & 0x01) ? '1' : '0';
			printf("%c", bit);
		}

		printf("\n");
	}

	return 0;
}