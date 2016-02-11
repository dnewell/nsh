#include "unifiedHeader.h"
#include "pipes.h"


void piper(int numberOfPipes) {
    if (numberOfPipes == 0) {
        noPipes();
    }
    else if (numberOfPipes == 1) {
        onePipe();
    }
    else if (numberOfPipes == 2) {
        twoPipes();
    }
    else {
        perror("This shell only supports 2 pipes.");
        exit(EXIT_FAILURE);
    }
}

// no pipes
void noPipes() {
    // Tokenize the input.
    char **proc1 = tokenizeInput(pipeCommands[0]);
    if (strcmp(proc1[0], "exit") == 0) // Check for the "exit" built-in command.
        exit(1);
    //shellExit();
    pid_t pid = fork();
    if (pid > 0) // Parent process
    {
        wait(0);
    }
    else if (pid == 0) // Child process
    {
//    if (strcmp(proc1[0], "history") == 0) // Check for the "history" built-in command.
//    {
//      // Check the argument.
//      if (strcmp(proc1[1], "") == 0)
//      {
//        shellHistoryDefault();
//      }
//      else
//      {
//        int x = atoi(proc1[1]);
//        shellHistory(x);
//      }
//      exit(EXIT_SUCCESS);
//    }
        if (strchr(pipeCommands[0], '>') != NULL) // Check for redirected input
        {
            //redirectInput();
        }
        else if (strchr(pipeCommands[0], '<') != NULL) {
            //redirectOutput();
        }
        else // All other commands
        {
            if (execvp(proc1[0], proc1) < 0);
            {
                perror("Could not exec.\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    else // Fork failed
    {
        perror("Fork failed.\n");
    }
}

// The input has one pipe
void onePipe() {
    int fds[2];
    pid_t pid1;
    pid_t pid2;
    // Tokenize the input
    char **proc1 = tokenizeInput(pipeCommands[0]);
    char **proc2 = tokenizeInput(pipeCommands[1]);

    // Pipe
    //if (pipe(fds) < 0)
    //  perror("Could not pipe");

    // Initial fork
    if ((pid1 = fork()) < 0) {
        perror("Could not perform initial fork");
        exit(EXIT_FAILURE);
    }
    else if (pid1 > 0) // Parent process waits for child to finish
        wait(0);
    else // Child process forks again and pipes
    {
        // Pipe
        if (pipe(fds) < 0)
            perror("Could not pipe");


        // Second Fork
        if ((pid2 = fork()) < 0) // Fork and check for error.
        {
            perror("Could not fork");
            exit(EXIT_FAILURE);
        }
        else if (pid2 > 0) // Parent process
        {
            close(fds[1]); // Close read end
            // Close stdout, redirect to the writing end of the pipe.
            if (dup2(fds[0], 0) < 0) {
                perror("Could not dup2");
                exit(EXIT_FAILURE);
            }
            wait(0);
            execvp(proc2[0], proc2);
            perror("Could not exec");
            exit(EXIT_FAILURE);
        }
        else // Child process
        {
            close(fds[0]);
            if (dup2(fds[1], 1) < 0) {
                perror("Could not dup2");
                exit(EXIT_FAILURE);
            }
            execvp(proc1[0], proc1);
            perror("Could not exec");
            exit(EXIT_FAILURE);
        }
    }
}


// The input has two pipes
void twoPipes() {
    int fds1[2];
    int fds2[2];
    pid_t pid1;
    pid_t pid2;
    pid_t pid3;
    // Tokenize the input
    char **proc1 = tokenizeInput(pipeCommands[0]);
    char **proc2 = tokenizeInput(pipeCommands[1]);
    char **proc3 = tokenizeInput(pipeCommands[2]);



    // Initial fork
    if ((pid1 = fork()) < 0) {
        perror("Could not perform initial fork");
        exit(EXIT_FAILURE);
    }
    else if (pid1 > 0) // Parent process waits for child to finish
        wait(0);


    else // Child process forks again and pipes
    {
        // Pipe
        if (pipe(fds1) < 0)
            perror("Could not pipe");


        // Second Fork
        if ((pid2 = fork()) < 0) // Fork and check for error.
        {
            perror("Could not fork");
            exit(EXIT_FAILURE);
        }
        else if (pid2 > 0) // Parent process
        {
            close(fds1[1]); // Close read end
            // Close stdout, redirect to the writing end of the pipe.
            if (dup2(fds1[0], 0) < 0) {
                perror("Could not dup2");
                exit(EXIT_FAILURE);
            }
            wait(0);
            execvp(proc3[0], proc3);
            perror("Could not exec");
            exit(EXIT_FAILURE);
        }


        else // Child process forks again and pipes
        {
            // Pipe
            if (pipe(fds2) < 0)
                perror("Could not pipe");

            // Third Fork
            if ((pid3 = fork()) < 0) {
                perror("Could not fork");
                exit(EXIT_FAILURE);
            }
            else if (pid3 > 0) // Parent process
            {
                close(fds1[0]); // Close write end of first pipe
                close(fds2[1]); // Close read end of second pipe
                if (dup2(fds2[0], 0) < 0) //Send stdin to
                {
                    perror("Could not dup2");
                    exit(EXIT_FAILURE);
                }
                if (dup2(fds1[1], 1) < 0) {
                    perror("Could no dup2");
                    exit(EXIT_FAILURE);
                }
                wait(0);
                execvp(proc2[0], proc2);
                perror("Could not exec");
                exit(EXIT_FAILURE);
            }
            else // Child process
            {
                close(fds2[0]);
                if (dup2(fds2[1], 1) < 0) {
                    perror("Could not dup2");
                    exit(EXIT_FAILURE);
                }
                execvp(proc1[0], proc1);
                perror("Could not exec");
                exit(EXIT_FAILURE);
            }
        }
    }
}

// Tokenizes a string according to spaces. This does not modify the original string.
char **tokenizeInput(char *input) {
    int i, j, k, elementcount;
    char tempInput[MAX + 1]; // Used to preserve char* input param.
    char countInput[MAX + 1];

    // Copy the input into the temp string and replace all newline chacacters with null terminators.
    strcpy(tempInput, input);
    for (k = 0; k < MAX + 1; k++)
        if (tempInput[k] == '\n')
            tempInput[k] = '\0';
    strcpy(countInput, tempInput);

    // Count how many elements there are in the input
    elementcount = 0;
    char *tempCountToken = strtok(countInput, " ");
    while (tempCountToken) {
        elementcount++;
        tempCountToken = strtok(NULL, " ");
    }
    // Initialize the array we will return.
    char **tokenized = (char **) calloc(10, sizeof(char *));
    for (j = 0; j < elementcount; j++) {
        tokenized[j] = (char *) calloc((MAX + 1), sizeof(char));
    }

    // Tokenize temp.
    char *token = strtok(tempInput, " ");
    for (i = 0; i < 10; i++) {
        if (token == NULL)
            break;
        strcpy(tokenized[i], token);
        token = strtok(NULL, " ");
    }
    return tokenized;
}
