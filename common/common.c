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

int parseIntLineToken(char* line, int length, int* outBuffer, char* tokens) {
	int i, j = 0;
	int numInts = 0;
	char snippet[1000];
	
	if (tokens==NULL) return parseIntLine(line, length, outBuffer);

	for (i=0; i<=length; i++) {
		if (strchr(tokens, line[i]) || i==length) {
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

int parseIntFileToken(char* fileName, int outBuffer[MAX_FILE_LINES]
						[MAX_FILE_NUMBERS],
	       int numInts[MAX_FILE_LINES], char* tokens) {
	FILE* fileHandler;
	char currentLine[1000];
	int numRecords = 0;

	fileHandler = fopen(fileName, "r");

	if (fileHandler!=NULL) {
		while (fgets(currentLine, 1000, fileHandler) != NULL) {
			numInts[numRecords] = parseIntLineToken(currentLine,
					strlen(currentLine),
					outBuffer[numRecords], tokens);
			numRecords++;
		}
		
	}
	else {
		numRecords = -1;
	}
	
	fclose(fileHandler);

	return numRecords;
}

int popChar(char* stack, int num, char* popVals) {
	int retVal, i;
	int lenMax = strlen(stack);
	
	retVal = 0;
	for (i=lenMax-num; i<lenMax; i++) {
		popVals[i-(lenMax-num)] = stack[i];
		stack[i] = '\0';
		retVal++;
	}
	popVals[num] = '\0';

	return retVal;
}

void pushChar(char* stack, char* pushVals) {
	strcat(stack, pushVals);
}

int parseCharLineSpaces(char* line, int length, char** outBuffer, int maxSpaces) {
	int i, j = 0;
	int numChars = 0;
	char snippet[1000];
	int numSpaces = 0;

	for (i=0; i<=length; i++) {
		//printf("[%d]:%c   ", i, line[i]);
		//printf("numSpaces: %d\n", numSpaces);
		if (line[i]==' ' || line[i]=='\n' || i==length) {
			if (j!=0) {
				snippet[j] = '\0';
				strcpy(outBuffer[numChars], snippet);
				numChars++;
				j = 0;
				numSpaces = 0;
				//printf("SAVE! %s\n", snippet);
			}
			else if (line[i]==' ') {
				numSpaces++;
				if (numSpaces==maxSpaces+1) {
					strcpy(outBuffer[numChars], "");
					numChars++;
					numSpaces = 0;
					//printf("SAVE! %s\n", "");
				}
			}
		}
		else {
			snippet[j] = line[i];
			j++;
		}
	}

	return numChars;
}

int parseCharFileSpaces(char* fileName, char** outBuffer[MAX_FILE_LINES],
	       int numChars[MAX_FILE_LINES], int maxSpaces) {
	FILE* fileHandler;
	char currentLine[1000];
	int numRecords = 0;

	fileHandler = fopen(fileName, "r");

	if (fileHandler!=NULL) {
		while (fgets(currentLine, 1000, fileHandler) != NULL) {
			numChars[numRecords] = parseCharLineSpaces(currentLine,
					strlen(currentLine),
					outBuffer[numRecords], maxSpaces);
			numRecords++;
		}
		
	}
	else {
		numRecords = -1;
	}
	
	fclose(fileHandler);

	return numRecords;
}
