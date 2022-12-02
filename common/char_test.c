#include <stdio.h>
#include "common.h"
#include <string.h>

int main() {
	char testStr[] = "A b C\n";
	char** charArray = allocStringArray(100);;
	char** charCollection[MAX_FILE_LINES];
	int numCharCollection[MAX_FILE_LINES];
	int numChars;

	char fileName[] = "letters.txt";

	int i, j;

	numChars = parseCharLine(testStr, strlen(testStr), charArray);

	printf("%d\n", numChars);

	for(i=0; i<numChars; i++) {
		printf("%d: %s\n", i, charArray[i]);
	}

	printf("*****\n\n");
	
	for(i=0; i<MAX_FILE_LINES; i++) {
		charCollection[i] = allocStringArray(10);
	}

	numChars = parseCharFile(fileName, charCollection, numCharCollection);

	printf("%d\n", numChars);

	for (i=0; i<numChars; i++) {
		printf("%d) ", i);
		for (j=0; j<numCharCollection[i]; j++) {
			printf("%s ", charCollection[i][j]);
		}
		printf("[total: %d]\n", numCharCollection[i]);
	}
	
	freeStringArray(charArray, 100);

	for(i=0; i<MAX_FILE_LINES; i++) {
		freeStringArray(charCollection[i], 10);
    }

	return 0;
}
