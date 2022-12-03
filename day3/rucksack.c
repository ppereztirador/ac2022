#include <stdio.h>
#include <string.h>
#include "../common/common.h"

void divideRucksack(char* rucksack, char* comp1, char* comp2) {
	int i;

	/* 1st half */
	for (i=0; i<strlen(rucksack)/2; i++) {
		comp1[i] = rucksack[i];
	}

	comp1[strlen(rucksack)/2] = '\0';

	/* 2nd half */
	for (i=(strlen(rucksack)/2); i<strlen(rucksack); i++) {
		comp2[i-(strlen(rucksack)/2)] = rucksack[i];
	}

	comp2[strlen(rucksack)/2] = '\0';
}

int charPriority(char c) {
	int retVal = 0;
	
	if (c>='a' && c<='z') {
		retVal = c - 'a' + 1;
	}
	else if (c>='A' && c<='Z') {
		retVal = c - 'A' + 27;
	}

	return retVal;
}

int main(int argc, char* argv[]) {
	char fileName[1000];
	int i;

	char** strList[MAX_FILE_LINES];
	int numStr[MAX_FILE_LINES];
	int numStrLines;
        int totalScore;
	char** rucksack;
	char* commonChar;

	if (argc<2) {
		printf("rucksack fileName\n");
	}
	else {
		/* Allocate */
		for (i=0; i<MAX_FILE_LINES; i++) {
			strList[i] = allocStringArray(2);
		}

		rucksack =  allocStringArray(2);

		/* Process */
		strcpy(fileName, argv[1]);
		numStrLines = parseCharFile(fileName, strList, numStr);

		for (i=0; i<numStrLines; i++) {
			divideRucksack(strList[i][0], rucksack[0], rucksack[1]);

			commonChar = strpbrk(rucksack[0], rucksack[1]);
			totalScore += charPriority(*commonChar);
		}

		printf("Total score: %d\n", totalScore);

		/* Free */
		for (i=0; i<MAX_FILE_LINES; i++) {
			freeStringArray(strList[i], 2);
		}

		freeStringArray(rucksack, 2);
	}

	return 0;
}
