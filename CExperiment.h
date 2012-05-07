#ifndef CEXPERIMENT_H
#define CEXPERIMENT_H

#include "CStudentList.h"
#include "CCommandList.h"
#include <fstream>
#include "CTime.h"
#include "CBTree.h"

using namespace std;

class CExperiment
{	
	private:	
		string mInsertFileName;
		CCommandList mCommands;
		fstream mFile;
		CStudentList mStudents;
		CTime mTimes;
		string mOutputFileName;
		ofstream OutputStream;

	public:
		CExperiment();
		~CExperiment();
		void Setup();
		void Run(int BlockSize);	
		
	   
};

#endif