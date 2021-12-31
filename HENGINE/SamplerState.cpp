#include "SamplerState.h"



SamplerState::SamplerState() : m_pState(nullptr)
{
}


SamplerState::~SamplerState()
{
	if (nullptr != m_pState)
	{
		m_pState->Release();
		m_pState = nullptr;
	}
}

bool SamplerState::Create()
{
	// Min Mag Mip�� �� ����ؼ� �������Ͷ�
	// Min Mag Mip�Ȼ�������� �˾Ƽ� �Ȼ���ϳ� �˾Ƽ� ���� �����ò�.
	m_Decs.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT;
	// D3D11_FILTER::D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR
	// m_Decs.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT;
	// ����
	// uv �ѹ��� 
	m_Decs.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	m_Decs.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	m_Decs.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;

	// D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_BORDER
	memcpy_s(m_Decs.BorderColor, sizeof(Vector4), &Vector4::RED, sizeof(Vector4));

	// ����
	// ������ ���Ѵ�.
	// �ʿ����. ��??? ������Ҳ��ϱ�.
	m_Decs.ComparisonFunc = D3D11_COMPARISON_NEVER;
	m_Decs.MaxAnisotropy = 0;
	m_Decs.MinLOD = -FLT_MAX;
	m_Decs.MaxLOD = FLT_MAX;

	m_Decs.MipLODBias = 1.0F;

	return Create(m_Decs);
}

bool SamplerState::Create(const D3D11_SAMPLER_DESC& _Decs)
{
	if (&m_Decs != &_Decs)
	{
		m_Decs = _Decs;
	}

	if (S_OK != GraphicDevice::MainDevice()->CreateSamplerState(&m_Decs, &m_pState))
	{
		BOOM;
		return false;
	}

	return true;
}

void SamplerState::Update(Shader::SHADERTYPE _ShaderType, int _SetIndex)
{
	if (nullptr == m_pState)
	{
		BOOM;
	}

	// _SetIndex ���õǴ� ��ġ
	// �� ��ġ���� �������� � �����ҷ�????

	switch (_ShaderType)
	{
	case Shader::SHT_VS:
		GraphicDevice::MainContext()->VSSetSamplers(_SetIndex, 1, &m_pState);
		break;
	case Shader::SHT_HS:
		GraphicDevice::MainContext()->HSSetSamplers(_SetIndex, 1, &m_pState);
		break;
	case Shader::SHT_DS:
		GraphicDevice::MainContext()->DSSetSamplers(_SetIndex, 1, &m_pState);
		break;
	case Shader::SHT_GS:
		GraphicDevice::MainContext()->GSSetSamplers(_SetIndex, 1, &m_pState);
		break;
	case Shader::SHT_PS:
		GraphicDevice::MainContext()->PSSetSamplers(_SetIndex, 1, &m_pState);
		break;
	default:
		BOOM;
		break;
	}

}