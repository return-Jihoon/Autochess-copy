#pragma once
#include "Resources.h"
#include "RenderTarget.h"
#include "DepthStencilBuffer.h"
// 깊이 버퍼와
// 랜더타겟을 모아서
// 여러개의 랜더타겟을 세팅하는 것은 물론
// 깊이 버퍼까지 세팅이 가능하게 만들어 놓을것이다.
// 아웃풋 머저의 랜더패스()
// 그게 랜더 패스에 넣어줄수는 없다.
// 캠때문에 안된다.
// 캠마다 가지고 있다.
// 이건 왠만하면 캠이 관리하고
// 그렇다고 단순히
// 최종출력 용도로만 사용하는것은
// 아니다.
// 기본적으로는 빛처리이기 때문에
// 지금 화면에서 바뀔까요?
// 심지어 더 효율이 좋지 않다.
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

