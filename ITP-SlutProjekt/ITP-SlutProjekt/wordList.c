#include <stdio.h>
#include "gen.h"
#include "wordManager.h"

// Necessary defines for error messages
#define errno   (*_errno())
#define _doserrno   (*__doserrno())
#define _sys_errlist (__sys_errlist())
#define _sys_nerr (*__sys_nerr())

#define MEEP "F:/Gallery/meep.txt"
#define MINO "F:/Gallery/mino.txt"

int printWordMenu(void);
void doWordMenu(int);
void printList(void);
bool readFileWords(string);
void readWord(void);
wordT* searchWord(string);
void changeWord(wordT*);
void removeWord(wordT*);
void removeAllWords(void);
bool closeWordList(void);

// Added functions

//

int main()
{
	system("chcp 1252");
	int wordChoice = 0;
	errno_t err = -1;

	//Create the listinfo
	listT *pList = (listT*)malloc(sizeof(listT));
	_set_errno(0);
	if (pList != NULL && !(err = strcpy_s(pList->listName, MAXNAMELENGTH, WORDLISTNAME)))
	{
		pList->listSize = MAXNOOFWORDS;
		pList->noOfWords = 0;
		pList->noOfValid = 0;
	}
	else if (err < 0)
		printf("\nMinnesallokering för listinformation misslyckades");
	else // err > 0
		perror("\nKopieringsfel"); //Prints the error message delivered by err, after the passed text

	//Create the list and run the menu
	if (!(err = wordManager(pList)))
	{
		do {
			doWordMenu(wordChoice = printWordMenu());
		} while (wordChoice);
	}
	else if (err < 0)
		pause("\nProgammet kunde inte starta, p.g.a. ogiltig listinformation.");
	else   
		perror("\nProgammet kunde inte starta, p.g.a. systemfel"); 
		 
	return 0;
}


int printWordMenu(void)
{
	system("cls");
	printf("\n\t%s\n\n\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n\t%s",
		"Programmet - Ordlista",
		"1.\tSkriv ut ordlista",
		"2.\tLäs in ord till ordlistan från en texfil",
		"3.\tLägg till ord manuellt",
		"4.\tSök i ordlistan",
		"5.\tUppdatera sökt ord", 
		"6.\tTa bort sökt ord", 
		"7.\tTöm ordlistan",
		"8.\tNollställ alla ords frekvens",
		"9.\tSpara till fil",
		"0.\tAvsluta programmet");  
	return getInt("\n\n\tDitt val:");
}

void doWordMenu(int choice)
{
	static wordT* pWord = NULL;
	system("cls");
	switch (choice)
	{
	case 0:
		closeWordList();
		printf("\n\tProgrammet avslutas!");
		break;
	case 1:
		printList();
		break;
	case 2:
		readFileWords(MEEP);
		break;
	case 3:
		readWord();
		break;
	case 4:
		searchWord("Söker ord i listan\n");
		break;
	case 5:
		changeWord(searchWord("Sök ett ord att ändra på\n"));
		break;
	case 6:
		removeWord(searchWord("Sök ett ord att ta bort\n"));
		break;
	case 7:
		break;
	case 8:
		if (!resetSelectedList(0))
			printf("\n\tKunde inte nollställa orden i listan!");
		else
			printf("\n\tAlla ord har nollställts!");
		break;
	case 9:
		break;
	default:
		printf("\nFelaktig inmatning, försök igen!");
			break;
	}
	pause("\n\n\tTryck tangent!");
}


void printList(void)
{
	wordT* aList = getList();
	if (aList != NULL)
	{
		int num = getNoOfWords();
		printf("\n\n\tListan av ord med deras frevens:\n");
		for (int i = 0; i < num; i++)
		{
			if (i % 8 == 0) {
				printf("\n");
			}
			if (aList[i].valid) {
				const int space = MAXWORDLENGTH;
				string s = malloc((space-1) * sizeof(char));
				if (aList[i].count > 9) {
					s = concat("| ", integerToString(aList[i].count));
					s = concat(s, "|");
					s = concat(s, aList[i].text);
				}
				else {
					s = concat("| ", integerToString(aList[i].count));
					s = concat(s, " |");
					s = concat(s, aList[i].text);
				}
				
				for (int j = stringLength(aList[i].text); j < space; j++) {
					s = concat(s, " ");
				}
				s[space] = '\0';
				printf("%s", s);
			}
		}
	}
	else
		printf("\n\tListan kunde inte skrivas ut!");
}

bool readFileWords(string aFileName)
{
	printf("\n\tLäser in ord från valfri text till ordlistan");

	/* Open File Stream */
	FILE* file = NULL;
	errno_t err = fopen_s(&file, aFileName, "r");
	if (err != 0) { printf("error"); }

	string s = NULL; // String to store each line
	/* No need to write != NULL */
	/* the while loop checks for that */
	while (s = readLine(file)) {
		addWordsToList(s);
	}
	return TRUE;
}

void readWord(void)
{
	// Read in Word
	// Pass to addWordToList function
	string s = getString("\n\tSkriv in en/flera ord eller mening som skall läggas till i ordlistan:\n\t");
	addWordsToList(s);
	printList();
}

wordT* searchWord(string msg)
{
	printf("\n\t");
	/* Get the word */
	string s = getString(msg);
	int *pIndex = getBlock(sizeof(int));
	wordT* pWord = getWord(s, pIndex);
	/* If exists or not */
	if (pWord != NULL) printf("\t%s\t\t%d", pWord->text, pWord->count);
	else {
		printf("\nInget sådant ord finns med i listan");
		return NULL;
	}
	return pWord;
}

void changeWord(wordT* pWord)
{
	if (pWord != NULL) {
		printf("\n\t");
		string s = getString("\n\n\tUppdatera ordet med:\n\t");
		strcpy_s(pWord->text, MAXWORDLENGTH, s);
	}
}

void removeWord(wordT* pWord)
{
	if(pWord != NULL)
		pWord->valid = FALSE;
}

void removeAllWords(void)
{

}

/********************************************************************
Function: closeWordList()
Usage: bool ok = closeWordList();
---------------------------------------------------------------------
Purpose: Used when the application is terminated by user.
Stores the wordlist array to the wordlist file.
The memory allocated by wordlist array is released.
Returns TRUE if every thing works otherwise FALSE.
********************************************************************/
bool closeWordList(void)
{
	//Save the wordlis to file
	//...
	//Release allocated memory
	if (freeList())
	{
		printf("\n\tMinne har frigjorts!");
		return TRUE;
	};
	return FALSE;
}