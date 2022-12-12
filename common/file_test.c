#include <stdio.h>
#include <string.h>
#include "fileTree.h"

int main() {
	fileNode* fn, * fn2, * fnEmpty;
	fileNode fn3;
	int i, t;
	char findName[] = "b";

	fn = createFileNodeList(3);
	fn2 = createFileNodeList(5);
	fnEmpty = createFileNodeList(0);

	strcpy(fn3.name, "NEW");
	fn3.parent = NULL;
	fn3.child = NULL;
	fn3.numNodes = 0;
	fn3.size = 123;

	initFileNodeList(fn, 3, NULL);
	initFileNodeList(fn2, 5, NULL);

	strcpy(fn[0].name, "a");
		fn[0].size = 1;
	strcpy(fn[1].name, "b");
	strcpy(fn[2].name, "c");
		fn[2].size = 1;

	strcpy(fn2[0].name, "aa");
		fn2[0].size = 1;
	strcpy(fn2[1].name, "bb");
		fn2[1].size = 1;
	strcpy(fn2[2].name, "cc");
		fn2[2].size = 1;
	strcpy(fn2[3].name, "dd");
		fn2[3].size = 1;
	strcpy(fn2[4].name, "ee");
		fn2[4].size = 1;

	addChild(fn, 1, fn2, 5);
	printf("**Before adding: %p\n", fn);
	fn = addNode(fn, 3, &fn3);
	printf("**After adding: %p\n", fn);

	fnEmpty = addNode(fnEmpty, 0, &fn3);
	
	for (i=0; i<4; i++) {
		printFile(&fn[i]);
	}

	printf("empty list\n");
	printFile(&fnEmpty[0]);
	printf("********\n");

	t = updateFileSizes(fn, 4);
	
	for (i=0; i<4; i++) {
		printFile(&fn[i]);
	}

	printf("Total Size: %d\n", t);

	/* Find files */
	i = findFile(fn, 4, findName);
	printf("Found file %s at position %i\n", findName, i);

	printf("**************\n");
	freeFileNodeList(fn, 4);
	freeFileNodeList(fnEmpty, 1);
	return 0;
}
