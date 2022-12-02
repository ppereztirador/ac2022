#include <stdio.h>
#include <string.h>
#include "../common/common.h"

/*Bias: player=ascii(X), opponent=ascii(A)*/
#define PLAYERBIAS 88
#define OPPONENTBIAS 65

int scoreTable[3][3] = {{3, 6, 0},
						{0, 3, 6},
						{6, 0, 3}};

char shapeTable[3][3] = {{'Z', 'X', 'Y'},
						{'X', 'Y', 'Z'},
						{'Y', 'Z', 'X'}};

int choiceTable[3] = {1, 2, 3};

int calculateScore(char* player, char* opponent) {
	int playerIdx, opponentIdx;

	playerIdx = player[0] - PLAYERBIAS;
	opponentIdx =  opponent[0] - OPPONENTBIAS;

	return choiceTable[playerIdx] + scoreTable[opponentIdx][playerIdx];
}

void calculateShape(char* outcome, char* opponent, char* player) {
	int outcomeIdx, opponentIdx;

	outcomeIdx = outcome[0] - PLAYERBIAS;
	opponentIdx =  opponent[0] - OPPONENTBIAS;
	
	player[0] = shapeTable[opponentIdx][outcomeIdx];
}

int main(int argc, char* argv[]) {
	char fileName[1000];
	int i;
	
	char** strList[MAX_FILE_LINES];
	char player[2] = "\0\0";
	int numStr[MAX_FILE_LINES];
	int numStrLines;
	int totalScore;

	if (argc<2) {
		printf("calculateScoreShape fileName\n");
	}   
	else {
		/* Allocate */
		for (i=0; i<MAX_FILE_LINES; i++) {
			strList[i] = allocStringArray(2);
		}

		/* Process */
		strcpy(fileName, argv[1]);
		numStrLines = parseCharFile(fileName, strList, numStr);

		totalScore = 0;
		for (i=0; i<numStrLines; i++) {
			calculateShape(strList[i][1], strList[i][0], player);
			totalScore += calculateScore(player, strList[i][0]);
		}

		printf("Total score: %d\n", totalScore);

		/* Free */
		for (i=0; i<MAX_FILE_LINES; i++) {
			freeStringArray(strList[i], 2);
		}
	}

	return 0;
}
