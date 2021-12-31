#pragma once
#include "GraphicDevice.h"
#include "D3DBuffer.h"
#include "Shader.h"

class ConstantBuffer : public D3DBuffer
{
private:
	bool m_bLink;

	Shader::SHADERTYPE m_Shader;
	unsigned int m_uiReg;
	UINT BufferSize;
	D3D11_SUBRESOURCE_DATA m_tSub;
	D3D11_MAPPED_SUBRESOURCE m_tMapSub;
	// 상수버퍼에서 사용될 실제데이터는 이녀석이다.
	void* m_Data;
	void(ConstantBuffer::*ShUpdateFunc)();

public:
	void Reg(unsigned int _uiReg) 
	{
		m_uiReg = _uiReg;
	}

	int Reg()
	{
		return m_uiReg;
	}

	//HSHADER::SHADERTYPE SHADERTYPE(HSHADER::SHADERTYPE _uiReg)
	//{
	//	m_uiReg = _uiReg;
	//}

	int SHADERTYPE()
	{
		return m_uiReg;
	}

public:
	bool Create(Shader::SHADERTYPE _Shader, size_t _Byte, UINT _Reg);

public:
	void Link(void* _Data, unsigned int _Size);

private:
	void VSUpdate();
	void HSUpdate();
	void DSUpdate();
	void GSUpdate();
	void PSUpdate();

public:
	void DataSetting(void* _pData, UINT _Size);
	void DataSetting();
	void Update();


public:
	ConstantBuffer();
	~ConstantBuffer();
};
