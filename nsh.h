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
char* getLine(void);

//int_fast16_t makeTokenList(char *,
//                           char *);

int8_t commandLoop(void);

#endif /* NSH_H_ */
