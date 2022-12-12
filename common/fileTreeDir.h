#ifndef FILETREE_H
#define FILETREE_H
	typedef struct fileNode fileNode;
	typedef struct fileDir fileDir;
	
	struct fileNode {
		char name[50];
		fileDir* parent;
		fileDir* child;
		int size;
	};

	struct fileDir {
		fileNode* listNodes;
		int numNodes;
	}

	fileNode* createFileNodeList(int);
	fileDir createFileDir(int);

	void initFileNodeList(fileNode*, int, fileNode*);
	void freeFileNodeList(fileNode*, int);
	void printFile(fileNode*);
	void addChild(fileNode*, int, fileNode*, int);
	int updateFileSizes(fileNode*, int);
	fileNode* addNode(fileNode*, int, fileNode*);
	int findFile(fileNode*, int, char[]);
#endif
