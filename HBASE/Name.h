#pragma once
#include <string>

// virtual을 하면 가상함수 테이블이 생기므로
// virtual이 없다면 일단 안전하다.
class Name
{
public:
	const wchar_t*		GetName() 
	{
		return mName.c_str();
	}
	void				SetName(const wchar_t* _Name) 
	{
		mName = _Name;
	}
	void				SetName(const std::wstring& _Name)
	{
		mName = _Name;
	}
	const std::wstring& CWStringName()
	{
		return mName;
	}

private:
	std::wstring mName;

protected:
	Name();
	~Name();
};

