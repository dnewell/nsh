/**
 *  nsh is a simple POSIX-compatible shell written by David Newell.
 *
 * 	Author: David Newell
 * 	SN: 250332100
 * 	For: Professor Hanan Lutfiyya
 */

#ifndef NSH_PIPES_H
#define NSH_PIPES_H

void piper(int);

void noPipes();

void onePipe();

void twoPipes();

char **make_tokenlist(char *input);

#endif //NSH_PIPES_H
