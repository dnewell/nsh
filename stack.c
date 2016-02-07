/*
 * A basic stack implemented using a linked list
 *
 *      Author: David Newell
 *      SN: 250332100
 *      For: Professor Hanan Lutfiyya
 */

#include "unifiedHeader.h"

// Data structure definition
struct listElement {
	char *s;
	struct listElement *next;  // Yes the definition can be recursive!
};

struct listElement *tos=NULL; // the top of the stack. Global variable.


/* --------------------------------------------------------------------------
 * function push: Enter string s into the stack.
 *  Space must be allocated for the string.
 * --------------------------------------------------------------------------
 */
void push(char *s)
{
	char *p;
	struct listElement *q;

	// Allocate memory for the string
    if ((p=malloc((strlen(s)+1)*sizeof(char))) == NULL) {
		printf("Fatal memory allocation error.\n");
		exit(1);  // Exit the program with error
	}
	strcpy(p, s); // Copy the string

	// Allocate memory for another listElement
    if ((q=malloc(sizeof(struct listElement))) == NULL) {
		printf("Fatal memory allocation error.\n");
		exit(1);  // Exit the program with error
	}
	q->s = p;  // add pointer to string into the list element
    // Note: q->s  is a shortcut for  (*q).s
	q->next = tos; // link to next element.
	tos = q;  // Top of stack now points to new element
}

/* --------------------------------------------------------------------------
 * function pop: Remove last entry of the stack.
 *      returns the string kept at the top of the stack.
 * --------------------------------------------------------------------------
 */
char *pop(void)
{
	char *p;
	struct listElement *q;

	if (tos == NULL)
		return NULL;
	q = tos;
    tos = tos->next; // Top of stack points to next element
	p = q->s;
	free(q); // Release memory occupied by the poped listElement
	return p;
}


int main(void)
{
	char s[100];
	char *p;

	do {
		scanf("%s", s); // read a string from keyboard
		push(s);
	} while (strlen(s) != 1); // exit if a single char string is read

	// Pop everything out of the stack and print:
	while ((p=pop()) != NULL) {
		printf("%s\n", p); // print string and change line.
		free(p);  // Release the memory used by the string
	}
}


///*
// * Push:
// * A canonical stack operation
// */

