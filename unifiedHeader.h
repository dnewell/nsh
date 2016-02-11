/**
 *  shell is a simple POSIX-compatible shell written by David Newell.
 *
 * 	Author: David Newell
 * 	SN: 250332100
 * 	For: Professor Hanan Lutfiyya
 */

#ifndef UNIFIEDHEADER_H_
#define UNIFIEDHEADER_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#define MAX 256                                 // maximum input line length
/* GLOBALS */
extern char pipeCommands[3][MAX];				// array global to contain the three commands we'll be piping



#endif /* UNIFIEDHEADER_H_ */
