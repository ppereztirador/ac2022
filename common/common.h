#ifndef COMMON_H
#define COMMON_H
	#define MAX_FILE_LINES 5000
	#define MAX_FILE_NUMBERS 50

	char** allocStringArray(int);
	void freeStringArray(char**, int);

	int parseIntLine(char*, int, int*);
	int parseFile(char*, int[MAX_FILE_LINES][MAX_FILE_NUMBERS], int[MAX_FILE_LINES]);
	int pushTop3(int[3], int);

	int parseCharLine(char* line, int length, char** outBuffer);
	int parseCharFile(char*, char**[MAX_FILE_LINES], int[MAX_FILE_LINES]);
#endif
