#include "RenderTarget.h"
#include "GraphicDebug.h"


RenderTarget::RenderTarget()
{
}


RenderTarget::~RenderTarget()
{
}

void RenderTarget::Clear() {

	if (nullptr != GraphicDevice::MainContext())
	{
		GraphicDevice::MainContext()->ClearRenderTargetView(m_pRTV, m_ClearColor.Arr);
	}
}

bool RenderTarget::Create(Vector4 _ClearColor, UINT _W, UINT _H, DXGI_FORMAT _eFormat, UINT _BindFlag)
{
	if (0 == _W)
	{
		BOOM;
	}

	if (0 == _H)
	{
		BOOM;
	}

	m_ClearColor = _ClearColor;

	m_Tex = new Texture();

	m_Tex->Create(_W, _H, _eFormat
		, _BindFlag
	, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	// 그래픽 카드로만 텍스처의 정보를 수정(랜더)할수 있다.
	// setpixel작업은 안될것이다.

	m_pRTV = m_Tex->GetRTV();
	m_pSRV = m_Tex->GetSRV();

	return true;
}

void RenderTarget::OmSet(ID3D11DepthStencilView* _pDSV)
{
	GraphicDevice::MainContext()->OMSetRenderTargets(1, &m_pRTV, _pDSV);
}

// 이녀석은 모른다.
// 
void RenderTarget::ShaderUpdate(Shader::SHADERTYPE _Type, int _Index) 
{
	if (nullptr == m_pSRV)
	{
		BOOM;
	}

	switch (_Type)
	{
	case Shader::SHT_VS:
		GraphicDevice::MainContext()->VSSetShaderResources(_Index, 1, &m_pSRV);
		break;
	case Shader::SHT_HS:
		GraphicDevice::MainContext()->HSSetShaderResources(_Index, 1, &m_pSRV);
		break;
	case Shader::SHT_DS:
		GraphicDevice::MainContext()->DSSetShaderResources(_Index, 1, &m_pSRV);
		break;
	case Shader::SHT_GS:
		GraphicDevice::MainContext()->GSSetShaderResources(_Index, 1, &m_pSRV);
		break;
	case Shader::SHT_PS:
		GraphicDevice::MainContext()->PSSetShaderResources(_Index, 1, &m_pSRV);
		break;
	default:
		BOOM;
		break;
	}


}
//
//void HRENDERTARGET::DebugRender(HVEC4 Pos, HVEC4 Size)
//{
//	H3DDEBUG::DrawTex()
//}

void RenderTarget::Copy(RenderTarget* _Other)
{

}