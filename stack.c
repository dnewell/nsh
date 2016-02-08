/*
 * A basic stack implemented using a linked list
 *
 *      Author: David Newell
 *      SN: 250332100
 *      For: Professor Hanan Lutfiyya
 */

#include "unifiedHeader.h"


/* NODE DATA DEFINITION (RECURSIVE) */
struct node {
	char *string;
	struct node *next;
};

/* GLOBALS */
struct node *topOfStack=NULL; // the top of the stack. Global variable.


/**
 * push functions pushes a string onto the stack
 *  TODO: DEL: (Space must be allocated for the string.
 *
 */
void push(const char *strToPush)
{
	char *data;
	struct node *currentNode;

	// Allocate memory for the string
    if ((data=malloc((strlen(strToPush)+1)*sizeof(char))) == NULL) {
		printf("Fatal memory allocation error.\n");
		exit(1);  // Exit the program with error
	}
	strcpy(data, strToPush); // Copy the string


if ((currentNode=malloc(sizeof(struct node))) == NULL) {					// allocate memory for a node, and check for malloc error
    	printf("Fatal memory allocation error.\n");
		exit(1);  															// program exits if allocation fails
	}
	(*currentNode).string = data;  											// string pointer added to the list
	(*currentNode).next = topOfStack; // link to next element.
	topOfStack = currentNode;  // Top of stack now points to new element
}

/* --------------------------------------------------------------------------
 * function pop: Remove last entry of the stack.
 *      returns the string kept at the top of the stack.
 * --------------------------------------------------------------------------
 */
char *pop(void)
{
	char *data;
	struct node *currentNode;


	if (topOfStack)
	{
		currentNode = topOfStack;
	    topOfStack = (*topOfStack).next; 									// make the top of stack point to the next element in list
	    data = (*currentNode).string;									//
		free(currentNode); 													// must always give as we've taken
		return data;
	}
	else
	{
	return NULL;
	}
}




///*
// * Push:
// * A canonical stack operation
// */

