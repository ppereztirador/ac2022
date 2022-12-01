#ifndef COMMON_H
#define COMMON_H
	#define MAX_FILE_LINES 5000
	#define MAX_FILE_NUMBERS 50
	int parseIntLine(char*, int, int*);
	int parseFile(char*, int[MAX_FILE_LINES][MAX_FILE_NUMBERS], int[MAX_FILE_LINES]);
	int pushTop3(int[3], int);
#endif
