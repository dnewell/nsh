/**
 *  nsh is a simple POSIX-compatible shell written by David Newell.
 *
 * 	Author: David Newell
 * 	SN: 250332100
 * 	For: Professor Hanan Lutfiyya
 */

#ifndef NSH_STACK_H
#define NSH_STACK_H

void resetStack(void);

char *pop(void);

void push(const char *strToPush);


#endif //NSH_STACK_H
