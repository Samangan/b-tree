////////////////////////////////////////////////////////////////////////////////
// Jason Ellis, Harry Hull
// Project 3.
// CPSC 3385: File Structures and Multimedia
// Spring 2010
// This class holds the functions that define a node in a BTree.
////////////////////////////////////////////////////////////////////////////////
#include "CBTreeNode.h"
#include <iostream>

int CBTreeNode::mMaxBlockKeys = 0;
int CBTreeNode::mBlockSize = 0;

////////////////////////////////////////////////////////////////////////////////
// Description:
//  Default constructor for a CBTreeNode object
//////////////////////////////////////////////////////////////////////////////////
CBTreeNode :: CBTreeNode()
{	
	mKeyCount = 0;
	
	mChildrenOffsets = new int[mMaxBlockKeys+1]; 
	
	mKeys = new  string [mMaxBlockKeys];
}
////////////////////////////////////////////////////////////////////////////////
// Description:
//  Constructs a CBTreeNode Object 
//	Input Parameters: 
//	  ChildrenOffsets - A reference to an array that holds the children to be transfered.
//	  Keys - A reference to an array that holds the Keys to be transfered.
//	  KeyCount - The keycount of the node.
//////////////////////////////////////////////////////////////////////////////////
CBTreeNode :: CBTreeNode(int* ChildrenOffsets, string* Keys, int KeyCount)
{
	
	mChildrenOffsets = new int[mMaxBlockKeys+1];
	mKeys = new string[mMaxBlockKeys];
	
	for(int i = 0; i < KeyCount; i++)
	{
		mChildrenOffsets[i] = ChildrenOffsets[i];
		mKeys[i] = Keys[i];
	}
	mChildrenOffsets[KeyCount] = ChildrenOffsets[KeyCount];
	mKeyCount = KeyCount;
		
}

////////////////////////////////////////////////////////////////////////////////
// Description:
//  Constructs a CBTreeNode Object 
//	Input Parameters: 
//	  LeftChild - 
//	  RightChild - 
//	  NewKey - 
//////////////////////////////////////////////////////////////////////////////////
CBTreeNode :: CBTreeNode(int LeftChild, int RightChild, string NewKey)
{	
	mKeyCount = 1;	
	mChildrenOffsets = new int[mMaxBlockKeys+1]; 
	mKeys = new string [mMaxBlockKeys];

	mChildrenOffsets[0] = LeftChild;
	mChildrenOffsets[1] = RightChild;

	mKeys[0] = NewKey;
}

////////////////////////////////////////////////////////////////////////////////
// Description:
//  Destructs a CBTreeNode Object by deallocating the pointers to the ChildrenOffsets
//	and Keys arrays.
//////////////////////////////////////////////////////////////////////////////////
CBTreeNode :: ~CBTreeNode()
{
	delete [] mChildrenOffsets;
	delete [] mKeys;
}
////////////////////////////////////////////////////////////////////////////////
// Description:
//  Searches for a key within a node. A binary search is implemented.
//	Input Parameters: 
//	  Target - The key that is being searched for within the node. 
//////////////////////////////////////////////////////////////////////////////////
int CBTreeNode :: Search (const string& Target)
{
	int End = mKeyCount - 1;
	int Start = 0;
	int Middle;
	
	while(Start <= End)
	{
		Middle = (Start + End)/2;
		int Result = strcmp(mKeys[Middle].c_str(), Target.c_str());

		if(Result > 0)
			End = Middle - 1;
		else if (Result < 0)
			Start = Middle + 1;
		else
			return Middle+1;
	}	
	
	return Start;
}

////////////////////////////////////////////////////////////////////////////////
// Description:
//  Determines whether or not a BTreeNode is a leaf.
//////////////////////////////////////////////////////////////////////////////////
bool CBTreeNode :: IsLeaf()
{
	return (mChildrenOffsets[0] == -1);
}

////////////////////////////////////////////////////////////////////////////////
// Description:
//  Determines whether or not a BTreeNode is full.
//////////////////////////////////////////////////////////////////////////////////
bool CBTreeNode :: IsFull()
{
	return (mKeyCount == mMaxBlockKeys);
}

