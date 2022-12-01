#include <stdio.h>
#include "common.h"
#include <string.h>

int main() {
	char testStr[] = "100\n";
	int intArray[100];
	int intCollection[MAX_FILE_LINES][MAX_FILE_NUMBERS];
	int numIntCollection[MAX_FILE_LINES];
	int numInts;

	char fileName[] = "numbers.txt";

	int i, j;

	numInts = parseIntLine(testStr, strlen(testStr), intArray);

	printf("%d\n", numInts);

	for(i=0; i<numInts; i++) {
		printf("%d: %d\n", i, intArray[i]);
	}

	printf("*****\n\n");
	
	numInts = parseFile(fileName, intCollection, numIntCollection);

	printf("%d\n", numInts);

	for (i=0; i<numInts; i++) {
		printf("%d) ", i);
		for (j=0; j<numIntCollection[i]; j++) {
			printf("%d ", intCollection[i][j]);
		}
		printf("[total: %d]\n", numIntCollection[i]);
	}

	return 0;
}
