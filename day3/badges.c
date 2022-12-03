#include <stdio.h>
#include <string.h>
#include "../common/common.h"

#define ELFGROUP 3

char findBadge(char** sGroup, int groupSize) {
	int i, j, commonStrings;
	char badge;

	for (i=0; i<strlen(sGroup[0]); i++) {
		commonStrings = 0;
		for (j=1; j<groupSize; j++) {
			if (strchr(sGroup[j], sGroup[0][i])!=NULL) {
				commonStrings++;
			}
		}

		if (commonStrings==groupSize-1) {
			badge = sGroup[0][i];
		}
	}

	return badge;
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
	int i, j;

	char** strList[MAX_FILE_LINES];
	int numStr[MAX_FILE_LINES];
	int numStrLines;
        int totalScore;
	char** elfGroup;
	char badge;

	if (argc<2) {
		printf("badges fileName\n");
	}
	else {
		/* Allocate */
		for (i=0; i<MAX_FILE_LINES; i++) {
			strList[i] = allocStringArray(2);
		}

		elfGroup =  allocStringArray(ELFGROUP);

		/* Process */
		strcpy(fileName, argv[1]);
		numStrLines = parseCharFile(fileName, strList, numStr);

		j = 0;
		for (i=0; i<numStrLines; i++) {
			if (j==ELFGROUP) {
				j = 0;

				badge = findBadge(elfGroup, ELFGROUP);
				totalScore += charPriority(badge);
			}

			strcpy(elfGroup[j], strList[i][0]);
			j++;
		}

		/* If there's one last group */
		if (j==ELFGROUP) {
			badge = findBadge(elfGroup, ELFGROUP);
			totalScore += charPriority(badge);
		}

		printf("Total score: %d\n", totalScore);

		/* Free */
		for (i=0; i<MAX_FILE_LINES; i++) {
			freeStringArray(strList[i], 2);
		}

		freeStringArray(elfGroup, ELFGROUP);
	}

	return 0;
}
