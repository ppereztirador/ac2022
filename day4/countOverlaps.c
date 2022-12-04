#include <stdio.h>
#include <string.h>
#include "../common/common.h"

int isOverlap(int* ranges) {
	int retVal = 0;
	//printf("%d-%d, %d-%d\n", ranges[0],ranges[1],ranges[2],ranges[3]);
	/* Range 2 overlaps range 1 */
	if (ranges[1]>=ranges[2] && ranges[0]<=ranges[2]) {
		//printf("1 TRUE\n");
		retVal = 1;
	}

	/* Range 1 overlaps range 2 */
	if (ranges[3]>=ranges[0] && ranges[2]<=ranges[1]) {
		//printf("2 TRUE\n");
		retVal = 1;
	}

	return retVal;
}


int main(int argc, char* argv[]) {
	char fileName[1000];
	int i;
	char tokens[] = " \n-,";

	int numIntLines;
	int numInt[MAX_FILE_LINES];
	int intList[MAX_FILE_LINES][MAX_FILE_NUMBERS];

	int numOverlaps;

	if (argc<2) {
		printf("countOverlaps fileName\n");
	}
	else {
		strcpy(fileName, argv[1]);
		numIntLines = parseIntFileToken(fileName, intList, numInt, tokens);

		for (i=0; i<numIntLines; i++) {
			numOverlaps += isOverlap(intList[i]);
		}

		printf("Overlaps: %d\n", numOverlaps);
	}

	return 0;
}
