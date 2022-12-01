#include <stdio.h>
#include <string.h>
#include "../common/common.h"

int main(int argc, char* argv[]) {
	char fileName[1000];
	int i, j, k;

	int numIntLines;
	int numInt[MAX_FILE_LINES];
	int intList[MAX_FILE_LINES][MAX_FILE_NUMBERS];

	int currentElfTotal;
	int currentElf;

	int topFood[3];

	if (argc<2) {
		printf("countFood fileName\n");
	}
	else {
		strcpy(fileName, argv[1]);
		numIntLines = parseFile(fileName, intList, numInt);

		for (i=0; i<=numIntLines; i++) {
			if (numInt[i]==0 || i==numIntLines) {
				/* Empty line or last elf*/
				pushTop3(topFood, currentElfTotal);
				currentElf++;
				currentElfTotal = 0;
			} else {
				currentElfTotal += intList[i][0];
			}
		}

		printf("Top 1: %d\n", topFood[0]);
		printf("Top 2: %d\n", topFood[1]);
		printf("Top 3: %d\n", topFood[2]);
		printf("Total: %d\n", topFood[0]+topFood[1]+topFood[2]);
	}

	return 0;
}
