////////////////////////////////////////////////////////////////////////////////
// Jason Ellis, Harry Hull
// Project 3.
// CPSC 3385: File Structures and Multimedia
// Spring 2010
// This class encapsulates a CBTreeNode.
////////////////////////////////////////////////////////////////////////////////
#include "CBTreeNodeWrapper.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// Description:
//   Default Constructor
//////////////////////////////////////////////////////////////////////////////////
CBTreeNodeWrapper :: CBTreeNodeWrapper(): CBTreeNode()
{
	mOffset = 0; 
	mDirtyFlag = false;
}

////////////////////////////////////////////////////////////////////////////////
// Description:
//   Constructor with offset
//	Input Parameters: 
//		Offset - offset of the node
//////////////////////////////////////////////////////////////////////////////////
CBTreeNodeWrapper :: CBTreeNodeWrapper(int Offset): CBTreeNode()
{
	mOffset = Offset; 
	mDirtyFlag = false;	
}

////////////////////////////////////////////////////////////////////////////////
// Description:
//   Constructor used in split fucntion for creating sibling
//	Input Parameters: 
//		ChildrenOffsets - Array of children offsets
//		Keys - array of keys
//      Offset - offset of node
//      KeyCount - number of keys in in the Keys array
//////////////////////////////////////////////////////////////////////////////////
CBTreeNodeWrapper :: CBTreeNodeWrapper(int* ChildrenOffsets, string* Keys, int Offset, int KeyCount) : CBTreeNode(ChildrenOffsets, Keys, KeyCount)
{
	mOffset = Offset; 
	mDirtyFlag = false;	
}

////////////////////////////////////////////////////////////////////////////////
// Description:
//   Constructor for creating new root
//	Input Parameters: 
//		Left - Left Child of the new root(old root)
//		Right - right childe of the new root(old root's sibling)
//		Key - index key to be added to new root
//      Offset - offset of new root
//////////////////////////////////////////////////////////////////////////////////
CBTreeNodeWrapper :: CBTreeNodeWrapper(int Left, int Right, string Key, int Offset) : CBTreeNode(Left, Right, Key)
{
	mOffset = Offset;
	mDirtyFlag = false;
}

////////////////////////////////////////////////////////////////////////////////
// Description:
//   Destructor
//////////////////////////////////////////////////////////////////////////////////
CBTreeNodeWrapper :: ~CBTreeNodeWrapper()
{
}

////////////////////////////////////////////////////////////////////////////////
// Description:
//   Gets offset of Node
//	Input Parameters: 
//////////////////////////////////////////////////////////////////////////////////
int  CBTreeNodeWrapper :: GetOffset()
{
	return mOffset;
}

////////////////////////////////////////////////////////////////////////////////
// Description:
//   Sets the dirty flag (tee hee)
//	Input Parameters: 
//		NewFlag - value to set dirty flag to
//////////////////////////////////////////////////////////////////////////////////
void CBTreeNodeWrapper :: SetDirtyFlag(bool NewFlag)
{
	mDirtyFlag = NewFlag;
}

////////////////////////////////////////////////////////////////////////////////
// Description:
//   Returns if the dirty flag(if the node needs to be written to file)
//	Input Parameters: 
//////////////////////////////////////////////////////////////////////////////////
bool CBTreeNodeWrapper :: IsDirty()
{
	return mDirtyFlag;
}

////////////////////////////////////////////////////////////////////////////////
// Description:
//   Splits the node, returning a sibling
//	Input Parameters: 
//		Offset - offset of the new sibling
//////////////////////////////////////////////////////////////////////////////////
CBTreeNodeWrapper* CBTreeNodeWrapper :: Split(int Offset)
{
	
	int* NewChildrenOffsets = new int[mMaxBlockKeys+1]; 
	string* NewKeys = new string [mMaxBlockKeys];

	int SplitIndex = 0;
	int SplitNodeKeyCount = 0;

	if(!IsLeaf())
	{	
		if((mKeyCount % 2) == 0)
		{
			SplitIndex = mKeyCount/2+1;
			SplitNodeKeyCount = mKeyCount/2-1;
		}
		else
		{
			SplitIndex = mKeyCount/2 + 1;
			SplitNodeKeyCount = mKeyCount/2;
		}

		int j = 0;
		NewChildrenOffsets[0] = mChildrenOffsets[SplitIndex];
		for(int i = SplitIndex; i < mKeyCount; i++)
		{		
			NewKeys[j] = mKeys[i];
			NewChildrenOffsets[j+1] = mChildrenOffsets[i+1];
			j++;
		}	
	}
	else
	{
		if((mKeyCount % 2) == 0)
		{
			SplitIndex = mKeyCount/2;
			SplitNodeKeyCount = mKeyCount/2;
		}
		else
		{
			SplitIndex = mKeyCount/2 + 1;
			SplitNodeKeyCount = mKeyCount/2;
		}

		NewChildrenOffsets[0] = -1;
		int j = 1;
		for(int i = SplitIndex; i < mKeyCount; i++)
		{
			NewChildrenOffsets[j] = mChildrenOffsets[i+1];
			NewKeys[j-1] = mKeys[i];
			j++;
		}
		NewChildrenOffsets[SplitNodeKeyCount] = mChildrenOffsets[mKeyCount];


	}
	
	CBTreeNodeWrapper* NewNode = new CBTreeNodeWrapper(NewChildrenOffsets, NewKeys, Offset,SplitNodeKeyCount );
	mKeyCount = (mKeyCount%2==0) ? mKeyCount/2 : mKeyCount/2 +1;
	
	delete [] NewChildrenOffsets;
	delete [] NewKeys;

	return NewNode;
}

////////////////////////////////////////////////////////////////////////////////
// Description:
//   Sets of the offset of the node
//	Input Parameters: 
//		NewOffset - new offset of the node
//////////////////////////////////////////////////////////////////////////////////
void CBTreeNodeWrapper :: SetOffset(int NewOffset)
{
	mOffset = NewOffset;
}