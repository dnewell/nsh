/**
 * nsh (NerudaShell) is a simple POSIX-compatible shell written by David Newell.
 *
 * It is dedicated to a fish trapped inside the wind.
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MAX 256                     // maximum input line length
#define CMD_MAX 10                  // maximum commands per line

/*
 *      This helper function reads/gets an input line from stdin.
 */
char* get_line(void){
    // TODO everything
}


/**
 *      makeTokenList takes an input string, and inserts each of the space delimited tokens it contains
 *      into an array.
 *
 *      The function takes as its input the following:
 *          inputBuffer: representation of the the string for which the tokens are to be determined for
 *          tokenArray: representation of the array that the found tokens are tbe put into
 *
 *      strtok() is used to extract the tokens, which are delimited by a space
*/
int_fast16_t makeTokenList(char *inputBuffer, char *tokenArray[])
{

    char *line;
    int_fast16_t argCount = 0;

    line = inputBuffer;
    tokenArray[argCount] = strtok(line, " ");

    do  {
        argCount ++;
        line = NULL;
        tokenArray[argCount] = strtok(line, " ");
    } while(tokenArray[argCount] != NULL);

    return argCount;
}

int main() {
    const char* PROMPT = "n#";
    const char* EXIT_TOKEN = "exit";
    char* line;
    pid_t pid;

    //start h code

    char input_line[MAX], *tokenArray[CMD_MAX];
    int_fast16_t i, n;

    while(1) {
        printf(PROMPT);
        if (fgets(input_line, MAX, stdin) != NULL)
            n = makeTokenList(input_line, tokenArray);
        else
            printf("error: no input\n");

        //printf("return is : %i", n);
        for (i = 0; i < n; i++)
            printf("extracted token is %s\n", tokenArray[i]);
        // end h code

        // TODO: exit loop on "exit" token
//        printf("n = %i, tokenArray = %s, exitToken = %s\n", n, tokenArray[0], EXIT_TOKEN);
        if (n == 1) {
            printf("%i", strcmp(tokenArray[0], EXIT_TOKEN));
            break;
        }
    }
    return 0;
}

