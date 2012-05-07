////////////////////////////////////////////////////////////////////////////////
// Jason Ellis, Harry Hull
// Project 3.
// CPSC 3385: File Structures and Multimedia
// Spring 2010
// This class inserts CBTreeNodes into the BTree and searches for CBTreeNodes in the BTree.
////////////////////////////////////////////////////////////////////////////////
#include "CBTree.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// Description:
//   Default Constructor
//////////////////////////////////////////////////////////////////////////////////
CBTree :: CBTree()
{		
}

////////////////////////////////////////////////////////////////////////////////
// Description:
//   Constructor creates the file that the B+Tree will be written.
//		It then configures the tree with the given BlockSize and then writes a 
//		blank root to the B+Tree file.
//	Input Parameters: 
//		BlockSize - Blocksize in bytes of the B+Tree.
//////////////////////////////////////////////////////////////////////////////////
CBTree :: CBTree(int BlockSize)
{	
	mNumberOfNodesReadConstructing = 0;
	mNumberOfNodesWrittenConstructing = 0;

	mNumberOfNodesReadSearching = 0;

	mTreeHeight = 1;

	mBlockSize = -1;  
	mMaxKeys = -1;
	
	CBTreeNode ConfigureNode;
	ConfigureNode.Configure(BlockSize);

	string BTreeFileName = "BTreeFile";
	char Number[] = "0000000000";
	_itoa_s(BlockSize,Number,11,10);
	BTreeFileName += Number;
	BTreeFileName += ".dat";

	mFile.open(BTreeFileName.c_str(), ios::in | ios::out | ios::trunc | ios::binary);
	mFile.seekp(0, ios::beg);
	short int A = 0;
	int B = -1; 
	mFile.write((char*)&A, sizeof(A));
	mFile.write((char*)&B, sizeof(B));
	mFile.width((BlockSize) - (2 + 4));
	mFile << "";

}

////////////////////////////////////////////////////////////////////////////////
// Description:
//   Destructor that closes the file stream.
//////////////////////////////////////////////////////////////////////////////////
CBTree :: ~CBTree()
{
	mFile.close();
}

////////////////////////////////////////////////////////////////////////////////
// Description:
//   Inserts a key into the BTree.
//	Input Parameters: 
//		Key - The key to be inserted into the BTree.
//		RecordFileOffset - The offset in the StudentData file where the rest of 
//			the record is stored.
//////////////////////////////////////////////////////////////////////////////////
void CBTree :: Insert(string Key, int RecordFileOffset)
{
	mFile.seekp(0, ios::beg);
	CBTreeNodeWrapper* CurrentNode = new CBTreeNodeWrapper(0);
	mFile >> *CurrentNode;
	mNumberOfNodesReadConstructing++;

	if(CurrentNode->IsFull())
	{
		mFile.seekp(0,ios::end);
		CurrentNode->SetOffset((int)mFile.tellg());
		CBTreeNodeWrapper* NewRightNode = CurrentNode->Split(CurrentNode->GetOffset()+CurrentNode->GetBlockSize());
		mTreeHeight++;
	
		mFile.seekp(0, ios::beg);
		CBTreeNodeWrapper* NewRoot = new CBTreeNodeWrapper(CurrentNode->GetOffset(), NewRightNode->GetOffset(),CurrentNode->GetKey(CurrentNode->GetKeyCount()),0); 

		mFile << *NewRoot;
		mNumberOfNodesWrittenConstructing++;

		mFile.seekp(0, ios::end);
		
		mFile << *CurrentNode;
		mNumberOfNodesWrittenConstructing++;

		mFile.seekp(0,ios::end);
		mFile << *NewRightNode;
		mNumberOfNodesWrittenConstructing++;
		
		if(Key >= NewRoot->GetKey(0))
		{
			CurrentNode = NewRightNode; 
		}
		delete NewRoot;
	}

	while(!CurrentNode->IsLeaf())
	{
		int NextOffset = CurrentNode->GetChildOffset(CurrentNode->Search(Key));
		mFile.seekg(NextOffset, ios::beg);
		
		CBTreeNodeWrapper* ChildNode = new  CBTreeNodeWrapper(NextOffset);  

		mFile >> *ChildNode;  
		mNumberOfNodesReadConstructing++;
	

		if(ChildNode->IsFull())
		{
			mFile.seekp(0, ios::end);
			CBTreeNodeWrapper* NewRightNode = ChildNode->Split((int) mFile.tellg());  
			string ChildKey = ChildNode->GetKey(ChildNode->GetKeyCount());
		
			CurrentNode->Insert(ChildKey, NewRightNode->GetOffset()); 	
			mFile.seekp(CurrentNode->GetOffset( ), ios::beg);
			
			mFile << *CurrentNode;
			mNumberOfNodesWrittenConstructing++;
		
			if(Key >= ChildKey)
			{
				delete CurrentNode;
				CurrentNode = NewRightNode; 
				CurrentNode->SetDirtyFlag(true);
				mFile.seekp(ChildNode->GetOffset(), ios::beg);
				mFile << *ChildNode;
				mNumberOfNodesWrittenConstructing++;
			}
			else
			{
				delete CurrentNode;
				CurrentNode = ChildNode; 

				
				CurrentNode->SetDirtyFlag(true);
				mFile.seekp(NewRightNode->GetOffset(), ios::beg);
				mFile << *NewRightNode;
				mNumberOfNodesWrittenConstructing++;
			}			
		}		
		else
		{
			delete CurrentNode;
			CurrentNode = ChildNode;
		}
		if(CurrentNode->IsDirty())
		{
			mFile.seekp(CurrentNode->GetOffset(), ios::beg);
			mFile << *CurrentNode;
			mNumberOfNodesWrittenConstructing++;
			CurrentNode->SetDirtyFlag(false);
		}
		
	}
	mFile.seekp(CurrentNode->GetOffset(), ios::beg);
	CurrentNode->Insert(Key, RecordFileOffset);
	mFile << *CurrentNode;
	mNumberOfNodesWrittenConstructing++;
	
	delete CurrentNode;
}

