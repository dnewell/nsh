/**
 *  shell is a simple POSIX-compatible shell written by David Newell.
 *
 * 	Author: David Newell
 * 	SN: 250332100
 * 	For: Professor Hanan Lutfiyya
 */

/* INCLUDES */
#include "unifiedHeader.h"
#include "shell.h"
#include "stack.h"
#include "pipes.h"

/* GLOBALS */
int8_t currentHistorySize = 0;          // number of commands issued this session
const char *PROMPT = "dnewell>";        // string to display for prompt
char pipeCommands[3][MAX];              // holds the commands from between pipes
char input_line[MAX];                   // holds current line of input from user


/*
 * The addToHistory function takes a string as input, and adds it to the commandHistory.
 */
void addToHistory(char *lineToAdd) {
    push(lineToAdd);
    currentHistorySize++;
}

/*
 * The displayHistory function displays the last 10 commands entered.
 */
void displayHistory() {
    int linesToPrint;

    if (currentHistorySize <= 0)
    {                      // no commands yet entered
        return;
    }
    else {
        (currentHistorySize < 10) ?
        (linesToPrint = currentHistorySize) : (linesToPrint = 10);

        int16_t i;

        for (i = 0; i < linesToPrint; i++)
        {                                               // print last n commands, up to a max of 10
            printf("%s", pop());
        }
        resetStack();                                   // return top of stack pointer to most recently pushed item
        printf("\n");
    }
}
/*
 * The initialize function clears the global array which holds the commands parsed from the input line
 */
void initialize(void)
{
    memset(input_line, '\0', MAX);
    int i;
    for (i = 0; i < 3; i++)
    {
        memset(pipeCommands[0], '\0', MAX);
    }
}

/*
 * Main shell loop.
 * Runs until user terminates their session, either by the 'exit' built-in,
 * or by sending the signal ctrl-c
 */
int commandLoop() {



    while (1) {
        initialize();
        int numberIoIn = 0;
        int numberIoOut = 0;
        int numberPipes = 0;
        int i;

        printf("%s", PROMPT);

        if (*fgets(input_line, MAX, stdin) != '\n')     // if input is \n, the user hit enter without entering a command
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

            if (numberPipes > 2) {
                printf("Currently, this shell only supports 0, 1, or 2 pipes.");
                continue;
            }

            if (numberIoIn > 0) {
                printf("Unfortunately, time constraints prevented me from implementing this.");
                continue;
            }

            if (numberIoOut > 1) {
                printf("Only one '>' permitted. ");
                continue;
            }

            if (((numberIoIn + numberIoOut) > 0) && (numberPipes > 0)) {
                printf("This shell does not support I/O redirection and pipes in the same command.");
                continue;                                               // jump to next iteration
            }

            if (strcmp(input_line, "exit\n") == 0)                      // check for built-in command 'exit'
            {
                exit(0);                                                // user requests exit
            }
            else if (strcmp(input_line, "history\n") == 0)              // check for built-in command 'history'
            {
                displayHistory();
                addToHistory(input_line);
            }
            else {
                addToHistory(input_line);
                // splits input using the pipes as the delimiter
                char *currentChar = strtok(input_line, "|");
                // populate pipeCommands array with the strings between the pipes, including any arguments.
                for (i = 0; i <= numberPipes; i++)
                {
                    strcpy(pipeCommands[i], currentChar);

                    currentChar = strtok(NULL, "|");
                }

                piper(numberPipes);                        // execution path depends on how many pipes are in the input
            }
        }
    }
}


int main() {

    int status = commandLoop();

    return status;
}