#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

char** allocStringArray(int numStrings) {
	char** retArray;
	int i;

	retArray = (char**) calloc(numStrings, sizeof(char*));

	if (retArray==NULL) {
		printf("ERROR ALLOCATING STRING\n");;
	}
	else {
		for (i=0; i<numStrings; i++) {
			retArray[i] = (char*) calloc(50, sizeof(char));
			if (retArray[i]==NULL) {
				printf("ERROR ALLOCATING STRING\n");
				freeStringArray(retArray, numStrings);
				break;
			}
		}
	}
	
	return retArray;
}

void freeStringArray(char** sArray, int numStrings) {
	int i;

	for (i=0; i<numStrings; i++) {
		free(sArray[i]);
	}

	free(sArray);
}

int parseIntLine(char* line, int length, int* outBuffer) {
	int i, j = 0;
	int numInts = 0;
	char snippet[1000];

	for (i=0; i<=length; i++) {
		if (line[i]==' ' || line[i]=='\n' || i==length) {
			if (j!=0) {
				snippet[j] = '\0';
				outBuffer[numInts] = atoi(snippet);
				numInts++;
				j = 0;
			}
		}
		else {
			snippet[j] = line[i];
			j++;
		}
	}

	return numInts;
}

int parseFile(char* fileName, int outBuffer[MAX_FILE_LINES][MAX_FILE_NUMBERS],
	       int numInts[MAX_FILE_LINES]) {
	FILE* fileHandler;
	char currentLine[1000];
	int numRecords = 0;

	fileHandler = fopen(fileName, "r");

	if (fileHandler!=NULL) {
		while (fgets(currentLine, 1000, fileHandler) != NULL) {
			numInts[numRecords] = parseIntLine(currentLine,
					strlen(currentLine),
					outBuffer[numRecords]);
			numRecords++;
		}
		
	}
	else {
		numRecords = -1;
	}
	
	fclose(fileHandler);

	return numRecords;
}

int pushTop3(int top3[3], int num) {
	/* Silly implementation, just to get a top three */
	int pos = 3;
	
	if (num>top3[0]) {
		top3[2] = top3[1];
		top3[1] = top3[0];
		top3[0] = num;
		pos = 0;
	}
	else if (num>top3[1]) {
		top3[2] = top3[1];
		top3[1] = num;
		pos = 1;
	}
	else if (num>top3[2]) {
		top3[2] = num;
		pos = 2;
	}

	return pos;
}


int parseCharLine(char* line, int length, char** outBuffer) {
	int i, j = 0;
	int numChars = 0;
	char snippet[1000];

	for (i=0; i<=length; i++) {
		if (line[i]==' ' || line[i]=='\n' || i==length) {
			if (j!=0) {
				snippet[j] = '\0';
				strcpy(outBuffer[numChars], snippet);
				numChars++;
				j = 0;
			}
		}
		else {
			snippet[j] = line[i];
			j++;
		}
	}

	return numChars;
}

int parseCharFile(char* fileName, char** outBuffer[MAX_FILE_LINES],
	       int numChars[MAX_FILE_LINES]) {
	FILE* fileHandler;
	char currentLine[1000];
	int numRecords = 0;

	fileHandler = fopen(fileName, "r");

	if (fileHandler!=NULL) {
		while (fgets(currentLine, 1000, fileHandler) != NULL) {
			numChars[numRecords] = parseCharLine(currentLine,
					strlen(currentLine),
					outBuffer[numRecords]);
			numRecords++;
		}
		
	}
	else {
		numRecords = -1;
	}
	
	fclose(fileHandler);

	return numRecords;
}
