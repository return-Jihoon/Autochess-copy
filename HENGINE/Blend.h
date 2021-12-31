#pragma once
#include "Resources.h"

class Blend :
	public Resources
{
private:
	D3D11_BLEND_DESC	m_Decs;
	ID3D11BlendState*	m_pState; // ���ؽ�
	Vector4				m_Color;

	// ID3D11DepthStencilState*	m_pState; // ���ؽ�


public:
	bool Create();
	bool Create(const D3D11_BLEND_DESC& _Desc);
	void Update();

public:
	Blend();
	~Blend();
};

