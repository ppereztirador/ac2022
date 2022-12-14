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
	fnEmpty = createFileNodeList(1);

	strcpy(fn3.name, "NEW");
	fn3.parent = NULL;
	fn3.child = NULL;
	fn3.numNodes = 0;
	fn3.size = 123;

	initFileNodeList(fn, NULL);
	initFileNodeList(fn2, NULL);

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
	fn = addNode(fn, &fn3);
	printf("**After adding: %p\n", fn);

	for (i=0; i<4; i++) {
		printFile(&fn[i]);
	}

	printf("Before adding to empty list: %p, %d\n", fnEmpty, countNodes(fnEmpty));
	fnEmpty = addNode(fnEmpty, &fn3);
	printf("empty list\n");
	printFile(&fnEmpty[0]);
	printFile(&fnEmpty[1]);
	printf("********\n");

	t = updateFileSizes(fn);
	
	for (i=0; i<4; i++) {
		printFile(&fn[i]);
	}

	printf("Total Size: %d\n", t);

	/* Find files */
	i = findFile(fn, findName);
	printf("Found file %s at position %i\n", findName, i);

	printf("**************\n");
	freeFileNodeList(fn);
	freeFileNodeList(fnEmpty);
	return 0;
}
