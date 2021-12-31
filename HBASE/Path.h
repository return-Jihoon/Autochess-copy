#pragma once
#include "Directory.h"
#include <map>


// Sprite, D:\Project\AR22\AR22API\BIN\Sprite
class Path
{
private:
	static std::map<std::wstring, Directory> m_PathMap;
	// �����ڸ� �ƹ��� �͵� �ȳ־��ָ�
public:
	static Directory Root;

public:
	static inline void SetRootDir(const Directory& _Dir)
	{
		Root = _Dir;
	}

	// �ִ�.
	static inline Directory GetRootDir()
	{
		return Root;
	}
	// ��Ʈ�� �������� � ��θ� ������ִ� �Լ�.
	static void CreatePath(const wchar_t* _Path);
	static void CreatePath(const wchar_t* _Name, const wchar_t* _Path);

	static Directory FindPathToDir(const wchar_t* _Name);

	static std::wstring PlusPath(const wchar_t* _Name, const wchar_t* _PlusPath);

	static std::wstring FindPathToString(const wchar_t* _Name);
	static std::wstring ExtractFileName(const wchar_t* _Path);

private:
	std::wstring m_Path;

public:
	const wchar_t* GetPath() {
		return m_Path.c_str();
	}

	void SetPath(const wchar_t* _Name)
	{
		m_Path = _Name;
	}

protected:
	Path();
	~Path();
};

