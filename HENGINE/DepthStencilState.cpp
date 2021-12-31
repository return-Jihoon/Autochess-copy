#include "DepthStencilState.h"



DepthStencilState::DepthStencilState()
{
	// memset(&m_Decs, 0, sizeof(m_Decs));
}


DepthStencilState::~DepthStencilState()
{
	if (nullptr != m_pState)
	{
		m_pState->Release();
		m_pState = nullptr;
	}
}

bool DepthStencilState::Create() 
{
	// ������ ����Ѵ�.
	// 2D�����̸�
	// ���� �׷����� ���� �ڿ� ���� ���̴�.
	m_Decs.DepthEnable = TRUE;

	// �׸��� ���̰��� ���Ҷ�
	// �ȼ����̴����� ���� ó�� �ؾ��Ѵٰ� ������� �ϴµ�. 
	// ���ο� �ȼ��� ���̰���
	// ������ ���̰����� ������.

	// 2D�����̸�
	// ���� �׷����� ���� �ڿ� ���� ���̴�.
	m_Decs.DepthFunc = D3D11_COMPARISON_LESS;

	// ���θ� ���⸸ �ϰ� 
	// ���� �������� �ʴ´�. 
	// ������ ������ ���ؼ��� 
	// Z���� ������ 
	m_Decs.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	m_Decs.StencilEnable = FALSE;

	//BOOL DepthEnable;
	//D3D11_DEPTH_WRITE_MASK DepthWriteMask;
	//D3D11_COMPARISON_FUNC DepthFunc;
	// BOOL StencilEnable;
	// UINT8 StencilReadMask;
	// UINT8 StencilWriteMask;
	// D3D11_DEPTH_STENCILOP_DESC FrontFace;
	// D3D11_DEPTH_STENCILOP_DESC BackFace;

	//typedef struct D3D11_DEPTH_STENCILOP_DESC
	//{
	//	D3D11_STENCIL_OP StencilFailOp;
	//	D3D11_STENCIL_OP StencilDepthFailOp;
	//	D3D11_STENCIL_OP StencilPassOp;
	//	D3D11_COMPARISON_FUNC StencilFunc;
	//} 	D3D11_DEPTH_STENCILOP_DESC;

	//D3D11_STENCIL_OP_KEEP = 1,
	//D3D11_STENCIL_OP_ZERO = 2,
	//D3D11_STENCIL_OP_REPLACE = 3,
	//D3D11_STENCIL_OP_INCR_SAT = 4,
	//D3D11_STENCIL_OP_DECR_SAT = 5,
	//D3D11_STENCIL_OP_INVERT = 6,
	//D3D11_STENCIL_OP_INCR = 7,
	//D3D11_STENCIL_OP_DECR = 8


	// �����޽�.

	return Create(m_Decs);
}

bool DepthStencilState::Create(const D3D11_DEPTH_STENCIL_DESC& _Desc) 
{
	if (&m_Decs != &_Desc)
	{
		m_Decs = _Desc;
	}

	if (S_OK != GraphicDevice::MainDevice()->CreateDepthStencilState(&m_Decs, &m_pState))
	{
		BOOM;
		return false;
	}

	return true;
}

void DepthStencilState::Update() 
{
	// 0~255������ ��ȣ��.
	// �ȼ��� ���� ���������� �ű⿡ ���� ���� ���ٽ� ���̴�.
	GraphicDevice::MainContext()->OMSetDepthStencilState(m_pState, 0);
}