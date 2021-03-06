#include "Directory.h"
#include "Debug.h"
#include "File.h"

// 

#include <atlstr.h>

#include <stdio.h>
#include <io.h>
#include <conio.h>



Directory::Directory()
{
	wchar_t Arr[1000];
	GetCurrentDirectoryW(1000, Arr);
	m_FullPath = Arr;
}

Directory::Directory(const wchar_t* _Path) 
{
	PathSetting(_Path);
	FileCheck();
}

Directory::~Directory()
{
}

void Directory::ReplaceParentPath() 
{
	Directory();

	// 123456789
	// C:\\BBB\\CCC
	// 'F'
	size_t CutCount = m_FullPath.find_last_of(L'\\', m_FullPath.size());
	// ġȯ
	m_FullPath.replace(CutCount, m_FullPath.size(), L"");
}

bool Directory::MoveDirectory(const wchar_t* _FolderName)
{
	std::wstring FindPath = m_FullPath + L"\\" + _FolderName;

	if (false == IO::ExistFile(FindPath.c_str()))
	{
		BOOM;
		return false;
	}

	m_FullPath = FindPath;

	return true;
}



//std::vector<std::wstring> HDIRECTORY::AllFiles() 
//{
//}

Directory::Directory(const Directory& _Other)  
{
	PathSetting(_Other.m_FullPath);
}

bool Directory::ExistFile(const wchar_t* _FileName)
{

	// std::wstring opertor +();
	return IO::ExistFile((m_FullPath + L"\\" + _FileName).c_str());
}

std::wstring Directory::GetFoldersName() 
{
	return GetFileName();
}

void Directory::GetFilesName(std::vector<File>& _List, const wchar_t* _FileEx)
{
	std::string Path = CW2A(m_FullPath.c_str()).m_psz;
	std::string Ex = CW2A(_FileEx).m_psz;
	Path.append("\\");
	Path.append(Ex);

	std::string PlusPath = CW2A(m_FullPath.c_str()).m_psz;
	PlusPath.append("\\");

	_finddata_t fd;
	intptr_t handle;
	int result = 1;
	handle = _findfirst(Path.c_str(), &fd);
	//현재 폴더 내 모든 파일을 찾는다.

	if (handle == -1)
	{
		printf("There were no files.\n");
		return;
	}

	while (result != -1)
	{
		if ('.' != fd.name[0])
		{
			_List.push_back(File(CA2W((PlusPath + fd.name).c_str()).m_psz));
		}


		result = _findnext(handle, &fd);
	}

	_findclose(handle);
	return;
}

