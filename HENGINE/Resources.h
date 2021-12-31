#pragma once
#include <Ref.h>
#include <Name.h>
#include <string>
#include <Path.h>
#include <File.h>
#include <map>
#include <unordered_map>

#include "GraphicDevice.h"


// ���߻��.
// �̸��� �Ȱ�ġ�� �ȴ�.
// Name �Լ��� �ɹ��������� ������ �������� ������� �ʾұ� ������ �����ϴ�.
// ���� �����е��� ���߻���� ����Ϸ��µ�
// �������� ����ϰ� �ʹٸ� ���������Լ��� ���ؼ� ����϶�.
// �� ���������Լ��� �������� �ʴ� ��
// c#������ �̷� ������ �������̽���� �Ͽ� �ƿ� �������� �����Ѵ�.


// ��ȯ�� �ȵȴٴ� ����
// ������ �Ǽ�.
// ����� ��� ���.
// HRES�� �ʿ��� ������ �ܼ��� ������ ���ֱ����� Ŭ������ �ȴ�.
class Resources : public Reference, public Name
{
private:
	// ����Ʈ Ÿ��
	// ����Ʈ ���ڿ� ���������� �Լ��� ������ ���� �����ʿ�
	// �ִ� �༮�� ����Ʈ�� �־��� �� �ִ�.
	template<typename RESTYPE>
	class HRESMGR
	{
	public:
		// �ӷ����ַ� �Ϸ���.
		// MAP�̸� �������ַ�
		// unordered_map �ӷ��� ������.
		static std::unordered_map<std::wstring, HPTR<RESTYPE>> m_ResMap;

		// ���ø� �Ҷ� �̳�Ŭ������ ���� Ÿ���� �Ҹ�Ȯ������ ������ �ִµ�.
		// static std::unordered_map<std::wstring, HPTR<RESTYPE>>::iterator FindIter;

	public:
		static HPTR<RESTYPE> Find(const std::wstring& _Key)
		{
			typename std::unordered_map<std::wstring, HPTR<RESTYPE>>::iterator FindIter = m_ResMap.find(_Key);

			if (FindIter == m_ResMap.end())
			{
				return nullptr;
			}

			return FindIter->second;
		}

		template<class... _Types>
		static HPTR<RESTYPE> Load(const std::wstring& _Path, _Types&&... _Args)
		{
			File NewFile = _Path;
			std::wstring FName = NewFile.GetFileName();
			return Load(FName, _Path, _Args...);
		}


		template<class... _Types>
		static HPTR<RESTYPE> Load(const std::wstring& _Name, const std::wstring& _Path, _Types&&... _Args)
		{
			// ������� �����ϴ� �޸𸮴�???
			// �ڵ� ������ �� 
			// �����忡 ������ ������
			// �޸� �������� ������
			// ������ ���Ҷ�. 


			if (nullptr != Find(_Name))
			{
				BOOM;
				return nullptr;
			}

			RESTYPE* NewRes = new RESTYPE();
			// Ű�� Ÿ���� ���� Ű�� wstring�� �ƴ϶��
			// char*
			// wchar_t* �� �ƴ϶�� ���ڿ��� �ƴ϶��
			NewRes->SetName(_Name);
			NewRes->FileSetting(_Path);
			if (false == NewRes->Load(_Args...))
			{
				BOOM;
				return nullptr;
			}


			// �̳༮
			m_ResMap.insert(std::unordered_map<std::wstring, HPTR<RESTYPE>>::value_type(_Name, NewRes));
			return NewRes;
		}


		template<class... _Types>
		static HPTR<RESTYPE> LoadToKey(const std::wstring& _Key, const std::wstring& _Path, _Types&&... _Args)
		{
			if (nullptr != Find(_Key))
			{
				BOOM;
				return nullptr;
			}

			RESTYPE* NewRes = new RESTYPE();
			// Ű�� Ÿ���� ���� Ű�� wstring�� �ƴ϶��
			// char*
			// wchar_t* �� �ƴ϶�� ���ڿ��� �ƴ϶��
			NewRes->SetName(_Key);
			NewRes->FileSetting(_Path);
			if (false == NewRes->Load(_Args...))
			{
				BOOM;
				return nullptr;
			}


			m_ResMap.insert(std::unordered_map<std::wstring, HPTR<RESTYPE>>::value_type(_Key, NewRes));

			return NewRes;
		}

		// Create�׷��� Res�� Create��� �̸��� ���� �Լ� ��ü�� ����� ��� �Ѵ�.
		template<class... _Types>
		static HPTR<RESTYPE> Create(const std::wstring& _Key, _Types&&... _Args)
		{
			if (nullptr != Find(_Key))
			{
				BOOM;
				return nullptr;
			}

			RESTYPE* NewRes = new RESTYPE();
			// Ű�� Ÿ���� ���� Ű�� wstring�� �ƴ϶��
			// char*
			// wchar_t* �� �ƴ϶�� ���ڿ��� �ƴ϶��
			NewRes->SetName(_Key);
			if (false == NewRes->Create(_Args...))
			{
				BOOM;
				return nullptr;
			}
			m_ResMap.insert(std::unordered_map<std::wstring, HPTR<RESTYPE>>::value_type(_Key, NewRes));

			return NewRes;
		}
	};

public:
	template<typename RESTYPE>
	static HPTR<RESTYPE> Find(const std::wstring& _Key)
	{
		return HRESMGR<RESTYPE>::Find(_Key);
	}

	template<typename RESTYPE, class... _Types >
	static HPTR<RESTYPE> Create(const std::wstring& _Key, _Types&&... _Args)
	{
		return HRESMGR<RESTYPE>::Create(_Key, _Args...);
	}

	// �ӽð�ü�� ���� ���Ϲ޴� ���۷���
	// RValue ���۷���
	template<typename RESTYPE, class... _Types>
	static HPTR<RESTYPE> Load(const std::wstring& _Path, _Types&&... _Args)
	{
		return HRESMGR<RESTYPE>::Load(_Path, _Args...);
	}

	template<typename RESTYPE, class... _Types>
	static HPTR<RESTYPE> LoadToName(const std::wstring& _Name, const std::wstring& _Path, _Types&&... _Args)
	{
		return HRESMGR<RESTYPE>::Load(_Name, _Path, _Args...);
	}

	template<typename RESTYPE, class... _Types>
	static HPTR<RESTYPE> LoadToKey(const std::wstring& _Key, const std::wstring& _Path, _Types&&... _Args)
	{
		return HRESMGR<RESTYPE>::LoadToKey(_Key, _Path, _Args...);
	}

protected:
	// ���Ͽ��� 
	File m_File;

public:
	virtual bool Create() { return true; }
	virtual bool Load() { return true; }

public:
	void FileSetting(const wchar_t* _Path) {
		m_File.PathSetting(_Path);
	}

	void FileSetting(const std::wstring& _Path) {
		m_File.PathSetting(_Path.c_str());
	}

public:
	Resources();
	~Resources();
};

template<typename RESTYPE>
std::unordered_map<std::wstring, HPTR<RESTYPE>> Resources::HRESMGR<RESTYPE>::m_ResMap;
