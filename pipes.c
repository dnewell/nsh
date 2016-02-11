/**
 *  shell is a simple POSIX-compatible shell written by David Newell.
 *
 * 	Author: David Newell
 * 	SN: 250332100
 * 	For: Professor Hanan Lutfiyya
 */
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
        exit(1);
    }
}

/*
 * This function executes a command with no pipes its string representation
 */
void noPipes() {

    char **process_one = make_tokenlist(pipeCommands[0]);

    pid_t pid = fork();

    if (pid > 0)                                                // in parent
    {
        wait(0);
    }
    else if (pid == 0)                                          // in child
    {

        if (isOutRedirect(pipeCommands[0]))                     // check for i/o redirection char
        {
            ioRedirectOutput();
        }
        else if (isInRedirect(pipeCommands[0]))
        {

        }
        else
        {
            if (execvp(process_one[0], process_one) < 0);       // exec error
            {
                exit(1);
            }
        }
    }
    else                                                        // Fork failed
    {
        printf("Error: fork failure.");
    }
}

/*
 * Check for > i/o redirection
 */
int isOutRedirect(char * charToCheck){
    return (strchr(charToCheck, '>') != NULL);
}

/*
 * Check for < i/o redirection
 */
int isInRedirect(char * charToCheck){
    return (strchr(charToCheck, '<') != NULL);
}


/*
 * This function executes a command with one pipe in its string representation
 */
void onePipe() {
    int fileDesc[2];

/* FORK 1 */
    pid_t pidOne = fork();


    char **process_one = make_tokenlist(pipeCommands[0]);
    char **process_two = make_tokenlist(pipeCommands[1]);


    if (pidOne < 0)
    {
        printf("Error: fork() failed.");
        exit(1);
    }
    else if (pidOne > 0)
    {
        wait(0);                                                    // wait for child to return
    }
    else
    {                                                               // now the child forks
        if (pipe(fileDesc) < 0)                                     // try pipe
        {
            printf("Error: failed to establish pipe");
            exit(1);
        }


/* FORK 2 */
        pid_t pidTwo = fork ();

        if (pidTwo < 0)
        {
            printf("Error: fork() failed.");
            exit(1);
        }
        else if (pidTwo > 0)
        {
            close(fileDesc[1]);                                     // in parent, redirect stdout to pipe input
            if (dup2(fileDesc[0], 0) < 0)
            {
                printf("Error: dup2() error");
                exit(1);
            }
            wait(0);

            execvp(process_two[0], process_two);

            printf("Error: execvp Error");

            exit(1);
        }
        else                                                        // pid == 0, in child
        {
            close(fileDesc[0]);

            if (dup2(fileDesc[1], 1) < 0)
            {
                exit(1);
            } else {
                execvp(process_one[0], process_one);                // exec
                exit(1);
            }

        }
    }
}

/*
 * Function removes all '>' from string
 */
void sanitizeOut(){
    int i;
    for (i = 0; i < strlen(pipeCommands[0]); i++)
    {
        if (pipeCommands[0][i] == '>')
        {
            pipeCommands[0][i] = ' ';
        }
    }
}

/*
 * Function handles i/o redirection
 */
void ioRedirectOutput()
{

    sanitizeOut();

    char** input = make_tokenlist(pipeCommands[0]);

    FILE* file = fopen(input[1], "w+");                              // open file for writing, overwriting if it exists

    int des = fileno(file);                                          // gets the file descriptor

/* FORK */
    pid_t pid = fork();

    if (pid > 0)                                    // in parent
    {
        wait(0);

    }
    else if (pid < 0)                               // error
    {
        printf("Error: fork() failed.");
        exit(1);
    }
    else                                            // in child
    {
        if (dup2(des, 1) < 0)
        {
            printf("Error: dup2() failed.");
            exit(1);
        }
        execvp(input[0], input);
    }
}

/*
 * This function executes a command with two pipes in its string representation
 */
void twoPipes() {

    char **process_one = make_tokenlist(pipeCommands[0]);
    char **process_two = make_tokenlist(pipeCommands[1]);
    char **process_three = make_tokenlist(pipeCommands[2]);
    
/* FORK 1 */
    pid_t pidOne = fork();
    if (pidOne < 0) 
    {
        printf("Error: fork() failed.");
        exit(1);
    }
    else if (pidOne > 0)
    {
        wait(0);                                                    // wait for child to return
    }
    else
    {
        int fileDesc[2];
        if (pipe(fileDesc) < 0)                                     // try pipe
        {
            printf("Error: failed to establish pipe");
            exit(1);
        }

/* FORK 2 */
        pid_t pidTwo = fork();

        if (pidTwo < 0)
        {
            printf("Error: fork() failed.");
            exit(1);
        }
        else if (pidTwo > 0)                                        // parent process
        {
            close(fileDesc[1]);                                     // in parent: redirect stdout to pipe input
            if (dup2(fileDesc[0], 0) < 0)
            {
                printf("Error: dup2() error");
                exit(1);
            }
            wait(0);

            execvp(process_three[0], process_three);

            printf("Error: execvp Error");

            exit(1);
        }
        else                                                        // Child process forks again and pipes
        {
            int fileDescOne[2];
            if (pipe(fileDescOne) < 0)
            {
                printf("Error: failed to establish pipe");
                exit(1);
            }

/* FORK 3 */
            pid_t pidThree = fork();
            if (pidThree < 0) {
                printf("Error: fork() failed.");
                exit(1);
            }
            else if (pidThree > 0)
            {
                close(fileDesc[0]);                                     // in parent, redirect stdout to pipe input

                close(fileDescOne[1]);                                  // pipe input closed

                if ((dup2(fileDescOne[0], 0) < 0) || (dup2(fileDesc[1], 1) < 0))
                {
                    printf("Error: dup2() failed");
                    exit(1);
                }
                wait(0);

                execvp(process_two[0], process_two);

                printf("Error: execvp failed");

                exit(1);
            }
            else                                                       // pid == 0, in child
            {
                close(fileDescOne[0]);
                if (dup2(fileDescOne[1], 1) < 0)
                {
                    exit(1);
                }

                execvp(process_one[0], process_one);

                printf("Error: execvp failed");

                exit(1);
            }
        }
    }
}

/*
 * Tokenize a string using spaces as the delimiter.
 * Based on the code provided on the course website,
 * but heavily modified.
 */
char **make_tokenlist(char *input) {
    
    char **result = (char **) calloc(15, sizeof(char *));
    char *token;
    char inputCopy[MAX + 1];

    strcpy(inputCopy, input);                    // duplicate of input, to leave input unmodified

    int i;
    for (i = 0; i < MAX + 1; i++)                // Sanitize input.  Replace '\n' with '\0' (null)
    {
        if (inputCopy[i] == '\n')
        {
            inputCopy[i] = '\0';
        }
    }

    char numberInputTokens[MAX + 1];
    strcpy(numberInputTokens, inputCopy);

    char *tokensSoFar = strtok(numberInputTokens, " ");
    int count = 0;
    while (*tokensSoFar)
    {                                                       // count tokens in input
        *tokensSoFar = strtok(NULL, " ");
       // tokensSoFar = strtok(NULL, " ");
        count++;
    }

    for (i = 0; i < count; i++)
    {
        result[i] = (char *) calloc((MAX + 1), sizeof(char));
    }

    token = strtok(inputCopy, " ");                         // init strtok

    for (i = 0; i < 10; i++)                                // split input on spaces
    {
        if (token != NULL)
        {
            strcpy(result[i], token);

            token = strtok(NULL, " ");
        }
        else
        {
            break;
        }
    }

    return result;
}
