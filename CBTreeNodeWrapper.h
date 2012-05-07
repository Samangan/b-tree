#ifndef CBTREENODEWRAPPER_H
#define CBTREENODEWRAPPER_H

#include "CBTreeNode.h"

using namespace std;

class CBTreeNodeWrapper : public CBTreeNode
{
	private:
		int mOffset;
		bool mDirtyFlag;

	public:
		CBTreeNodeWrapper();
		CBTreeNodeWrapper(int Offset);
		CBTreeNodeWrapper(int* ChildrenOffsets, string* keys, int Offset, int KeyCount);
		CBTreeNodeWrapper(int Left, int Right, string Key, int Offset);
		~CBTreeNodeWrapper();
		void SetOffset(int NewOffset);
		int GetOffset();
		void SetDirtyFlag(bool NewFlag);
		bool IsDirty();
		CBTreeNodeWrapper* Split(int Offset);

};
#endif