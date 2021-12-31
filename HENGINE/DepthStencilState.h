#pragma once
#include "Resources.h"

// ���׸��󳻺��� �Լ��� ������ �����������̶�� �����.

// �Ϻ���.
// ���ս��� ������.
// ���� �����Ȳ���δ� ������ ����������
// �߳����� �ִ�.
// ���� �ڵ���� �Ϻ������� ���ڴ�.

class DepthStencilState : public Resources
{
private:
	D3D11_DEPTH_STENCIL_DESC	m_Decs;
	ID3D11DepthStencilState*	m_pState; // ���ؽ�

public:
	bool Create();
	bool Create(const D3D11_DEPTH_STENCIL_DESC& _Desc);
	void Update();


public:
	DepthStencilState();
	~DepthStencilState();
};

