#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../common/common.h"
#define NUMCHARS 5000

int findRepeats(char group[4]) {
	int i, j;
	int repeats = 0;

	for (i=0; i<4; i++) {
		for (j=i+1; j<4; j++) {
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
	char tempGroup[4] = "    ";
	int numChars;

	if (argc<2) {
		printf("countPacket fileName\n");
	}
	else {
		/* Allocate */
		signal = (char*) calloc(NUMCHARS, sizeof(char));

		/* Process */
		strcpy(fileName, argv[1]);
		fileHandler = fopen(fileName, "r");
		fgets(signal, NUMCHARS, fileHandler);
		fclose(fileHandler);
		numChars = strlen(signal);

		j = 0;
		for (i=0; i<numChars; i++) {
			if (j==4) j = 0;
			tempGroup[j] = signal[i];
			j++;

			if (i>3) {
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
