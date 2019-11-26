#include "wordManager.h"

//Remember to free these variables when program ends
static listT *wlInfo = NULL;//Holds info about the wordlist
static wordT *wl = NULL;	//Pointer to an array for the wordlist items, elements of type wordT
static wordT *cwl = NULL;	//A copy of wl only for reading, the user cannot change the original wl

/********************************************************************
Function: isInWordList()
Usage: int ok = isInWordList(aWordString, &wordIndex);
---------------------------------------------------------------------
Purpose: Checks if a given string (aWordString)is within the list 
array. If so returns TRUE, otherwise FALSE. Sets the wordindex to the 
index in the list array of the searched word, if found, otherwise the 
index is set to -1. The index is accessible through the pointer 
wordIndex.
********************************************************************/
static bool isInWordList(string, int *);

/********************************************************************
Function: getCountOfValid()
Usage: int count = getCountOfValid();
---------------------------------------------------------------------
Purpose: Counts and returns the number of valid words in the current 
list.
********************************************************************/
static int getCountOfValid(void); 

errno_t wordManager(listT* pList)
{
	errno_t err = -1;
	if (pList != NULL)
		wlInfo = pList;
	else
		return err;

	//Check if list-info is ok
	if (wlInfo->listName != NULL && stringLength(wlInfo->listName) > 0 && wlInfo->listSize > 0)
	{
		FILE *wordFile = NULL;
		_set_errno(0);
		//check if wordlist file exists, if not create it
		if ((err = _access_s(wlInfo->listName, 0)) == ENOENT)
		{
			_set_errno(0);
			//Create the file and close it 
			if (!(err = fopen_s(&wordFile, wlInfo->listName, "w")))
			{
				if ((wordFile != NULL) && !fclose(wordFile))
					wordFile = NULL;
			}
			else
				return err;
		}
		else if(err)
			return err;

		//Create an array for holding the words from the wordlist file
		wl = (wordT*)malloc(sizeof(wordT) * wlInfo->listSize);

		_set_errno(0);
		//If wordlist exists check if the file can be opened for reading
		if (wl != NULL && !(err = fopen_s(&wordFile, wlInfo->listName, "r")))
		{
//First alternative
/*			string line = readLine(wordFile);
			int i = 0;
			while (line != NULL)
			{
				strcpy_s(wl[i].text, MAXWORDLENGTH, subString(line, 0, findChar(' ', line, 0) - 1));
				wl[i].count = stringToInteger(subString(line, findChar(' ', line, 0), stringLength(line) - 1));
				wl[i++].valid = TRUE;
				free(line);
				line = readLine(wordFile);
			} */
///Second alternative		
/*			string line = readLine(wordFile);
			int i = 0;
			while (line != NULL)
			{
				if (sscanf_s(line, "%s%d", wl[i].text, (unsigned)_countof(wl[i].text), &wl[i].count) == 2)
					wl[i++].valid = TRUE;
				free(line);
				line = readLine(wordFile);
			}*/
////Third alternative
			int i = 0;
			while (fscanf_s(wordFile, "%s%d", wl[i].text, (unsigned)_countof(wl[i].text), &wl[i].count) != EOF)
				wl[i++].valid = TRUE; 

			wlInfo->noOfWords = i;
			if ((wordFile != NULL) && !fclose(wordFile))
				wordFile = NULL;
			wlInfo->noOfValid = getCountOfValid();
		}
		else
			return err;
	}
	return err;
}	

const wordT* getList(void)
{
	if (cwl != NULL)
		free(cwl);
	// wordT *cwl = ... Instead use a static array, otherwhise you force the user to free it  
	cwl = (wordT*)malloc(sizeof(wordT) * wlInfo->noOfWords); //= wl; Does not do it
	for (int i = 0; i < wlInfo->noOfWords; i++)
		cwl[i] = wl[i];
	return cwl; //since cwl is a copy you cannot change the original list in wl
}

int getNoOfWords(void)
{
	return wlInfo->noOfWords;
}

bool saveWordListToFile(void)
{

}

