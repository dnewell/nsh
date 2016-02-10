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
#include "nsh.h"
#include "pipes.c"

#define HISTORY_MAX 10

// static const char * commandHistory[HISTORY_MAX];         // array to hold previously issues commands
int8_t currentHistorySize = 0;         // number of commands issued this session
const char * PROMPT = "dnewell>";    // string to display for prompt
char pipeCommands[4][MAX];

/*
 *      This helper function gets a line of user input from stdin.
 */
char * get_line()
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
	//printf("++ his: %s", lineToAdd);
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
		(currentHistorySize < 10) ?
				(linesToPrint = currentHistorySize) : (linesToPrint = 10);

		int16_t i;

		for (i = 0; i < linesToPrint; i++)
		{
			printf("%s", pop());
		}

		printf("/n");
	}
}

int_fast16_t makeTokenList(char * inputBuffer, char * tokenArray[])
{
	char * line;
	int_fast16_t argCount = 0;

	line = inputBuffer;
	tokenArray[argCount] = strtok(line, " ");

	do
	{
		argCount++;

		line = NULL;
		tokenArray[argCount] = strtok(line, " ");
	} while (tokenArray[argCount] != NULL);

	return argCount;
}



/*
 * This function does the initial fork, from which all other
 * processes are forked.
 */
int8_t doMainFork(){

	int status = 0;			// status defaults to no error

		commandLoop();

	return status;
}



int commandLoop()
{
	char input_line[MAX];

	//*tokenArray[CMD_MAX];

	while (1)
	{
		memset(input_line, '\0', MAX);
		int numberIoIn = 0;
		int numberIoOut = 0;
		int numberPipes = 0;
		int i;							// loops counter

		printf("%s", PROMPT);

		if (*fgets(input_line, MAX, stdin) != '\n') // if input is \n, the user hit enter without entering a command
		{

			// count the number of pipes in the input
		    for (i = 0; i < MAX; i++)
		    {
		      if (input_line[i] == '|')
		      {
		    	  numberPipes++;
		      }
		    }

			// count the number of i/o in redirects in the input
		    for (i = 0; i < MAX; i++)
		    {
		      if (input_line[i] == '<')
		      {
		    	  numberIoIn++;
		      }
		    }

			// count the number of i/o out redirects in the input
		    for (i = 0; i < MAX; i++)
		    {
		      if (input_line[i] == '>')
		      {
		    	  numberIoOut++;
		      }
		    }

		    if (numberPipes > 2)
		    {
		    	printf("Currently, this shell only supports 0, 1, or 2 pipes.");
		    	continue;
		    }


		    if (numberIoIn > 0)
		    {
		    	printf("Unfortunately, time constraints prevented me from implementing this.");
		    }

		    if ( ( (numberIoIn + numberIoOut) > 0) && (numberPipes > 0) )
		    {
		    	printf("This shell does not support I/O redirection and pipes in the same command.");
		    	continue;											// jump to next iteration of while loop
		    }

			//int numberToks = makeTokenList(input_line, tokenArray); // tokenArray contains all arguments from user's input line

			if (strcmp(input_line, "exit\n") == 0) 					// check for built-in command 'exit'
			{
				return 0;                                  			// user requests exit
			}
			else if (strcmp(input_line, "history\n") == 0) 			// check for built-in command 'history'
			{
				displayHistory();
				addToHistory(input_line);
			}
			else
			{
				addToHistory(input_line);
				  int i;
				  char* current = strtok(input_line, "|");  // 'initialize' strtok to break input on "|" delimiters
				  // populate pipeCommands array with the strings between the pipes, including any arguments.
				  for (i = 0; i <= numberPipes; i++)
				  {
				    strcpy(pipeCommands[i],  current);
				    current = strtok(NULL, "|");
				  }

				// TODO run commands//	char *tmp3[CMD_MAX] = { NULL };

				    // Which scenario are we in? It is dependent on how many pipes are in the raw input.
				piper(numberPipes);
				//doCommand(tokenArray, numberToks);
//				int_fast16_t i;
//
//				for (i = 0; i < numberToks; i++)
//				{
//					printf("will run command %s\n", tokenArray[i]);
//					// printf("line: %s", input_line);
//				}
			}
		}
	}
	// return 0;
	// return 0;
}


int main()
{

	doMainFork();
	int8_t status = commandLoop();

	return status;
}

//~ Formatted by Jindent --- http://www.jindent.com