////////////////////////////////////////////////////////////////////////////////
// Description:
//  Inserts a Key into a CBTreeNode.
//	Input Parameters: 
//	  Key - The key to be inserted.
//	  Offset - The offset of the record in the student data file.
//////////////////////////////////////////////////////////////////////////////////
void CBTreeNode :: Insert(string Key, int Offset)
{
	int Stop = Search(Key);
	
	for(int i = mKeyCount; i > Stop; i--)
	{
		mChildrenOffsets[i+1] = mChildrenOffsets[i];
		mKeys[i] = mKeys[i-1];
	}
	mChildrenOffsets[Stop+1] = Offset;
	mKeys[Stop] = Key;
	mKeyCount++;
}

////////////////////////////////////////////////////////////////////////////////
// Description:
//  Gets the needed child offset.
//	Input Parameters: 
//	  Index - The index of the Child's Offset to return.
//////////////////////////////////////////////////////////////////////////////////
int CBTreeNode :: GetChildOffset(int Index)
{
	return mChildrenOffsets[Index];
}

////////////////////////////////////////////////////////////////////////////////
// Description:
//  Gets the needed key from the CBTreeNode.
//	Input Parameters: 
//	  Index - The index of the key needed.
//////////////////////////////////////////////////////////////////////////////////
string CBTreeNode :: GetKey(int Index)
{
	return mKeys[Index];
}

////////////////////////////////////////////////////////////////////////////////
// Description:
//  Gets the number of keys in the CBTreeNode.
//////////////////////////////////////////////////////////////////////////////////
int CBTreeNode :: GetKeyCount()
{
	return mKeyCount;
}

////////////////////////////////////////////////////////////////////////////////
// Description:
//  Configures the CbTreeNodes with the correct block size and maximum block keys.
//	Input Parameters: 
//	  BlockSize - 
//////////////////////////////////////////////////////////////////////////////////
void CBTreeNode :: Configure(int BlockSize)
{
	mBlockSize = BlockSize;
	mMaxBlockKeys = (BlockSize-6)/13; 
}

////////////////////////////////////////////////////////////////////////////////
// Description:
//  Gets the block size of the CBTreeNode.
//////////////////////////////////////////////////////////////////////////////////
int CBTreeNode :: GetBlockSize()
{
	return mBlockSize;
}

////////////////////////////////////////////////////////////////////////////////
// Description:
//  Overloads the input operator to allow for inserting a CBTreeNode.
//	Input Parameters: 
//	  InputStream -  The input FileStream.
//	  CBTreeNode - The CBTreeNode to insert into.
//////////////////////////////////////////////////////////////////////////////////
istream& operator >> (istream& InputStream, CBTreeNode& CBTreeNode)
{
	InputStream.read((char *) &CBTreeNode.mKeyCount, sizeof(CBTreeNode.mKeyCount));
	InputStream.read((char *) &CBTreeNode.mChildrenOffsets[0], sizeof(CBTreeNode.mChildrenOffsets[0]));
	for(int i = 0; i < CBTreeNode.mKeyCount; i++)
	{
		InputStream.width( 9 );
		InputStream >> CBTreeNode.mKeys[i];
		InputStream.read((char *) &CBTreeNode.mChildrenOffsets[i+1], sizeof(CBTreeNode.mChildrenOffsets[i+1]));
	}
	return InputStream;
}

////////////////////////////////////////////////////////////////////////////////
// Description:
//  Overloads the output operator to allow for writing a CBTreeNode.
//	Input Parameters: 
//	  OutputStream -  The output FileStream.
//	  CBTreeNode - The CBTreeNode to write.
//////////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream& OutputStream, CBTreeNode& CBTreeNode)
{
	OutputStream.write((char *) &CBTreeNode.mKeyCount, sizeof(CBTreeNode.mKeyCount));
	OutputStream.write((char *) &CBTreeNode.mChildrenOffsets[0], sizeof(CBTreeNode.mChildrenOffsets[0]));
	for(int i = 0; i < CBTreeNode.mKeyCount; i++)
	{
		OutputStream.write((char *) &CBTreeNode.mChildrenOffsets[i+1],sizeof(CBTreeNode.mChildrenOffsets[i+1])); 
	}
	OutputStream.width((CBTreeNode.mBlockSize) - (4*(CBTreeNode.mKeyCount + 1) + 9*CBTreeNode.mKeyCount + 2));
	OutputStream << "";
	
	return OutputStream;
}
