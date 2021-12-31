#pragma once
#include <vector>
#include "Texture.h"

// �ؽ�ó�� �ɰ� ������ ������� ��.
class Texture;
class Sprite : public Resources
{
private:
	HPTR<Texture> m_Tex;
	std::vector<Vector4> m_CutVec;

	int m_LastIdx;

public:
	unsigned int MultiCount() 
	{
		return (unsigned int)m_CutVec.size();
	}

	int GetLastIdx()
	{
		return m_LastIdx;
	}

public:
	// for������ �ڸ��°�.
	// 21 50 �߶��ּ���

	// SOLID �߿� �������̽� �и���Ģ.

	bool Create(const wchar_t* _TexName, unsigned int _XCount, unsigned int _YCount, unsigned int _Start = -1, unsigned int _End = -1);

	// 1 12 5 �ڸ��ڴ�.
	void PushCutData(unsigned int _XCount, unsigned int _YCount, unsigned int _Index);
	void PushCutData(Vector4 _CutData, unsigned int _Index);

public:
	Vector4 GetCutData(unsigned int _Index);

	void Update(Shader::SHADERTYPE _ShaderType, int _SetIndex);


public:
	Sprite();
	~Sprite();
};

