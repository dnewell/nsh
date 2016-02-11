/**
 *  shell is a simple POSIX-compatible shell written by David Newell.
 *
 * 	Author: David Newell
 * 	SN: 250332100
 * 	For: Professor Hanan Lutfiyya
 */

#ifndef NSH_H_
#define NSH_H_



/*
 * Function prototypes
 */

void addToHistory(char *);
int commandLoop();
void displayHistory();
void initialize(void);


#endif /* NSH_H_ */
