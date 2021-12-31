#include "DepthStencilBuffer.h"



DepthStencilBuffer::DepthStencilBuffer()
{
}


DepthStencilBuffer::~DepthStencilBuffer()
{
}

void DepthStencilBuffer::Create(UINT _W, UINT _H, DXGI_FORMAT _eFormat, float _ClearDepth, __int8 _Stencil)
{
	m_ClearDepth = _ClearDepth;
	m_Stencil = _Stencil;
	// �Ϲ����� ���� 
	m_Tex = new Texture();

	//D3D11_USAGE::D3D11_USAGE_DEFAULT �׷��� ī�忡�� �����ϴ� ����
	if (false == m_Tex->Create(_W, _H, _eFormat, D3D11_BIND_DEPTH_STENCIL, D3D11_USAGE::D3D11_USAGE_DEFAULT))
	{
		BOOM;
	}

	m_DSV = m_Tex->GetDSV();
}

void DepthStencilBuffer::Clear() 
{
	if (nullptr != GraphicDevice::MainContext())
	{
		// ��� �����̶�� ���� 
		GraphicDevice::MainContext()->ClearDepthStencilView(m_Tex->GetDSV(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, m_ClearDepth, m_Stencil);
	}
}