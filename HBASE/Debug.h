#pragma once

#include <Windows.h>
#include <assert.h>
#include <iostream>
#include <crtdbg.h>

#define BOOM assert(false)


class Debug
{
public:
	static bool IsOpenConsole;
	static void End() 
	{
		if (true == IsOpenConsole)
		{
			FreeConsole();   //�ܼ��� ����
		}
	}

	static void LeakCheck() 
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	}

	static void ConsolePrintLineArg(const wchar_t* text, ...)
	{
		if (false == IsOpenConsole) 
		{ 
			return; 
		}

		va_list		argp;
		va_start(argp, text);
		wchar_t printText[1024] = { 0, };
		swprintf_s(printText, text, argp);
		va_end(argp);
		std::wcout << printText << std::endl;
	}

	static void ConsolePrintArg(const wchar_t* text, ...)
	{
		if (false == IsOpenConsole) { return; }

		va_list		argp;
		va_start(argp, text);
		wchar_t printText[1024] = { 0, };
		swprintf_s(printText, text, argp);
		va_end(argp);

		std::wcout << text;
	}

	static void OutputDebugStringW(const wchar_t* text = nullptr)
	{
		if (nullptr == text)
		{
			return;
		}

		OutputDebugStringW(text);
	}


	static void ConsolePrintLine(const wchar_t* text = nullptr) 
	{
		if (false == IsOpenConsole)	{ return; }
		if (nullptr == text)
		{
			std::wcout << std::endl;
			return;
		}
		std::wcout << text << std::endl;
	}


	static void ConsolePrintA(const char* text)
	{
		if (false == IsOpenConsole) { return; }
		std::cout << text;
	}


	static void ConsolePrint(const wchar_t* text)
	{
		if (false == IsOpenConsole) { return; }
		std::wcout << text;
	}

	static void OpenConsole()
	{
		//return;
		// �ܼ��� �ϳ� �ߴ°Ű�.
		// �� �ܼ��� ����¿� ������ ������Ѵ�.
		// �ܼ����� ���� ������ �Է����� ��ɷ� �ְڴ�.
		// �ܼ����� �Է��� �������� �Է��� ��ɷ� �ְڴ�.
		if (AllocConsole())
		{
			FILE *acStreamOut;
			FILE *acStreamIn;
			freopen_s(&acStreamOut, "CONOUT$", "wt", stdout);
			freopen_s(&acStreamIn, "CONIN$", "r", stdin);
			IsOpenConsole = true;
			std::wcout.imbue(std::locale("kor"));
			std::wcout << L"Console Debug Start OK" << std::endl;
		}
	}

private:
	Debug() {}
	~Debug() {}

};