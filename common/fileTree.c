#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileTree.h"

fileNode* createFileNodeList(int numNodes) {
	fileNode* retFile;
	int i;

	retFile = (fileNode*) calloc(numNodes, sizeof(fileNode));
	for (i=0; i<numNodes-1; i++) {
		retFile[i].next = 1;
	}
	retFile[numNodes-1].next = 0;

	return retFile;
}

void initFileNodeList(fileNode* fn, fileNode* parent) {
	int i;
	
	i = 0;
	do {
		fn[i].parent = parent;
		fn[i].size = 0;
		fn[i].child = NULL;
		fn[i].numNodes = 0;
		i ++;
	} while (fn[i-1].next==1);
}

int countNodes(fileNode* fn) {
	int i = 0;
	do {
		i ++;
	} while (fn[i-1].next==1);

	return i;
}

void initFileNodeParent(fileNode* fn, fileNode* parent) {
	int i;
	
	i = 0;
	do {
		fn[i].parent = parent;
		i ++;
	} while (fn[i-1].next==1);
}


void freeFileNodeList(fileNode* fn) {
	int i;

	i = 0;
	do {
		//printf("FREE %d\n", i);
		//printFile(&fn[i]);
		if (fn[i].child!=NULL) {
			//printf("**FREE %p, %d\n", fn[i].child, fn[i].numNodes);
			freeFileNodeList(fn[i].child);
		}
		i ++;
	} while (fn[i-1].next==1);

	free(fn);
}

void addChild(fileNode* fn, int nodeIdx, fileNode* child, int numNodes) {
	fn[nodeIdx].child = child;
	fn[nodeIdx].numNodes = numNodes;
	fn[nodeIdx].size = 0;

	initFileNodeParent(child, &fn[nodeIdx]);
}

int updateFileSizes(fileNode* fn) {
	int i;
	int totalSize = 0;

	i = 0;
	do {
		if (fn[i].child!=NULL) {
			fn[i].size = updateFileSizes(fn[i].child);
		}
		totalSize += fn[i].size;
		i ++;
	} while (fn[i-1].next==1);

	return totalSize;
}

fileNode* addNode(fileNode* fn, fileNode* newNode) {
	fileNode* retFn;
	int numNodes = countNodes(fn);

	retFn = (fileNode*) realloc(fn, (numNodes+1)*sizeof(fileNode));
	
	strcpy(retFn[numNodes].name, newNode->name);
	retFn[numNodes].parent = newNode->parent;
	retFn[numNodes].child = newNode->child;
	retFn[numNodes].size = newNode->size;
	retFn[numNodes].numNodes = newNode->numNodes;
	retFn[numNodes-1].next = 1;  retFn[numNodes].next = 0;

	return retFn;
}

void printFile(fileNode* fn) {
	printf("%s: %d\n***", fn->name, fn->size);
	printf("parent: %p, children [%d]: %p\n\n", fn->parent, fn->numNodes, fn->child);
}

int findFile(fileNode* fn, char name[]) {
	int retIdx = -1;
	int i;

	if (strcmp(name, "..")==0) {
		retIdx = -2;
	}
	else {
		i = 0;
		do {
			if (strcmp(name, fn[i].name)==0) {
				retIdx = i;
				break;
			}
			i ++;
		} while (fn[i-1].next==1);
	}

	return retIdx;
}
