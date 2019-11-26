#include "gen.h"

void clearStdIn(void)
{
	int c;
	while ((c = getchar() != '\n') && c != EOF);

}

void pause(string str)
{
	printf("%s",str);
	clearStdIn();
}

bool closeFile(FILE** aFile)
{
	if (*aFile != NULL && !fclose(*aFile))
		*aFile = NULL;
	return (*aFile == NULL);
}

int getInt(string text)
{
	printf("%s", text);
	return getInteger();
}

string getString(string text)
{
	printf("%s", text);
	return getLine();
}
