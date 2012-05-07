#ifndef CBTREE_H
#define CBTREE_H

#include <fstream>
#include <string>
#include "CBTreeNodeWrapper.h"

using namespace std;

class CBTree
{	
	private:
		fstream mFile;
		int CBTree::mBlockSize;    
		int CBTree::mMaxKeys; 
		
		long int mNumberOfNodesReadConstructing;
		long int mNumberOfNodesWrittenConstructing;

		long int mNumberOfNodesReadSearching;

		int mTreeHeight;
		
	public:
		CBTree();
		CBTree(int BlockSize);
		~CBTree();
		void Insert(string Key, int RecordFileOffset);
		int Search(string Key);
		
		int GetHeight();
		
		long int GetNodesRead(bool IsInsert);
		long int GetNodesWritten();
};

#endif