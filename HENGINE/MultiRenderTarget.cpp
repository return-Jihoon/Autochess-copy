#include "MultiRenderTarget.h"


MultiRenderTarget::MultiRenderTarget() : SizeX(-1), SizeY(-1)
{
}


MultiRenderTarget::~MultiRenderTarget()
{
}


void MultiRenderTarget::OmSet() 
{
	GraphicDevice::MainContext()->OMSetRenderTargets((UINT)ArrRTV.size(), &ArrRTV[0], m_DSV);
}

void MultiRenderTarget::Depth(HPTR<DepthStencilBuffer> _DSBUFFER) 
{
	
	if (nullptr != _DSBUFFER)
	{
		m_DSBUFFER = _DSBUFFER;
		m_DSV = _DSBUFFER->DSV();
	}
}

void MultiRenderTarget::CreateTarget(int _W, int _H)
{
	HPTR<RenderTarget> NewTarget = new RenderTarget();

	NewTarget->Create({ 0.0f, 0.0f, 0.0f, 0.0f } // ÀÌ Å¸°ÙÀÌ Å¬¸®¾îÅ¸°Ù µÉ¶§ »ö±ò
		, (UINT)_W // ³Êºñ
		, (UINT)_H // ³ôÀÌ
		, DXGI_FORMAT_R32G32B32A32_FLOAT // »ö±ò ÇüÅÂ
		, D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE);

	ArrRenderTarget.push_back(NewTarget);
	ArrRTV.push_back(NewTarget->m_pRTV);
}

void MultiRenderTarget::Clear() 
{
	for (size_t i = 0; i < ArrRenderTarget.size(); i++)
	{
		ArrRenderTarget[i]->Clear();
	}

}