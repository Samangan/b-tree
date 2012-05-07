 ////////////////////////////////////////////////////////////////////////////////
// Jason Ellis, Harry Hull
// Project 3.
// CPSC 3385: File Structures and Multimedia
// Spring 2010
// This class handles 
////////////////////////////////////////////////////////////////////////////////

#include "CStudentList.h"
#include <iostream>



////////////////////////////////////////////////////////////////////////////////
// Description:
//   Constructs CStudentList object by opening the file stream.
//	Input Parameters: 
//////////////////////////////////////////////////////////////////////////////////
CStudentList :: CStudentList()  
{
	FileName = "StudentData.dat";
	FileStream.open(FileName.c_str(), ios::in | ios::out | ios::trunc);
	FileStream << "|";
}


////////////////////////////////////////////////////////////////////////////////
// Description:
//   Destructs the CStudentList object by closing the file stream.
//	Input Parameters: 
//////////////////////////////////////////////////////////////////////////////////
CStudentList :: ~CStudentList()
{
	FileStream.close(); 
}

////////////////////////////////////////////////////////////////////////////////
// Description:
//   Adds a student to the CStudentList by writing it to the file stream.
//	Input Parameters: 
//		Record - Student Record to be written to file.
//////////////////////////////////////////////////////////////////////////////////
int CStudentList :: AddStudent(string Record) //returns file offset of what was just added
{
	int Offset = 0;
	FileStream.seekp(0,ios::end);
	Offset = (int) FileStream.tellg();
	FileStream << Record << "|";
	//cout << "Record: " << Record << " At offset: " << Offset << endl;
	return Offset;
}

////////////////////////////////////////////////////////////////////////////////
// Description:
//   Gets Student Record at Offset
//	Input Parameters: 
//		Offset - Offset to retrieve student record from.
//////////////////////////////////////////////////////////////////////////////////
string CStudentList :: GetStudent(int Offset)
{

	string Record;
	FileStream.seekg(Offset);
	getline(FileStream, Record, '|');
	return Record;
}