#pragma warning(disable:4996)
/*
 * File: strlib.c
 * Version: 1.0
 * Last modified on Fri Jul 15 14:10:41 1994 by eroberts
 * -----------------------------------------------------
 * This file implements the strlib.h interface.
 */

/*
 * General implementation notes:
 * -----------------------------
 * This module implements the strlib library by mapping all
 * functions into the appropriate calls to the ANSI <string.h>
 * interface.  The implementations of the individual functions
 * are all quite simple and do not require individual comments.
 * For descriptions of the behavior of each function, see the
 * interface.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "genlib.h"
#include "strlib.h"

/*
 * Constant: MaxDigits
 * -------------------
 * This constant must be larger than the maximum
 * number of digits that can appear in a number.
 */

#define MaxDigits 30

/* Private function prototypes */

static string createString(int len);

/* Section 1 -- Basic string operations */

string concat(string s1, string s2)
{
    string s;
    int len1, len2;

    if (s1 == NULL || s2 == NULL) {
        error("NULL string passed to concat");
    }
    len1 = strlen(s1);
    len2 = strlen(s2);
    s = createString(len1 + len2);
    strcpy(s, s1);
    strcpy(s + len1, s2);
    return (s);
}

char ithChar(string s, int i)
{
    int len;

    if (s == NULL) error("NULL string passed to ithChar");
    len = strlen(s);
    if (i < 0 || i > len) {
        error("Index outside of string range in ithChar");
    }
    return (s[i]);
}

string subString(string s, int p1, int p2)
{
    int len;
    string result;

    if (s == NULL) error("NULL string passed to subString");
    len = strlen(s);
    if (p1 < 0) p1 = 0;
    if (p2 >= len) p2 = len - 1;
    len = p2 - p1 + 1;
    if (len < 0) len = 0;
    result = createString(len);
    strncpy(result, s + p1, len);
    result[len] = '\0';
    return (result);
}

string charToString(char ch)
{
    string result;

    result = createString(1);
    result[0] = ch;
    result[1] = '\0';
    return (result);
}

int stringLength(string s)
{
    if (s == NULL) error("NULL string passed to stringLength");
    return (strlen(s));
}

string copyString(string s)
{
    string newstr;

    if (s == NULL) error("NULL string passed to copyString");
    newstr = createString(strlen(s));
    strcpy(newstr, s);
    return (newstr);
}

/* Section 2 -- String comparison functions */

bool stringEqual(string s1, string s2)
{
    if (s1 == NULL || s2 == NULL) {
        error("NULL string passed to stringEqual");
    }
    return (strcmp(s1, s2) == 0);
}

int stringCompare(string s1, string s2)
{
    if (s1 == NULL || s2 == NULL) {
        error("NULL string passed to stringCompare");
    }
    return (strcmp(s1, s2));
}

/* Section 3 -- Search functions */

int findChar(char ch, string text, int start)
{
    char *cptr;

    if (text == NULL) error("NULL string passed to findChar");
    if (start < 0) start = 0;
    if (start > strlen(text)) return (-1);
    cptr = strchr(text + start, ch);
    if (cptr == NULL) return (-1);
    return ((int) (cptr - text));
}

int findString(string str, string text, int start)
{
    char *cptr;

    if (str == NULL) error("NULL pattern string in findString");
    if (text == NULL) error("NULL text string in findString");
    if (start < 0) start = 0;
    if (start > strlen(text)) return (-1);
    cptr = strstr(text + start, str);
    if (cptr == NULL) return (-1);
    return ((int) (cptr - text));
}

/* Section 4 -- Case-conversion functions */

string convertToLowerCase(string s)
{
    string result;
    int i;

    if (s == NULL) {
        error("NULL string passed to convertToLowerCase");
    }
    result = createString(strlen(s));
    for (i = 0; s[i] != '\0'; i++) result[i] = tolower(s[i]);
    result[i] = '\0';
    return (result);
}

string convertToUpperCase(string s)
{
    string result;
    int i;

    if (s == NULL) {
        error("NULL string passed to convertToUpperCase");
    }
    result = createString(strlen(s));
    for (i = 0; s[i] != '\0'; i++) result[i] = toupper(s[i]);
    result[i] = '\0';
    return (result);
}

/* Section 5 -- Functions for converting numbers to strings */

string integerToString(int n)
{
    char buffer[MaxDigits];

    sprintf(buffer, "%d", n);
    return (copyString(buffer));
}

int stringToInteger(string s)
{
    int result;
    char dummy;

    if (s == NULL) {
        error("NULL string passed to stringToInteger");
    }
    if (sscanf(s, " %d %c", &result, &dummy) != 1) {
        error("stringToInteger called on illegal number %s", s);
    }
    return (result);
}

string realToString(double d)
{
    char buffer[MaxDigits];

    sprintf(buffer, "%G", d);
    return (copyString(buffer));
}

double stringToReal(string s)
{
    double result;
    char dummy;

    if (s == NULL) error("NULL string passed to stringToReal");
    if (sscanf(s, " %lg %c", &result, &dummy) != 1) {
        error("stringToReal called on illegal number %s", s);
    }
    return (result);
}

/* Private functions */

/*
 * Function: createString
 * Usage: s = createString(len);
 * -----------------------------
 * This function dynamically allocates space for a string of
 * len characters, leaving room for the null character at the
 * end.
 */

static string createString(int len)
{
    return ((string) getBlock(len + 1));
}
