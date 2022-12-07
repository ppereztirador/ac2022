#ifndef FILETREE_H
#define FILETREE_H
	typedef struct fileNode fileNode;
	
	struct fileNode {
		char name[50];
		fileNode* parent;
		fileNode* child;
		int size;
		int numNodes;
	};

	fileNode* createFileNodeList(int);
	void initFileNodeList(fileNode*, int, fileNode*);
	void freeFileNodeList(fileNode*, int);
	void printFile(fileNode*);
	void addChild(fileNode*, int, fileNode*, int);
	int updateFileSizes(fileNode*, int);
#endif
