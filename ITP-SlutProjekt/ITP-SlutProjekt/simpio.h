/*
 * File: simpio.h
 * Version: 1.1
 * Modified on Wed Apr 27 07:29:13 1994 by eroberts
 * Last modified 2019-10-25 by Anders Carstensen
 *	Changed name of functions to begin with lower case letter
 *	In source file added - #pragma warning(disable:4996)
 *	which in windows enables the use of unsafe functions
 *	such as scanf. 
 * -----------------------------------------------------
 * This interface provides access to a simple package of
 * functions that simplify the reading of input data.
 */

#ifndef _simpio_h
#define _simpio_h

#include "genlib.h"

/*
 * Function: getInt
 * Usage: i = getInteger();
 * ------------------------
 * getInteger reads a line of text from standard input and scans
 * it as an integer.  The integer value is returned.  If an
 * integer cannot be scanned or if more characters follow the
 * number, the user is given a chance to retry.
 */

int getInteger(void);

/*
 * Function: getLong
 * Usage: l = getLong();
 * ---------------------
 * getLong reads a line of text from standard input and scans
 * it as a long integer.  The value is returned as a long.
 * If an integer cannot be scanned or if more characters follow
 * the number, the user is given a chance to retry.
 */

long getLong(void);

/*
 * Function: getReal
 * Usage: x = getReal();
 * ---------------------
 * getReal reads a line of text from standard input and scans
 * it as a double.  If the number cannot be scanned or if extra
 * characters follow after the number ends, the user is given
 * a chance to reenter the value.
 */

double getReal(void);

/*
 * Function: getLine
 * Usage: s = getLine();
 * ---------------------
 * getLine reads a line of text from standard input and returns
 * the line as a string.  The newline character that terminates
 * the input is not stored as part of the string.
 */

string getLine(void);

/*
 * Function: readLine
 * Usage: s = readLine(infile);
 * ----------------------------
 * readLine reads a line of text from the input file and
 * returns the line as a string.  The newline character
 * that terminates the input is not stored as part of the
 * string.  The readLine function returns NULL if infile
 * is at the end-of-file position.
 */

string readLine(FILE *infile);

#endif
