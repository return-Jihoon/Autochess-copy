#pragma once
// 상속받을 애가.
#include "Transform.h"
#include <JTime.h>
#include <KeyInput.h>
#include "Actor.h"

class Actor;
class Logic : public Component
{
public:
	Scene* GetScene();
	HPTR<Actor> CreateObject(const wchar_t* _Name = L"GameObject");

public:
	//virtual void UpdateAfter();
	//virtual void Update();
	//virtual void UpdateBefore();
	//virtual void FinalUpdate();
	//virtual void RenderBefore();
	//virtual void RenderAfter();
	//virtual void ColBefore();
	//virtual void ColAfter();
	//virtual void Release();
	//virtual void ReleaseAfter();


public:
	Logic();
	~Logic();
};

// 
//class MOVEOBJLOGIC : public HLOGIC
//{
//
//};

