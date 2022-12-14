#ifndef FILETREE_H
#define FILETREE_H
	typedef struct fileNode fileNode;
	
	struct fileNode {
		char name[50];
		fileNode* parent;
		fileNode* child;
		int next;
		int size;
		int numNodes;
	};

	fileNode* createFileNodeList(int);
	void initFileNodeList(fileNode*, fileNode*);
	void freeFileNodeList(fileNode*);
	void printFile(fileNode*);
	void addChild(fileNode*, int, fileNode*, int);
	int updateFileSizes(fileNode*);
	fileNode* addNode(fileNode*, fileNode*);
	int findFile(fileNode*, char[]);
	int countNodes(fileNode*);
#endif
