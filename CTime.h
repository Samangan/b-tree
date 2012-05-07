#ifndef CTIME_H
#define CTIME_H

#include <fstream>

using namespace std;

class CTime
{	
	private:	
		static const long cLength = 4000000;
		unsigned long mTimes[cLength];
		int mCurrentLength;
	public:
		CTime();
		void StoreTime();
		int ComputeTime();
		void Reset();
};


#endif

