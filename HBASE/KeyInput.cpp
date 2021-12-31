#include "KeyInput.h"
#include <Windows.h>


HPTR<Input::Key> Input::mNewKey = nullptr;
std::map<std::wstring, HPTR<Input::Key>> Input::mAllKeyMap;
std::map<std::wstring, HPTR<Input::Key>>::iterator Input::mKeyStartIter;
std::map<std::wstring, HPTR<Input::Key>>::iterator Input::mKeyEndIter;

/////////////////////////// Key

Input::Key::Key() : mUp(false),mUpAway(true),mDown(false),mPress(false)
{

}
Input::Key::~Key() {

}

void Input::Key::Update() 
{
	if (true == IsKeyCheck()) // ��Ű�� �����ִ�.
	{
		if (true == mUpAway) // ���� �ȴ����ִ�.
		{
			// Ű�� ���ȴ°�? yes
			// ���� �����ӿ��� Ű�� �����°�? no
			mUp = false;
			mUpAway = false;
			mDown = true;
			mPress = true;
		}
		else 
		{
			// Ű�� ���ȴ°�? yes
			// ���� �����ӿ��� Ű�� �����°�? yes
			mUp = false;
			mUpAway = false;
			mDown = false;
			mPress = true;
		}
	}
	else 
	{

		if (true == mPress) 
		{
			// Ű�� ���ȴ°�? no
			// ���� �����ӿ��� Ű�� �����°�? yes
			mUp = true;
			mUpAway = true;
			mDown = false;
			mPress = false;
		}
		else
		{
			// Ű�� ���ȴ°�? no
			// ���� �����ӿ��� Ű�� �����°�? no
			mUp = false;
			mUpAway = true;
			mDown = false;
			mPress = false;
		}
	}
}

bool Input::Key::IsKeyCheck() 
{
	for (size_t i = 0; i < mKeyVector.size(); i++)
	{
		if (0 == GetAsyncKeyState(mKeyVector[i]))
		{
			return false;
		}
	}

	return true;
}

////////////////////// Input



Input::Input()
{
}


Input::~Input()
{
}


HPTR<Input::Key> Input::findKey(const wchar_t* _Name)
{
	std::map<std::wstring, HPTR<Key>>::iterator FindIter = mAllKeyMap.find(_Name);

	if (FindIter == mAllKeyMap.end())
	{
		return nullptr;
	}

	return FindIter->second;
}
//
//void HINPUT::InputEnd()
//{
//	KeyStart = m_AllKey.begin();
//	KeyEnd = m_AllKey.end();
//
//	for (; KeyStart != KeyEnd; ++KeyStart)
//	{
//		if (nullptr != KeyStart->second)
//		{
//			delete KeyStart->second;
//			KeyStart->second = nullptr;
//		}
//	}
//}


void Input::Update() 
{
	mKeyStartIter = mAllKeyMap.begin();
	mKeyEndIter = mAllKeyMap.end();

	for (; mKeyStartIter != mKeyEndIter; ++mKeyStartIter)
	{
		mKeyStartIter->second->Update();
	}
}

bool Input::Down(const wchar_t* _Name) 
{
	HPTR<Input::Key> FKey = findKey(_Name);

	if (nullptr == FKey)
	{
		BOOM;
	}

	return FKey->mDown;
}
bool Input::UpAway(const wchar_t* _Name) {
	HPTR<Input::Key> FKey = findKey(_Name);

	if (nullptr == FKey)
	{
		BOOM;
	}

	return FKey->mUpAway;
}
bool Input::Press(const wchar_t* _Name) {
	HPTR<Input::Key> FKey = findKey(_Name);

	if (nullptr == FKey)
	{
		BOOM;
	}

	return FKey->mPress;
}
bool Input::Up(const wchar_t* _Name) {
	HPTR<Input::Key> FKey = findKey(_Name);

	if (nullptr == FKey)
	{
		BOOM;
	}

	return FKey->mUp;
}

bool Input::IsKey(const wchar_t* _Name) {
	HPTR<Input::Key> FKey = findKey(_Name);

	if (nullptr == FKey)
	{
		return false;
	}

	return true;
}