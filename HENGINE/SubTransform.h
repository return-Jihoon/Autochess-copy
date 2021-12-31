#pragma once
#include "Transform.h"
class SubTransform : public Transform
{
private:
	bool IsRotLock;
	bool IsPosLock;
	bool IsScaleLock;

public:
	SubTransform();
	~SubTransform();
};

