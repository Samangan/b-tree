 ////////////////////////////////////////////////////////////////////////////////
// Jason Ellis, Harry Hull
// Project 2.
// CPSC 3385: File Structures and Multimedia
// Revision Date: 3/3/2010
// Spring 2010
// This class holds the list of command objects and provides functions to interact
// with the command object.
////////////////////////////////////////////////////////////////////////////////

#include "CCommandList.h"

CCommandList::CCommandList()
{
}

////////////////////////////////////////////////////////////////////////////////
// Description:
//   Reads in the input file into a command list.
//	Input Parameters: 
//	  InputStream- FileStream to an input file.
//	  CommandList- A list of command objects.
//////////////////////////////////////////////////////////////////////////////////

istream& operator >> (istream& InputStream, CCommandList& CommandList)
{
	long long int i = 0;
	while(InputStream.peek() != EOF)
	{
		InputStream >> CommandList.mCommandList[i];
			i++;
	}
	CommandList.mLength = i;
	//cout << CommandList.GetLength();

	return InputStream;
}
////////////////////////////////////////////////////////////////////////////////
// Description:
//   Returns the length of the command list.
//////////////////////////////////////////////////////////////////////////////////
int CCommandList :: GetLength()
{
	return mLength;
}
////////////////////////////////////////////////////////////////////////////////
// Description:
//   Returns a command at the given index.
//	Input Parameters:
//	  Index- The needed index of the command list array.
//////////////////////////////////////////////////////////////////////////////////
CCommand CCommandList :: GetCommand(int Index)
{
	return mCommandList[Index];
}
