#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../common/common.h"

int isVisible(char*** trees, int numRows, int numCols, int x, int y) {
	int i, j;
	int dirVisible, dirVal;
	
	dirVisible = 0;
	/* Search left */
	i = x;
	dirVal = 1;
	for (j=y-1; j>=0; j--) {
		if (trees[i][0][j]>=trees[x][0][y]) {
			dirVal = 0;
			break;
		}
	}
	dirVisible += dirVal;
	
	/* Search right */
	i = x;
	dirVal = 1;
	for (j=y+1; j<numCols; j++) {
		if (trees[i][0][j]>=trees[x][0][y]) {
			dirVal = 0;
			break;
		}
	}
	dirVisible += dirVal;

	/* Search up */
	j = y;
	dirVal = 1;
	for (i=x-1; i>=0; i--) {
		if (trees[i][0][j]>=trees[x][0][y]) {
			dirVal = 0;
			break;
		}
	}
	dirVisible += dirVal;

	/* Search down */
	j = y;
	dirVal = 1;
	for (i=x+1; i<numRows; i++) {
		if (trees[i][0][j]>=trees[x][0][y]) {
			dirVal = 0;
			break;
		}
	}
	dirVisible += dirVal;

	return dirVisible;
}

int main(int argc, char* argv[]) {
	char fileName[1000];
	int i, j;

	char** strList[MAX_FILE_LINES];
	int numStr[MAX_FILE_LINES];
	int numStrLines;
	
	int numRows, numCols;
	int forest[100][100];
	int totalScore;

	if (argc<2) {
		printf("countTrees fileName\n");
	}
	else {
		/* Allocate */
		for (i=0; i<MAX_FILE_LINES; i++) {
			strList[i] = allocStringArray(1);
		}

		/* Process */
		strcpy(fileName, argv[1]);
		numStrLines = parseCharFile(fileName, strList, numStr);
		numRows = numStrLines;
		numCols = strlen(strList[0][0]);

		totalScore = 0;
		for (i=0; i<numRows; i++) {
			for (j=0; j<numCols; j++) {
				//printf("%c ", strList[i][0][j]);
				if (isVisible(strList, numRows, numCols, i, j)) {
					totalScore ++;
				}
			}
			//printf("\n");
		}

		printf("Num visible trees: %d\n", totalScore);

		/* Free */
		for (i=0; i<MAX_FILE_LINES; i++) {
			freeStringArray(strList[i], 1);
		}

	}

	return 0;
}
