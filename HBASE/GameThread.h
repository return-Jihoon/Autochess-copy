#pragma once
#include "Ref.h"
#include <Windows.h>
#include <process.h>
#include <map>
//#include <string>

// ũ��Ƽ�� ���� �ϳ��� �ϳ��� ����ȭ�� �����ϴ�.
// ������� ����ȭ
// + �޸� ����ȭ
// CRITICAL_SECTION m_CS; ����
// ���谡 �����ϴ� ������ �Ѹ� ���� �ִ�.
// �̳༮�� Ű�� �Ǿ��༭ �� �̿��Ѵ�.

class CriticalSection
{
	friend class Syncronize;

private:
	CRITICAL_SECTION m_CS;

public:
	CriticalSection()
	{
		InitializeCriticalSection(&m_CS);
	}

	~CriticalSection()
	{
		DeleteCriticalSection(&m_CS);
	}
};

class Syncronize
{
public:
	CriticalSection& m_CS;

public:
	Syncronize(CriticalSection& _CS) : m_CS(_CS)
	{
		EnterCriticalSection(&m_CS.m_CS);
	}

	~Syncronize() {
		LeaveCriticalSection(&m_CS.m_CS);
	}
};

// ������ ��ü�� ��ü�� ����� �ʹ�.
class Thread : public Reference
{
private:
	enum THREADARGMODE
	{
		TAM_NEW,
		TAM_LINK,
	};

	//class StaticConAndDes 
	//{
	//public:
	//	StaticConAndDes();
	//	~StaticConAndDes();
	//};
	//friend StaticConAndDes;
	//static StaticConAndDes SCDInst;

public:
	static std::map<std::wstring, HPTR<Thread>> m_AllThread;
	static unsigned HGAMETHREADFUNC(void*);

	static void AllThreadReset();



private:
	static HPTR<Thread> FindThread(const wchar_t* _Name);
	static void DestroyThread(const wchar_t* _Name);

public:
	template<typename T>
	static void CreateThread(const wchar_t* _Name, unsigned(__stdcall* _ThreadFunc)(Thread*, void*), T& _Arg, THREADARGMODE _Mode = THREADARGMODE::TAM_NEW)
	{
		CreateThread(_Name, _ThreadFunc, &_Arg, sizeof(T));
	}

	static void CreateThread(const wchar_t* _Name, unsigned(__stdcall* _ThreadFunc)(Thread*, void*), void* _Arg, int _Size, THREADARGMODE _Mode = THREADARGMODE::TAM_NEW);
	static void DeathThread(const wchar_t* _Name);

private:
	std::wstring m_Name;
	bool m_IsEnd;
	HANDLE m_HANDLE;
	THREADARGMODE m_Mode;
	unsigned int ID;
	void* m_Arg;
	unsigned(__stdcall* m_ThreadFunc)(Thread*, void*);
	
public:
	bool IsDeath() 
	{
		return m_IsEnd;
	}

	void Death() 
	{
		m_IsEnd = true;
	}

private:
	void Start(unsigned(__stdcall* _ThreadFunc)(Thread*, void*), void* _Arg);
	

private:
	Thread();
	~Thread();
};

