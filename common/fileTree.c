#include <stdio.h>
#include <stdlib.h>
#include "fileTree.h"

fileNode* createFileNodeList(int numNodes) {
	fileNode* retFile;
	retFile = (fileNode*) calloc(numNodes, sizeof(fileNode));

	return retFile;
}

void initFileNodeList(fileNode* fn, int numNodes, fileNode* parent) {
	int i;
	
	for (i=0; i<numNodes; i++) {
		fn[i].parent = parent;
		fn[i].size = 0;
		fn[i].child = NULL;
		fn[i].numNodes = 0;
	}
}

void initFileNodeParent(fileNode* fn, int numNodes, fileNode* parent) {
	int i;
	
	for (i=0; i<numNodes; i++) {
		fn[i].parent = parent;
	}
}


void freeFileNodeList(fileNode* fn, int numNodes) {
	int i;
	for (i=0; i<numNodes; i++) {
		printf("FREE %d\n", i);
		printFile(&fn[i]);
		if (fn[i].child!=NULL) {
			printf("**FREE %p, %d\n", fn[i].child, fn[i].numNodes);
			freeFileNodeList(fn[i].child, fn[i].numNodes);
		}
	}

	free(fn);
}

void addChild(fileNode* fn, int nodeIdx, fileNode* child, int numNodes) {
	fn[nodeIdx].child = child;
	fn[nodeIdx].numNodes = numNodes;
	fn[nodeIdx].size = 0;

	initFileNodeParent(child, numNodes, &fn[nodeIdx]);
}

int updateFileSizes(fileNode* fn, int numNodes) {
	int i;
	int totalSize = 0;

	for (i=0; i<numNodes; i++) {
		if (fn[i].child!=NULL) {
			fn[i].size = updateFileSizes(fn[i].child, fn[i].numNodes);
		}
		totalSize += fn[i].size;
	}

	return totalSize;
}

void printFile(fileNode* fn) {
	printf("%s: %d\n***", fn->name, fn->size);
	printf("parent: %p, children [%d]: %p\n\n", fn->parent, fn->numNodes, fn->child);
}
