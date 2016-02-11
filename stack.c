/*
 * A stack implemented using a linked list.
 * Includes a non-standard function to reset the topOfStack pointer
 * to the most recently pushed item.
 *
 *      Author: David Newell
 *      SN: 250332100
 *      For: Professor Hanan Lutfiyya
 */

#include "unifiedHeader.h"


/*
 * Data structure for a node
 */
struct node {
	char *string;
	struct node *next;
};

/*
 * Globals
 */
struct node *topOfStack = NULL;                                             // the top of the stack.
struct node *permaTop = NULL;

/**
 * Function push pushes a string onto the stack
 */
void push(const char *strToPush)
{
	char *data;
	struct node *currentNode;

    if ((data = malloc((strlen(strToPush) + 1) * sizeof(char))) == NULL) {   // catch memory allocation error
        printf("Error: could not allocate memory.\n");
        exit(EXIT_FAILURE);
	}
    strcpy(data, strToPush);


    if ((currentNode = malloc(sizeof(struct node))) ==
        NULL) {                    											// allocates and catches possible error
    	printf("Fatal memory allocation error.\n");
		exit(1);  															// program exits if allocation fails
	}
	(*currentNode).string = data;  											// string pointer added to the list
    (*currentNode).next = topOfStack;                                       // next element

    topOfStack = currentNode;                                               // top of the stack now points to new element
    permaTop = currentNode;                                                 // set global un-stack-like permanent top variable
}



/*
 * Function pop returns the top data item on the stack
 */
char *pop(void)
{
	char *data;
	struct node *currentNode;

	if (topOfStack)
	{
		currentNode = topOfStack;
        topOfStack = (*topOfStack).next;
        data = (*currentNode).string;
		return data;
	}
	else
	{
	return NULL;
	}
}

/*
 * Function reset stack returns the pointer to the top of the stack to the
 * most recent item pushed
 */
void resetStack() {
    topOfStack = permaTop;
}
