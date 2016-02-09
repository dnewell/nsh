/*
 *      Author: David Newell
 *      SN: 250332100
 *      For: Professor Hanan Lutfiyya
 */

/*
 * Includes
 */

#include "unifiedHeader.h"
#include "stack.c"

#define HISTORY_MAX 10
//static const char * commandHistory[HISTORY_MAX];         // array to hold previously issues commands
int8_t              currentHistorySize	= 0;             // number of commands issued this session
const char *        PROMPT		= "dnewell>";    // string to display for prompt

/*
 *      This helper function gets a line of user input from stdin.
 */
char * get_line(void)
{
    return "asd";
}

/*
 *      This function takes as input a string, and adds it to the commandHistory.
 *      TODO: Implement a history data structure using a circular buffer/queue
 */
void addToHistory(char * lineToAdd)
{
	push(lineToAdd);
    currentHistorySize++;
    printf("++ his: %s", lineToAdd);


}

/*
 * This function displays the last 10 commands entered.
 * TODO: Implement a history data structure using a circular buffer/queue
 */
void displayHistory()
{
    int linesToPrint;
    if (currentHistorySize <= 0)
    {
        return;    // no commands have been entered.
    }
    else
    {
    	(currentHistorySize < 10) ? (linesToPrint = currentHistorySize) : (linesToPrint = 10);

    	int16_t i;
		for (i = 0; i < linesToPrint; i++)
		{
			printf("%s", pop());
		}
		printf("/n");
    }
}

int_fast16_t makeTokenList(char * inputBuffer,
                           char * tokenArray[])
{
    char *       line;
    int_fast16_t argCount	= 0;

    line					= inputBuffer;
    tokenArray[argCount]	= strtok(line, " ");

    do
    {
        argCount++;

        line					= NULL;
        tokenArray[argCount]	= strtok(line, " ");
    }
    while (tokenArray[argCount] != NULL);

    return argCount;
}

int commandLoop()
{
    char input_line[MAX], *tokenArray[CMD_MAX];

    while (1)
    {
        printf("%s", PROMPT);

        if (*fgets(input_line, MAX, stdin) != '\n')           						// if input is \n, the user hit enter without entering a command
        {
        	int_fast16_t numberToks = makeTokenList(input_line, tokenArray);    	// tokenArray contains all arguments from user's input line

            if (strcmp(input_line, "exit\n") == 0)            						// check for built-in command 'exit'
            {
                return 0;															// user requests exit
            }
            else if (strcmp(input_line, "history\n") == 0)    						// check for built-in command 'history'
            {
                displayHistory();
            }
            else
            {
                addToHistory(input_line);

                // TODO run commands
                int_fast16_t i;

                for (i = 0; i < numberToks; i++)
                {
                    //printf("will run command %s\n", tokenArray[i]);
                    //printf("line: %s", input_line);
                }
            }
        }
    }
  //  return 0;
}

int main()
{
	int8_t status = commandLoop();

    return status;
}
