/*
 * File: strlib.h
 * Version: 1.1
 * Modified on Fri Jul 15 14:10:40 1994 by eroberts
 * Last modified 2019-10-25 by Anders Carstensen
 *	Changed name of functions to begin with lower case letter.
 *	In source file added - #pragma warning(disable:4996),
 *	which in windows enables the use of unsafe functions 
 *	such as scanf, used in some of Roberts functions. 
 * -----------------------------------------------------
 * The strlib.h file defines the interface for a simple
 * string library.  In the context of this package, strings
 * are considered to be an abstract data type, which means
 * that the client relies only on the operations defined for
 * the type and not on the underlying representation.
 */

/*
 * Cautionary note:
 * ----------------
 * Although this interface provides an extremely convenient
 * abstraction for working with strings, it is not appropriate
 * for all applications.  In this interface, the functions that
 * return string values (such as concat and subString) do so
 * by allocating new memory.  Over time, a program that uses
 * this package will consume increasing amounts of memory
 * and eventually exhaust the available supply.  If you are
 * writing a program that runs for a short time and stops,
 * the fact that the package consumes memory is not a problem.
 * If, however, you are writing an application that must run
 * for an extended period of time, using this package requires
 * that you make some provision for freeing any allocated
 * storage.
 */

#ifndef _strlib_h
#define _strlib_h

#include "genlib.h"

/* Section 1 -- Basic string operations */

/*
 * Function: concat
 * Usage: s = concat(s1, s2);
 * --------------------------
 * This function concatenates two strings by joining them end
 * to end.  For example, concat("ABC", "DE") returns the string
 * "ABCDE".
 */

string concat(string s1, string s2);

/*
 * Function: ithChar
 * Usage: ch = ithChar(s, i);
 * --------------------------
 * This function returns the character at position i in the
 * string s.  It is included in the library to make the type
 * string a true abstract type in the sense that all of the
 * necessary operations can be invoked using functions. Calling
 * ithChar(s, i) is like selecting s[i], except that ithChar
 * checks to see if i is within the range of legal index
 * positions, which extend from 0 to stringLength(s).
 * ithChar(s, stringLength(s)) returns the null character
 * at the end of the string.
 */

char ithChar(string s, int i);

/*
 * Function: subString
 * Usage: t = subString(s, p1, p2);
 * --------------------------------
 * subString returns a copy of the substring of s consisting
 * of the characters between index positions p1 and p2,
 * inclusive.  The following special cases apply:
 *
 * 1. If p1 is less than 0, it is assumed to be 0.
 * 2. If p2 is greater than the index of the last string
 *    position, which is stringLength(s) - 1, then p2 is
 *    set equal to stringLength(s) - 1.
 * 3. If p2 < p1, subString returns the empty string.
 */

string subString(string s, int p1, int p2);

/*
 * Function: charToString
 * Usage: s = charToString(ch);
 * ----------------------------
 * This function takes a single character and returns a
 * one-character string consisting of that character.  The
 * charToString function is useful, for example, if you
 * need to concatenate a string and a character.  Since
 * concat requires two strings, you must first convert
 * the character into a string.
 */

string charToString(char ch);

/*
 * Function: stringLength
 * Usage: len = stringLength(s);
 * -----------------------------
 * This function returns the length of s.
 */

int stringLength(string s);

/*
 * Function: copyString
 * Usage: newstr = copyString(s);
 * ------------------------------
 * copyString copies the string s into dynamically allocated
 * storage and returns the new string.  This function is not
 * ordinarily required if this package is used on its own,
 * but is often necessary when you are working with more than
 * one string package.
 */

string copyString(string s);

/* Section 2 -- String comparison functions */

/*
 * Function: stringEqual
 * Usage: if (stringEqual(s1, s2)) ...
 * -----------------------------------
 * This function returns TRUE if the strings s1 and s2 are
 * equal.  For the strings to be considered equal, every
 * character in one string must precisely match the
 * corresponding character in the other.  Uppercase and
 * lowercase characters are considered to be different.
 */

bool stringEqual(string s1, string s2);

/*
 * Function: stringCompare
 * Usage: if (stringCompare(s1, s2) < 0) ...
 * -----------------------------------------
 * This function returns a number less than 0 if string s1
 * comes before s2 in alphabetical order, 0 if they are equal,
 * and a number greater than 0 if s1 comes after s2.  The
 * ordering is determined by the internal representation used
 * for characters, which is usually ASCII.
 */

int stringCompare(string s1, string s2);

/* Section 3 -- Search functions */

/*
 * Function: findChar
 * Usage: p = findChar(ch, text, start);
 * -------------------------------------
 * Beginning at position start in the string text, this
 * function searches for the character ch and returns the
 * first index at which it appears or -1 if no match is
 * found.
 */

int findChar(char ch, string text, int start);

/*
 * Function: findString
 * Usage: p = findString(str, text, start);
 * ----------------------------------------
 * Beginning at position start in the string text, this
 * function searches for the string str and returns the
 * first index at which it appears or -1 if no match is
 * found.
 */

int findString(string str, string text, int start);

/* Section 4 -- Case-conversion functions */

/*
 * Function: convertToLowerCase
 * Usage: s = convertToLowerCase(s);
 * ---------------------------------
 * This function returns a new string with all
 * alphabetic characters converted to lower case.
 */

string convertToLowerCase(string s);

/*
 * Function: convertToUpperCase
 * Usage: s = convertToUpperCase(s);
 * ---------------------------------
 * This function returns a new string with all
 * alphabetic characters converted to upper case.
 */

string convertToUpperCase(string s);

/* Section 5 -- Functions for converting numbers to strings */

/*
 * Function: integerToString
 * Usage: s = integerToString(n);
 * ------------------------------
 * This function converts an integer into the corresponding
 * string of digits.  For example, integerToString(123)
 * returns "123" as a string.
 */

string integerToString(int n);

/*
 * Function: stringToInteger
 * Usage: n = stringToInteger(s);
 * ------------------------------
 * This function converts a string of digits into an integer.
 * If the string is not a legal integer or contains extraneous
 * characters, stringToInteger signals an error condition.
 */

int stringToInteger(string s);

/*
 * Function: realToString
 * Usage: s = realToString(d);
 * ---------------------------
 * This function converts a floating-point number into the
 * corresponding string form.  For example, calling
 * realToString(23.45) returns "23.45".  The conversion is
 * the same as that used for "%G" format in printf.
 */

string realToString(double d);

/*
 * Function: stringToReal
 * Usage: d = stringToReal(s);
 * ---------------------------
 * This function converts a string representing a real number
 * into its corresponding value.  If the string is not a
 * legal floating-point number or if it contains extraneous
 * characters, stringToReal signals an error condition.
 */

double stringToReal(string s);

#endif
