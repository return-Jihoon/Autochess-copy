#include "Sprite.h"


Sprite::Sprite() : m_Tex(nullptr)
{
}


Sprite::~Sprite()
{
}

bool Sprite::Create(const wchar_t* _TexName, unsigned int _XCount, unsigned int _YCount, unsigned int _Start, unsigned int _End)
{
	m_LastIdx = _End - 2;

	if (-1 == _Start)
	{
		_Start = 0;
	}

	if (-1 == _End)
	{
		_End = _YCount * _XCount;
	}

	if (_Start > _End)
	{
		BOOM;
		return false;
	}

	if (nullptr == _TexName)
	{
		BOOM;
		return false;
	}

	m_Tex = Resources::Find<Texture>(_TexName);

	if (nullptr == m_Tex)
	{
		BOOM;
		return false;
	}

	if (_End >= (unsigned int)m_CutVec.size())
	{
		m_CutVec.resize(_End + 1);
	}

	// 0���� ������ ��Ʈ���� �ϴµ�
	// �����е��� ���� ���弼��.
	// 12, 5, 5 20
	for (unsigned int i = _Start; i < _End; i++)
	{
		PushCutData(_XCount, _YCount, i);
	}

	return true;
}

void Sprite::PushCutData(unsigned int _XCount, unsigned int _YCount, unsigned int _Index)
{
	// 12, 5
	// 15
	//������ �������??
	unsigned int X = _Index % _XCount;
	unsigned int Y = _Index / _XCount;

	// �ؽ�ó�� UV�� ������ 0~1�� ����.
	Vector4 Data;
	Data.Size.x = (1.0f / (float)_XCount);
	Data.Size.y = (1.0f / (float)_YCount);
	Data.x = Data.Size.x * X; // 1���� ����� ���´�.
	Data.y = Data.Size.y * Y; // 1���� ����� ���´�.

	PushCutData(Data, _Index);
}

void Sprite::PushCutData(Vector4 _CutData, unsigned int _Index)
{
	if (_Index >= (unsigned int)m_CutVec.size())
	{
		m_CutVec.resize(_Index);
	}

	m_CutVec[_Index] = _CutData;
}

void Sprite::Update(Shader::SHADERTYPE _ShaderType, int _SetIndex)
{
	if (nullptr == m_Tex)
	{
		BOOM;
	}

	m_Tex->Update(_ShaderType, _SetIndex);
}

Vector4 Sprite::GetCutData(unsigned int _Index)
{
	if (_Index >= (unsigned int)m_CutVec.size())
	{
		BOOM;
		return { 0.0F };
	}

	return m_CutVec[_Index];
}