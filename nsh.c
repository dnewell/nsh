/**
 *  nsh is a simple POSIX-compatible shell written by David Newell.
 *
 * 	Author: David Newell
 * 	SN: 250332100
 * 	For: Professor Hanan Lutfiyya
 */
#include "unifiedHeader.h"

/*
 *      This helper function reads/gets an input line from stdin.
 */
char* get_line(void) {

	return "asd";
}

/**
 *      makeTokenList takes an input string, and inserts each of the space delimited tokens it contains
 *      into an array.
 *
 *      The function takes as its input the following:
 *          inputBuffer: representation of  the string for which the tokens are to be determined for
 *          tokenArray: representation of the array that the found tokens are to put into
 *
 *      strtok() is used to extract the tokens, which are delimited by a space
 *
 *      This tokenizing code is used with permission from:
 *      http://www.csd.uwo.ca/courses/CS3305b/Assignments/token.c
 */
int_fast16_t makeTokenList(char *inputBuffer, char *tokenArray[]) {

	char *line;
	int_fast16_t argCount = 0;

	line = inputBuffer;
	tokenArray[argCount] = strtok(line, " ");

	do {
		argCount++;
		line = NULL;
		tokenArray[argCount] = strtok(line, " ");
	} while (tokenArray[argCount] != NULL);

	return argCount;
}

int main() {
	const char* PROMPT = "n#";
	const char* EXIT_TOKEN = "exit";

	//char* line;
	//pid_t pid;

	char input_line[MAX], *tokenArray[CMD_MAX];



	while (1) {
		printf("%s", PROMPT);

		int_fast16_t n;

		if (fgets(input_line, MAX, stdin) != NULL){
			n = makeTokenList(input_line, tokenArray);
		}
		else {

		}
			printf("error: no input\n");

		int_fast16_t i;
		for (i = 0; i < n; i++)
			printf("extracted token is %s\n", tokenArray[i]);


		// TODO: exit loop on "exit" token
//        printf("n = %i, tokenArray = %s, exitToken = %s\n", n, tokenArray[0], EXIT_TOKEN);
		if (n == 1) {
			printf("%i", strcmp(tokenArray[0], EXIT_TOKEN));
			break;
		}
	}
	return 0;
}

