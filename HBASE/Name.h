#pragma once
#include <string>

// virtual�� �ϸ� �����Լ� ���̺��� ����Ƿ�
// virtual�� ���ٸ� �ϴ� �����ϴ�.
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

