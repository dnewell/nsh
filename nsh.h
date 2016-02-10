/*
 * nsh.h
 *
 *      Author: David Newell
 *      SN: 250332100
 *      For: Professor Hanan Lutfiyya
 */

#ifndef NSH_H_
#define NSH_H_
/*
 * Function prototypes
 */
char* getLine();

int_fast16_t makeTokenList(char * inputBuffer, char * tokenArray[]);
void addToHistory(char *);
int commandLoop();
void displayHistory();
int_fast16_t makeTokenList(char *, char *asdasd[]);
int8_t doMainFork();
//int doCommand(char *tok[], int num);

#endif /* NSH_H_ */