bool freeList(void)
{
	if (wl != NULL)
	{
		//Release memory of wordlist array
		free(wl);
		wl = NULL;
		if (wlInfo != NULL)
		{
			//Release memory of list information
			free(wlInfo);
			wlInfo = NULL;
			return TRUE;
		}
		if (cwl != NULL)
		{
			free(cwl);
			cwl = NULL;
		}
	}
	return FALSE;
}

void emptyList(void)
{

}

static bool isInWordList(string aWord,int *pIndex)
{
	/* Loop through all word and compare */
	for (int i = 0; i < wlInfo->noOfWords; i++) {
		if (stringEqual(aWord, wl[i].text)) {
			*pIndex = i; // Index of equal word
			return TRUE;
		}
	}
	return FALSE;
}

static int getCountOfValid(void)
{
	int count = 0;
	for (int i = 0; i < wlInfo->noOfWords; i++)
	{
		if (wl[i].valid)
			count++;
	}
	return count;
}

bool addWordToList(wordT aWord)
{
	wl[(wlInfo->noOfWords++)] = aWord;
}

/* --Added-- */
bool addWordsToList(string text) {
	int length = stringLength(text); // Get length of string
	const char c[2] = " "; // Separator 
	string token, tokenTemp; // Main token to hold info, second token to hold info between function calls
	token = strtok_s(text, c, &tokenTemp); // Get first substring
	while (token != NULL) {
		/* Removing leading and trailing characters */
		/* Only allows alphanumeric characters */
		if (cleanWord(token, stringLength(token))) {		
			int *index = getBlock(sizeof(int)); /* Variable to hold index of word if it exists */
			wordT *curWord = getWord(token, index); /* Get word from list */
			if (curWord != NULL) {
				/* If word exists */
				/* Change values and Update it */
				curWord->count++;
				curWord->valid = TRUE;
				if (!setWord(*curWord, index))
					printf("\tWord could not be set");
			}
			else {
				/* If no word exists */
				/* Creat one and add it */
				wordT aWord = { "" , 1, TRUE };
				strcpy_s(aWord.text, MAXWORDLENGTH, token);
				addWordToList(aWord);
			}
		}
		else {
			//printf("\n\tInvalid word detected");
		}

		token = strtok_s(NULL, c, &tokenTemp);
	}
	return TRUE;
}

bool cleanWord(string pStr, int strLength)
{
	string aStr = copyString(pStr);
	char *back;
	while (!isalnum((unsigned char)*aStr)) aStr++; // Remove all leading non-alphanumeric characters
	if (*aStr == 0) return FALSE; // Is there nothing left?

	/* Current Position plus the rest of the length */
	/* to reach the back in order to remove trailing characters*/
	back = aStr + stringLength(aStr) - 1; 
	while (back > aStr && !isalnum((unsigned char)*back)) back--;
	
	/* back[0] is where the word ends */
	/* so on the next index (back[1])*/
	/* end the string with \0 */
	back[1] = '\0';

	/* Check if anything random characters are left*/
	/* if so then return FAlSE cause... uppgiften */
	for (int i = 0; i < stringLength(aStr); i++)
		if (!isalnum((unsigned char)aStr[i]))
			return FALSE;

	/* Modify the passed string */
	strcpy_s(pStr, (stringLength(aStr) +1)*sizeof(char), convertToLowerCase(aStr));
	return TRUE;
}

bool resetSelectedList(int iVal)
{
	if ((wl != NULL) && (wlInfo->noOfWords < wlInfo->listSize))
	{
		for (int i = 0; i < wlInfo->noOfWords; i++)
			wl[i].count = iVal;
		return TRUE;
	}
	return FALSE;
}

const wordT* getWord(string aStr, int *pIndex)
{
	/* If in word list then return the word */
	if (isInWordList(aStr, pIndex)) 
		return &wl[*pIndex];
	return NULL;
}

bool setWord(wordT aWord, int index)
{
	/* Check if the word exists then make change */
	if (isInWordList(aWord.text, &index) != NULL) {
		wl[index] = aWord;
		return TRUE;
	}
	else return FALSE;
}

