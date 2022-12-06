#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../common/common.h"

void readCrates(char** rawStrings[], int numLines, int numCols, char** crateStacks) {
	int i, j;

	for (i=numLines-1; i>=0; i--) {
		for (j=0; j<numCols; j++) {
			if (rawStrings[i][j][0]=='[') {
				crateStacks[j][numLines-i-1] = rawStrings[i][j][1];
			}
			else {
				crateStacks[j][numLines-i-1]='\0';
			}
		}
	}
}

int main(int argc, char* argv[]) {
	char fileName[1000];
	int i, j;

	char** strList[MAX_FILE_LINES];
	char** crateList;
	char** temp;
	int numStr[MAX_FILE_LINES];
	int numStrLines;
	int numCrateLines;
	int numCols;
	int totalScore;
	int stack1, stack2, numPop;

	if (argc<2) {
		printf("crates9001 fileName\n");
	}
	else {
		/* Allocate */
		for (i=0; i<MAX_FILE_LINES; i++) {
			strList[i] = allocStringArray(15);
		}
		temp = allocStringArray(1);

		/* Process */
		strcpy(fileName, argv[1]);
		numStrLines = parseCharFileSpaces(fileName, strList, numStr, 3);

		for (numCrateLines=0; numCrateLines<numStrLines; numCrateLines++) {
			if (numStr[numCrateLines]==0) break;
		}
		numCols = numStr[numCrateLines-1];

		crateList = allocStringArray(numCols);
		readCrates(strList, numCrateLines-1, numCols, crateList);

		/*
		for (i=0; i<numCols; i++) {
			printf("%d:: %s\n", i, crateList[i]);
		}
		*/

		for (i=numCrateLines+1; i<numStrLines; i++) {
			numPop = atoi(strList[i][1]);
			stack1 = atoi(strList[i][3])-1;
			stack2 = atoi(strList[i][5])-1;
			popChar(crateList[stack1], numPop, temp[0]);
			pushChar(crateList[stack2], temp[0]);
		}
		/*
		for (i=0; i<numCols; i++) {
			printf("%d:: %s\n", i, crateList[i]);
		}
		*/

		printf("Last elements: ");
		for (i=0; i<numCols; i++) {
			j = strlen(crateList[i])-1;
			printf("%c", crateList[i][j]);
		}
		printf("\n");

		/* Free */
		for (i=0; i<MAX_FILE_LINES; i++) {
			freeStringArray(strList[i], 2);
		}

		freeStringArray(crateList, numCols);
		freeStringArray(temp, 1);
	}

	return 0;
}
