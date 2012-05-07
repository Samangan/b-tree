 ////////////////////////////////////////////////////////////////////////////////
// Jason Ellis, Harry Hull
// Project 3.
// CPSC 3385: File Structures and Multimedia
// Spring 2010
// This class combines the functions from the other classes to perform
// the needed trials.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include "CExperiment.h"



CExperiment :: CExperiment()  
{
	mInsertFileName = "InsertSearchCommands.csv";
	mOutputFileName = "FinalOutput.csv";

	OutputStream.open(mOutputFileName.c_str(), ios::trunc);

	OutputStream << "blocksize, total construction time, total search time, num of nodes read, num of nodes written, height of b-tree, number of nodes read while searching" << endl;
}

CExperiment :: ~CExperiment()
{
	OutputStream.close();
}

////////////////////////////////////////////////////////////////////////////////
// Description:
//   Setup reads in the command file into a command list object.
//////////////////////////////////////////////////////////////////////////////////
void CExperiment :: Setup()
{		
	ifstream InsertFile;  
	InsertFile.open(mInsertFileName.c_str());	
	if(!InsertFile)
	{
		cerr << "Error opening Insert Command File";
		exit(1);
	}
	InsertFile.ignore(89234, '\n'); 
	InsertFile >> mCommands;
	InsertFile.close();
	//mStudents = CStudentList();

	
}

////////////////////////////////////////////////////////////////////////////////
// Description:
//  This function processes each command in the commandlist while tracking the time. 
//	It calls the various calculate functions to produce data.
//	Input Parameters: 
//	  BlockSize - The size (in bytes) of each node in the b+tree
//////////////////////////////////////////////////////////////////////////////////
void CExperiment :: Run(int BlockSize)
{
	int NewOffset;
	CBTree RunTree = CBTree(BlockSize);

	OutputStream << BlockSize << ", ";

	mTimes.StoreTime();

	bool insert = true;
	for (int i = 0; i < mCommands.GetLength(); i++)
	{
		if(mCommands.GetCommand(i).CommandIsInsert())
		{
			if(i%5555 == 0)
			{
				cout << '.';
			}
			insert = true;
			NewOffset = mStudents.AddStudent(mCommands.GetCommand(i).GetId() + ", " + mCommands.GetCommand(i).GetRecord());
			RunTree.Insert(mCommands.GetCommand(i).GetId(), NewOffset);
		}
		else
		{
			if(insert == true)
				{
					mTimes.StoreTime();
					OutputStream << mTimes.ComputeTime() << ", ";
					mTimes.Reset();
					insert = false;
					mTimes.StoreTime();
				}
			
			
			int SearchOffset = RunTree.Search(mCommands.GetCommand(i).GetId());
			if(SearchOffset == -1)
			{
				cout << "ID: " << mCommands.GetCommand(i).GetId()<< " NOT FOUND" << endl;
			}
			else
			{
				//cout << mStudents.GetStudent(SearchOffset);
			}
		}		
	}
	mTimes.StoreTime();
	OutputStream << mTimes.ComputeTime() << ", ";
	mTimes.Reset();
	
		
	OutputStream << RunTree.GetNodesRead(1) << ", " << RunTree.GetNodesWritten() << ", " <<  RunTree.GetHeight() << ", " <<  RunTree.GetNodesRead(0) << endl;

	

}
