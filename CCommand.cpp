////////////////////////////////////////////////////////////////////////////////
// Jason Ellis, Harry Hull
// Project 3.
// CPSC 3385: File Structures and Multimedia
// Revision Date: 3/3/2010
// Spring 2010
// This class holds the command object.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include "CCommand.h"


CCommand :: CCommand()  
{	
}

////////////////////////////////////////////////////////////////////////////////
// Description:
//   Reads in from the file stream a single command.
//	Input Parameters: 
//	  InputStream- FileStream to an input file.
//	  Command- A object that holds the command and the record.
//////////////////////////////////////////////////////////////////////////////////
istream& operator >> (istream& InputStream, CCommand& Command)
{
	string command;

	getline(InputStream, command, ',');

	if(command == "Insert")
	{ 
		Command.mIsInsert = true;
	}
	else
	{
		Command.mIsInsert = false;
	}

	
	if(Command.mIsInsert)
	{
		getline(InputStream, Command.mId, ',');
		getline(InputStream, Command.mRecord, '\n');
	}
	else
	{
		getline(InputStream, Command.mId, '\n');
	}

	return InputStream;
}


////////////////////////////////////////////////////////////////////////////////
// Description:
//   Returns true if command is an insert and false if it is a delete command.
//////////////////////////////////////////////////////////////////////////////////
bool CCommand :: CommandIsInsert()
{
	return mIsInsert;
}


string CCommand :: GetId()
{
	return mId;
}
////////////////////////////////////////////////////////////////////////////////
// Description:
//   Returns the student record string.
//////////////////////////////////////////////////////////////////////////////////
string CCommand :: GetRecord()
{
	return mRecord;
}