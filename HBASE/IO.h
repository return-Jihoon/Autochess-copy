#pragma once
// io input output�� ����
// ��������� �Լ��� �ƴϸ� ������
// ��κ� io ��� 
// img Texture
// #include <Windows.h>
// #include <Windows.h>
// �ΰ����� ���ÿ� 


// #include <Windows.h>
#include <Windows.h>
// �⺻���� �������� ���� �ǵ��� �ʾƵ� ����ش�.

#include <iostream>
#include <io.h>

class IO
{
public:
	static bool ExistFile(const char* _FileName);
	static bool ExistFile(const wchar_t* _FileName);

private:
	IO() {}
	~IO() {}
};

