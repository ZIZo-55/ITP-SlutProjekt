/*
* File: gen.h
* Version: 1.0
* Modified 2019-11-10 by Anders Carstensen
* A set of functions simplifiying things
*/

#ifndef _gen
#define _gen

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "genlib.h"
#include "simpio.h"

//typedef unsigned char * ustring;

/********************************************************************
Function: clearStdIn()
Usage: clearStdIn();
---------------------------------------------------------------------
Purpose: Removes trailing characters from inputbuffer
********************************************************************/
void clearStdIn(void);

/********************************************************************
Function: pause()
Usage: pause();
---------------------------------------------------------------------
Purpose: Removes trailing characters from inputbuffer and halt program
********************************************************************/
void pause(ustring); 

/********************************************************************
Function: closeFile()
Usage: ok = closeFile(fileHandle);
---------------------------------------------------------------------
Purpose: closes the passed file handle and sets it to NULL.
********************************************************************/
bool closeFile(FILE**);

/********************************************************************
Function: getInt()
Usage: int anInt = getInt(aMessage);
---------------------------------------------------------------------
Purpose: prompts the user to enter an integer, which then is returned
********************************************************************/
int getInt(string);

/********************************************************************
Function: getString()
Usage: string aStr = getString(aMessage);
---------------------------------------------------------------------
Purpose: prompts the user to enter a string, which then is returned.
The used memory need to be released with free().
********************************************************************/
string getString(string);

#endif