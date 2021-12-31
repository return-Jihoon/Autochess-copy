#include "Ref.h"



Reference::Reference() : mReferenceCount(0), mbDebug(false)
{
}


Reference::~Reference()
{
}

void Reference::DebugCheck()
{
	if (true == mbDebug)
	{
		int a = 0;
	}
}

void Reference::increaseReferenceCount()
{
	++mReferenceCount;
}

void Reference::decreaseReferenceCount()
{
	--mReferenceCount;

	if (0 >= mReferenceCount)
	{
		delete this;
	}
}