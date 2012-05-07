
#ifndef CSTUDENTLIST_H
#define CSTUDENTLIST_H

#include <fstream>
#include <string>
using namespace std;

class CStudentList
{	
	private:
		fstream FileStream;
		string FileName;

	public: 
		CStudentList();
		~CStudentList();
		int AddStudent(string Record); 
		string GetStudent(int Offset); 



};

#endif
