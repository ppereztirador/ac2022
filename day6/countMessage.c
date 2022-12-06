#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../common/common.h"
#define NUMCHARS 5000
#define GROUPSIZE 14

int findRepeats(char group[GROUPSIZE]) {
	int i, j;
	int repeats = 0;

	for (i=0; i<GROUPSIZE; i++) {
		for (j=i+1; j<GROUPSIZE; j++) {
			if (group[i]==group[j]) {
				repeats++;
			}
		}
	}

	return repeats;
}

int main(int argc, char* argv[]) {
	char fileName[1000];
	int i, j;
	FILE* fileHandler;

	char* signal;
	char tempGroup[GROUPSIZE];
	int numChars;

	if (argc<2) {
		printf("countMessage fileName\n");
	}
	else {
		/* Allocate */
		signal = (char*) calloc(NUMCHARS, sizeof(char));
		
		for (i=0; i<GROUPSIZE; i++) {
			/* This isn't necessary because there's acheck for the
			 * group size later, but still
			 */
			tempGroup[i] = ' ';
		}

		/* Process */
		strcpy(fileName, argv[1]);
		fileHandler = fopen(fileName, "r");
		fgets(signal, NUMCHARS, fileHandler);
		fclose(fileHandler);
		numChars = strlen(signal);

		j = 0;
		for (i=0; i<numChars; i++) {
			if (j==GROUPSIZE) j = 0;
			tempGroup[j] = signal[i];
			j++;

			if (i>=GROUPSIZE) {
				if (findRepeats(tempGroup)==0) {
					break;
				}
			}
		}

		printf("Last index: %d\n", i+1);

		/* Free */
		free(signal);
	}

	return 0;
}
