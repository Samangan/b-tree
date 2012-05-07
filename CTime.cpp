 ////////////////////////////////////////////////////////////////////////////////
// Jason Ellis, Harry Hull
// Project 2.
// CPSC 3385: File Structures and Multimedia
// Revision Date: 3/3/2010
// Spring 2010
// This class holds the functions for storing and computing the elapsed time data
////////////////////////////////////////////////////////////////////////////////

#include <fstream>
#include <string>
#include <windows.h>
#include "CTime.h"
			   

CTime :: CTime()  
{
	mCurrentLength = 0;	
}

////////////////////////////////////////////////////////////////////////////////
// Description:
//   This function stores the current Tick Count.
//	 This number is then stored into an array of type longs.
////////////////////////////////////////////////////////////////////////////////
void CTime :: StoreTime()
{	
	mTimes[mCurrentLength] =  GetTickCount();
	mCurrentLength++;	
}

////////////////////////////////////////////////////////////////////////////////
// Description:
//   After the time data is collected and after the file is closed this function
//	 is called to compute the data stored in the area from the StoreTime() function.
//	Input Parameters: 
//	  FileStream- FileStream to an output file.
//////////////////////////////////////////////////////////////////////////////////

int CTime :: ComputeTime() 
{
	//for(int i = 0; i < mCurrentLength; i++)
	//{ 
		return mTimes[mCurrentLength-1]-mTimes[0];
}

void CTime :: Reset()
{
	mCurrentLength = 0;
}
