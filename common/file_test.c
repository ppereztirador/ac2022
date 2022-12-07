#include <stdio.h>
#include <string.h>
#include "fileTree.h"

int main() {
	fileNode* fn, * fn2;
	int i, t;

	fn = createFileNodeList(3);
	fn2 = createFileNodeList(5);
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
	
	for (i=0; i<3; i++) {
		printFile(&fn[i]);
	}

	t = updateFileSizes(fn, 3);
	
	for (i=0; i<3; i++) {
		printFile(&fn[i]);
	}

	printf("Total Size: %d\n", t);

	printf("**************\n");
	freeFileNodeList(fn, 3);
	return 0;
}
