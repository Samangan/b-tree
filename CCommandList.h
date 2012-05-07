#ifndef CCOMMANDLIST_H
#define CCOMMANDLIST_H

#include "CCommand.h"
#include <fstream>

using namespace std;

class CCommandList
{
	private:
		static const long int cListSize = 4000000;
		CCommand mCommandList[cListSize];
		long long int mLength;

	public:
		CCommandList(void);
		friend istream& operator >> (istream& InputStream, CCommandList& CommandList);
		int GetLength();
		CCommand GetCommand(int Index);

};
#endif