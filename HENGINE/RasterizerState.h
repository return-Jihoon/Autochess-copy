#pragma once 
#include "Resources.h"

class RasterizerState : public Resources
{
private:
	// Unmap ���� ������.
	// ���Ƽ� ���ִ� ����ȭ ���
	D3D11_RASTERIZER_DESC		m_Decs;
	ID3D11RasterizerState*		m_pState; // ���ؽ�

public:
	bool Create();
	bool Create(const D3D11_RASTERIZER_DESC& _Desc);
	void Update();

public:
	RasterizerState();
	~RasterizerState();
};

