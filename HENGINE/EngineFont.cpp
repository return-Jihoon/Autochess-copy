#include "EngineFont.h"



EngineFont::EngineFont() : m_pFontFactory(nullptr), m_pFontWrapper(nullptr)
{
}


EngineFont::~EngineFont()
{
	if (nullptr != m_pFontFactory)
	{
		m_pFontFactory->Release();
	}

	if (nullptr != m_pFontWrapper)
	{
		m_pFontWrapper->Release();
	}
}

// ���̷�Ʈ���� ��Ʈ�� ����°� ��Ʈ ĳ�� 
// ���� ���տ� ���� ���̴� ó���� ����� �Ѵ�.

bool EngineFont::Create(const wchar_t* _FontName) 
{
	//  C:: ��������.ttf

	if (S_OK != FW1CreateFactory(FW1_VERSION, &m_pFontFactory))
	{
		BOOM;
		return false;
	}

	// m_pFontFactory->CreateFontWrapper()

	if (S_OK != m_pFontFactory->CreateFontWrapper(GraphicDevice::MainDevice(), _FontName, &m_pFontWrapper))
	{
		BOOM;
		return false;
	}

	return true;
}

void EngineFont::DrawWorld(const wchar_t* _Text, float _fSize, Vector4 Pos, Vector4 COLOR, FW1_TEXT_FLAG _Flag)
{
	if (nullptr == m_pFontWrapper)
	{
		BOOM;
		return;
	}

	// 
	// m_pFontWrapper->DrawGeometry
}

void EngineFont::DrawUI(const wchar_t* _Text, float _fSize, Vector4 Pos, Vector4 COLOR, FW1_TEXT_FLAG _Flag /*= FW1_TOP*/)
{
	if (nullptr == m_pFontWrapper)
	{
		BOOM;
		return;
	}

	// �ɼ� ������ �ִ°� ������. ����.
	// FW1_TEXT_FLAG �̰� ��Ʈ ���� �����ε�....
	m_pFontWrapper->DrawString(GraphicDevice::MainContext(), _Text, _fSize, Pos.x, Pos.y, COLOR.ConToUIntColorRGBA(), _Flag);
}