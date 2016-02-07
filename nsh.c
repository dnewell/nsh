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
static const char * commandHistory[HISTORY_MAX];         // array to hold previously issues commands
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
void addToHistory(const char * lineToAdd)
{
    printf("added to history: %s", lineToAdd);

    commandHistory[currentHistorySize]	= lineToAdd;

    int8_t i;

    for (i = 0; i < currentHistorySize; i++)
    {
        printf("%s\n", commandHistory[i]);
    }

    currentHistorySize++;
}

/*
 * This function displays the last 10 commands entered.
 * TODO: Implement a history data structure using a circular buffer/queue
 */
void displayHistory()
{
    // int value;
    if (currentHistorySize == 0)
    {
        return;    // no commands have been entered.
    }
    else
    {
        int8_t i;

        // print 1 - 10 commands
        if (currentHistorySize < 10)
        {
            for (i = 0; i < currentHistorySize; i++)
            {
                printf("%s\n", commandHistory[i]);
            }
        }

        // else
        // {
        // int temp        = currentHistorySize;
        //
        // for (h = (temp - 10); h < 10; h++)
        // {
        // printf("%s\n", commandHistory[h]);
        // }
        // }
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

        int_fast16_t n;

        if (*fgets(input_line, MAX, stdin) != '\n')           // error handling
        {
            n	= makeTokenList(input_line, tokenArray);    // tokenArray contains all arguments from user's input line

            if (strcmp(input_line, "exit\n") == 0)            // check for built-in termination command 'exit'
            {
                return 0;
            }
            else if (strcmp(input_line, "history\n") == 0)    // check for built-in termination command 'history'
            {
                displayHistory();
            }
            else
            {
                addToHistory(input_line);

                // TODO run commands
                int_fast16_t i;

                for (i = 0; i < n; i++)
                {
                    printf("will run command %s\n", tokenArray[i]);
                    printf("line: %s", input_line);
                }
            }
        }
    }

    return 0;
}

int main()
{
	int command = 0;
	while (command != 3)
	    {
	        printf("Enter your choice:\n1) Push integer\n2) Pop Integer\n3) Quit.\n");
	        scanf("%d",&command);
	        if (command == 1)
	        {
	            // push
	            int num;
	            scanf("%d",&num);
	            push(num);
	        }
	        else
	        {
	            if (command == 2)
	            {
	                pop();
	            }
	            else
	            {
	                if (command != 3)
	                {
	                    printf("Command not understood.\n");
	                }
	            }
	        }
	    }
    commandLoop();

    return 0;
}
