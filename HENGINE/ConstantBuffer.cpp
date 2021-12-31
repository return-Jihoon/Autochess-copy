#include "ConstantBuffer.h"


ConstantBuffer::ConstantBuffer() : m_uiReg(0), m_bLink(false)
{
}


ConstantBuffer::~ConstantBuffer()
{

	if (m_bLink == false && nullptr != m_Data)
	{
		delete[](char*)m_Data;
		m_Data = nullptr;
	}

}

// ���ÿ� �ΰ��� ��������� �Ѵٸ�????
bool ConstantBuffer::Create(Shader::SHADERTYPE _Shader, size_t _Byte, UINT _Reg)
{
	m_uiReg = _Reg;

	switch (_Shader)
	{
	case Shader::SHT_VS:
		ShUpdateFunc = &ConstantBuffer::VSUpdate;
		break;
	case Shader::SHT_HS:
		ShUpdateFunc = &ConstantBuffer::HSUpdate;
		break;
	case Shader::SHT_DS:
		ShUpdateFunc = &ConstantBuffer::DSUpdate;
		break;
	case Shader::SHT_GS:
		ShUpdateFunc = &ConstantBuffer::GSUpdate;
		break;
	case Shader::SHT_PS:
		ShUpdateFunc = &ConstantBuffer::PSUpdate;
		break;
	default:
		break;
	}

	// �����͸� �����Ҵ����� ������ �ִ´�.
	m_Desc.ByteWidth = (UINT)_Byte;
	m_Data = new char[_Byte];
	// �̰� �׷���ī�尡 �����ұ� �ƴϸ� CPU�� �Ҵ��ұ� �� �̷��͵�
	// �׸��� �����Ҷ� �����Ҽ� �ְ� �Ұž�????
	m_Desc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;

	if (D3D11_USAGE::D3D11_USAGE_DYNAMIC == m_Desc.Usage)
	{
		m_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}

	m_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	if (S_OK != GraphicDevice::MainDevice()->CreateBuffer(&m_Desc, nullptr, &m_Buffer))
	{
		BOOM;
		return false;
	}

	return true;
}

// ����� ���⿡ ���´�.
void ConstantBuffer::DataSetting(void* _pData, UINT _Size) {

	// ���� �ٲܲ���.
	GraphicDevice::MainContext()->Map(m_Buffer,
		0, D3D11_MAP_WRITE_DISCARD, 0, &m_tMapSub);
	// m_tMapSub.pData �׷���ī��� ���ϴ� ��θ� ���´�.

	// ���� �ٲٴ� �۾�
	memcpy_s(m_tMapSub.pData, m_Desc.ByteWidth, _pData, _Size);

	// ������ �ݴ´�.
	GraphicDevice::MainContext()->Unmap(m_Buffer, 0);
}

void ConstantBuffer::DataSetting() 
{
	if (false == m_bLink)
	{
		BOOM;
	}

	GraphicDevice::MainContext()->Map(m_Buffer,
		0, D3D11_MAP_WRITE_DISCARD, 0, &m_tMapSub);
	// m_tMapSub.pData �׷���ī��� ���ϴ� ��θ� ���´�.

	// ���� �ٲٴ� �۾�
	memcpy_s(m_tMapSub.pData, m_Desc.ByteWidth, m_Data, BufferSize);

	// ������ �ݴ´�.
	GraphicDevice::MainContext()->Unmap(m_Buffer, 0);
}

void ConstantBuffer::Update()
{
	(this->*ShUpdateFunc)();
}

void ConstantBuffer::VSUpdate() { GraphicDevice::MainContext()->VSSetConstantBuffers(m_uiReg, 1, &m_Buffer); }
void ConstantBuffer::HSUpdate() { GraphicDevice::MainContext()->HSSetConstantBuffers(m_uiReg, 1, &m_Buffer); }
void ConstantBuffer::DSUpdate() { GraphicDevice::MainContext()->DSSetConstantBuffers(m_uiReg, 1, &m_Buffer); }
void ConstantBuffer::GSUpdate() { GraphicDevice::MainContext()->GSSetConstantBuffers(m_uiReg, 1, &m_Buffer); }
void ConstantBuffer::PSUpdate() { GraphicDevice::MainContext()->PSSetConstantBuffers(m_uiReg, 1, &m_Buffer); }


void ConstantBuffer::Link(void* _Data, unsigned int _Size)
{
	if (nullptr != m_Data)
	{
		delete[] m_Data;
	}

	if (0 >= _Size)
	{
		BOOM;
	}

	if (m_Desc.ByteWidth != _Size)
	{
		// ���� �������� �Ѵ�.
		BOOM;
	}

	m_Data = _Data;
	m_Desc.ByteWidth = _Size;
	BufferSize = _Size;
	m_bLink = true;
}