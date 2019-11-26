#ifndef _wordManager
#define _wordManager

//Include files, to be added here
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include "strlib.h"	//Roberts modified library
#include "simpio.h"	//Roberts modified library
#include <string.h>

//Constants
#define WORDLISTNAME "ordlista.txt"	//The default name of the wordlist
#define MAXWORDLENGTH 30	//The maximum stringlength for a word stored in the list array
#define MAXNAMELENGTH 30	//The maximum string length for a filename
#define MAXNOOFWORDS 10000	//The maximum number of words in the list array

//Structs
typedef struct {
	unsigned char listName[MAXNAMELENGTH];	//The name of the file storing the word list
	int listSize;		//The maximum number of words that can be held
	int noOfWords;		//The number of elements in the word array (total)
	int noOfValid;		//The number of valid words
} listT;	//A struct type for holding information about a word list array 

typedef struct {
	unsigned char text[MAXWORDLENGTH];  //The word
	int count;	//The frequency of use uptil now
	bool valid;	//True if not outdated, only used in the array
} wordT; //A struct type for the word element stored in the list array


//Function declarations

/********************************************************************
Function: wordManager()
Usage: errno_t anError = wordManager(aFileName);
---------------------------------------------------------------------
Purpose: To initialize the wordlist. Must be done before using the 
wordlist. The lisT* pointer passed to the function contains info 
about the filename for storing the wordlist, and the maximum number 
of elements that the wordlist may contain. Checks if the wordlist 
file  exist. If not the file will be created. 
Creates a struct variable for holding the information about the 
wordlist. Creates an array for holding the words in the list and 
loads the array with data from the wordlist file.
Returns an error number if e.g. it is not possible to open the 
wordlist file. 
********************************************************************/
errno_t wordManager(listT*);

/********************************************************************
Function: getList()
Usage: wordT* pWordList = getList();
---------------------------------------------------------------------
Purpose: Return a pointer to the word list array, such that existing
elements in the list cannot be changed. This makes it possible for a
user function, outside the module, to read the elements.
********************************************************************/
const wordT* getList(void);

/********************************************************************
Function: getNoOfWords()
Usage: int noOfWords = getNoOfWords();
---------------------------------------------------------------------
Purpose: Returns the total number of words stored in the list.
Regardless of if the words are marked as valid or not.
********************************************************************/
int getNoOfWords(void);

/********************************************************************
Function: saveWordListToFile()
Usage: bool ok = saveWordListToFile();
---------------------------------------------------------------------
Purpose: Used when the wordlist is saved to file. The  wordlist array
is stored in the wordlist file. Returns TRUE if every thing works
otherwise FALSE, if something goes wrong.
********************************************************************/
bool saveWordListToFile(void);

/********************************************************************
Function: freeList()
Usage: bool ok = freeList();
---------------------------------------------------------------------
Purpose: The memory allocated by wordlist array is released.
Returns TRUE if all allocated memory can be released, otherwise FALSE.
********************************************************************/
bool freeList(void);

/********************************************************************
Function: emptyList()
Usage: emptyList();
---------------------------------------------------------------------
Purpose: Removes all words from the list array.
********************************************************************/
void emptyList(void);

/********************************************************************
Function: addWordToList()
Usage: bool ok = addWordToList(aWord);
---------------------------------------------------------------------
Purpose: Adds the word to the end of the word list array. 
Returns TRUE if this is possible otherwise FALSE.
********************************************************************/
bool addWordToList(wordT aWord);

/********************************************************************
Function: cleanWord()
Usage: bool ok = cleanWord(aWord, lengthOfWord);
---------------------------------------------------------------------
Purpose: Removes non-letter characters from the word and makes it 
lower case.
Returns TRUE if cleaning is successful. Returns FALSE if e.g. removal 
of non-letter characers occur in the middle of the word. 
********************************************************************/
bool cleanWord(string aWord,int strLength);

/********************************************************************
Function: resetSelectedList(aWord)
Usage: resetSelectedList(aWord);
---------------------------------------------------------------------
Purpose: The count for the words in the list are set to number provided
as a parameter. Return TRUE if successful otherwise FALSE.
********************************************************************/
bool resetSelectedList(int iVal);

/********************************************************************
Function: getWord()
Usage: wordT* pWord = getWord(aString, pIndex);
---------------------------------------------------------------------
Purpose: Returns a pointer to a word in the list, such that the text
of the word matches string passed to the function. Also retrieves the 
index position in the list array through the pointer pIndex.
********************************************************************/
const wordT* getWord(string, int *);

/********************************************************************
Function: setWord()
Usage: bool ok = setWord(aWord, anArrayIndex);
---------------------------------------------------------------------
Purpose: Updates an existing word in the list array according to the 
word passed as a parameter, at the index position passed as the 
parameter anArrayIndex. Returns TRUE if possible to update the word in 
the list array, otherwise FALSE. 
********************************************************************/
bool setWord(wordT, int);
 

/* Added Functions */

bool addWordsToList(string text);
#endif // !_wordManager
