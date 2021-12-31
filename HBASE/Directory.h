#pragma once
#include "IOPath.h"
#include <vector>
#include <string>
#include <list>

class File;
class Directory : public IOPath
{
public:
	// ���� �߿��ϴ�.
	// ���������
	// ���ڿ�
	// �����
	// ���α׷����� 3�� �⺻��

	// c::/
	void ReplaceParentPath();
	bool MoveDirectory(const wchar_t* _FolderName);
	bool ExistFile(const wchar_t* _FileName);

	std::wstring GetFoldersName();

	void GetFilesName(std::vector<File>& _List, const wchar_t* _FileEx);

public:
	// virtual std::list<HFILE> AllFiles();

public:
	// �� ���α׷��� ����� ��ġ��
	// �ڽ��� ��η� �������̴�.
	Directory(const Directory& _Other);
	Directory(const wchar_t* _Name);

	Directory();
	// ��ΰ� �����Ȱ�.
	// HDIRECTORY(const wchar_t* _Name);
	~Directory();
};