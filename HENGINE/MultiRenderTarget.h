#pragma once
#include "Resources.h"
#include "RenderTarget.h"
#include "DepthStencilBuffer.h"
// ���� ���ۿ�
// ����Ÿ���� ��Ƽ�
// �������� ����Ÿ���� �����ϴ� ���� ����
// ���� ���۱��� ������ �����ϰ� ����� �������̴�.
// �ƿ�ǲ ������ �����н�()
// �װ� ���� �н��� �־��ټ��� ����.
// ķ������ �ȵȴ�.
// ķ���� ������ �ִ�.
// �̰� �ظ��ϸ� ķ�� �����ϰ�
// �׷��ٰ� �ܼ���
// ������� �뵵�θ� ����ϴ°���
// �ƴϴ�.
// �⺻�����δ� ��ó���̱� ������
// ���� ȭ�鿡�� �ٲ���?
// ������ �� ȿ���� ���� �ʴ�.
// 
class MultiRenderTarget : Resources
{
private:
	int SizeX;
	int SizeY;

	std::vector<HPTR<RenderTarget>> ArrRenderTarget;
	std::vector<ID3D11RenderTargetView*> ArrRTV;

	HPTR<DepthStencilBuffer> m_DSBUFFER;
	ID3D11DepthStencilView* m_DSV;

public:
	HPTR<RenderTarget> Target(int _Index) 
	{
		return ArrRenderTarget[_Index];
	}

	void Depth(HPTR<DepthStencilBuffer> _DSBUFFER);

	void Clear();

	void CreateTarget(int _W, int _H);
	void OmSet();

public:
	MultiRenderTarget();
	~MultiRenderTarget();
};

