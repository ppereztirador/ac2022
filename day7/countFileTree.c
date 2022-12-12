#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../common/common.h"
#include "../common/fileTree.h"
#define NUMCHARS 5000
#define GROUPSIZE 14

int sortCommand(char** command) {
	int commandType;

	if (strcmp(command[0], "$")) {
		if (strcmp(command[1], "cd")) {
			commandType = 1;
		}
		if (strcmp(command[1], "ls")) {
			commandType = 2;
		}
	}
	else if (strcmp(command[0], "dir")) {
		commandType = 3;
	}
	else {
		commandType = 4;
	}

	return commandType;
}

fileNode* executeCommand(char** command, fileNode* currentDir, int* numNodes) {
	int i;
	fileNode* retVal = NULL;
	char dirName[50];
	int commandType = sortCommand(command);
	fileNode tempNode;

	switch (commandType) {
		case 1:
			strcpy(dirName, command[2]);
			i = findFile(currentDir, *(numNodes), dirName);
			if (i==-2) {
				retVal = currentDir[0].parent;
			}
			break;
		case 2:
			retVal = NULL;
			break;
		case 3:
			/* Directory */
			strcpy(tempNode.name, command[1]);
			tempNode.size = 0;
			tempNode.numNodes = 0;
			tempNode.child = NULL;
			/* Leave parent to later init */

			retVal = addNode(currentDir, *(numNodes), &tempNode);
			break;
		case 4:
			/* File with size */
			strcpy(tempNode.name, command[1]);
			tempNode.size = atoi(command[0]);
			tempNode.numNodes = 0;
			tempNode.child = NULL;
			/* Leave parent to later init */
			
			retVal = addNode(currentDir, *(numNodes), &tempNode);
			break;
		case default:
			/* Shouldn't be reached with contest commands */
			printf("COMMAND ERROR\n");
			break;
	}

	return retVal;
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