////////////////////////////////////////////////////////////////////////////////
// Description:
//   Searchs for a key in the BTree.
//	Input Parameters: 
//		Key - The key to be looked for in the BTree.
//////////////////////////////////////////////////////////////////////////////////
int CBTree :: Search(string Key)
{	
	mFile.seekp(0, ios::beg);
	
	CBTreeNodeWrapper* CurrentNode= new CBTreeNodeWrapper(0);
	mFile >> *CurrentNode;
	mNumberOfNodesReadSearching++;

	while(!CurrentNode->IsLeaf())
	{
		int ChildIndex = CurrentNode->Search(Key);
		mFile.seekg(CurrentNode->GetChildOffset(ChildIndex),ios::beg); 
		CurrentNode->SetOffset((int)mFile.tellg());  
		mFile >> *CurrentNode; 
		mNumberOfNodesReadSearching++;		
	}
	
	int SearchIndex = CurrentNode->Search(Key);
	if(CurrentNode->GetKey(SearchIndex-1) != Key)
	{
		delete CurrentNode;
		return -1;
	}
		int current = CurrentNode->GetChildOffset(SearchIndex);
		delete CurrentNode;
		return current;	
}

////////////////////////////////////////////////////////////////////////////////
// Description:
//		Gets the number of nodes read from the BTree.
//	Input Parameters: 
//		IsInsert - Determines whether to return the number of reads during 
//			insertion or searching.
//////////////////////////////////////////////////////////////////////////////////
long int CBTree :: GetNodesRead(bool IsInsert)
{
	if(IsInsert == true)
	{
		return mNumberOfNodesReadConstructing;
	}
	else
	{
		return mNumberOfNodesReadSearching;
	}
}

////////////////////////////////////////////////////////////////////////////////
// Description:
//   Gets the number of nodes written to the BTree.
//////////////////////////////////////////////////////////////////////////////////
long int CBTree :: GetNodesWritten()
{
	return mNumberOfNodesWrittenConstructing;
}

////////////////////////////////////////////////////////////////////////////////
// Description:
//   Gets the height of the BTree.
//////////////////////////////////////////////////////////////////////////////////
int CBTree :: GetHeight()
{
	return mTreeHeight;
}




