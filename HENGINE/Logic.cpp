#include "Logic.h"
#include "Scene.h"

Logic::Logic()
{
}

Logic::~Logic()
{
}


Scene* Logic::GetScene() 
{
	return GetActor()->GetScene();
}

HPTR<Actor> Logic::CreateObject(const wchar_t* _Name)
{
	return GetScene()->CreateActor(_Name);
}