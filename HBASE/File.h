#pragma once
#include "Directory.h"

// �̰� C#�����ϰ� �ִ� �̴ϴ�.
// C#�� ���δ� Ŭ����.

class File : public IOPath
{

public:
	// Ȯ����.
	// Ȯ���� �־��ָ� 
	// true
	bool CheckExtension(const wchar_t* _Ext);
	std::wstring GetFileName();

	Directory GetDirectory();


public:
	File();
	File(const wchar_t* _Path);
	File(const std::wstring& _Path);
	~File();
};

