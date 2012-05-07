#ifndef CCOMMAND_H
#define CCOMMAND_H

#include <string>
#include <iostream>

using namespace std;

class CCommand
{	
	private:
		string mRecord;
		bool mIsInsert;
		string mId;

	public:
		CCommand();
		bool CommandIsInsert();
		string GetRecord();
		string GetId();
		friend istream& operator >> (istream& InputStream, CCommand& Command);
};

#endif
