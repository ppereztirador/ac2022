#include <stdio.h>
#include <string.h>
#include "../common/common.h"

int main(int argc, char* argv[]) {
	char fileName[1000];
	int i, j, k;

	int numIntLines;
	int numInt[MAX_FILE_LINES];
	int intList[MAX_FILE_LINES][MAX_FILE_NUMBERS];

	int currentElfTotal, bestElfTotal;
	int currentElf, bestElf;

	if (argc<2) {
		printf("countFood fileName\n");
	}
	else {
		strcpy(fileName, argv[1]);
		numIntLines = parseFile(fileName, intList, numInt);

/*
		for (i=0; i<numIntLines; i++) {
	                printf("%d) ", i);
        	        for (j=0; j<numInt[i]; j++) {
                	        printf("%d ", intList[i][j]);
                	}
               		 printf("[total: %d]\n", numInt[i]);
        	}
*/

		currentElf = 1;
		bestElf = 1;
		currentElfTotal = 0;
		bestElfTotal = 0;
		for (i=0; i<=numIntLines; i++) {
			if (numInt[i]==0 || i==numIntLines) {
				/* Empty line or last elf*/
				if (currentElfTotal>bestElfTotal) {
					bestElf = currentElf;
					bestElfTotal = currentElfTotal;
				}

				currentElf++;
				currentElfTotal = 0;
			} else {
				currentElfTotal += intList[i][0];
			}
		}

		printf("Elf number %d: %d\n", bestElf, bestElfTotal);
	}

	return 0;
}
