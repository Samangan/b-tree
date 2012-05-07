#ifndef CBTREENODE_H
#define CBTREENODE_H

#include <fstream>
#include <string>

using namespace std;

class CBTreeNode
{	
	protected:	
	    static int mMaxBlockKeys; 
		static int mBlockSize;
		short int mKeyCount;
		
		const static int cKeyOffLength = 13;
		int* mChildrenOffsets; 
		string* mKeys; 

	public:
		CBTreeNode();
		CBTreeNode(int LeftChild, int RightChild, string NewKey);
		~CBTreeNode();
		CBTreeNode(int* ChildrenOffsets, string* Keys, int KeyCount);
		int GetChildOffset(int Index);
		int GetBlockSize();
		int GetKeyCount();
		string GetKey(int Index);
		int Search (const string& Target);
		void Insert(string Key, int Offset);
		bool IsLeaf();
		bool IsFull();
		static void Configure(int BlockSize);
		

		friend istream& operator >> (istream& InputStream, CBTreeNode& CBTreeNode);
		friend ostream& operator << (ostream& OutputStream, CBTreeNode& CBTreeNode);
	   


};
#endif