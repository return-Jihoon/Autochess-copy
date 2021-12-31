#pragma once
#include "Resources.h"
#include <unordered_map>
#include <unordered_set>

class D3DBuffer;
class Shader : public Resources
{
public:
	enum SHADERTYPE
	{
		SHT_VS,
		SHT_HS,
		SHT_DS,
		SHT_GS,
		SHT_PS,
		SHT_END,
	};

public:
	static unsigned int SizeOfFormat(DXGI_FORMAT _Fmt);

protected:
	static char VERBUFFERTEXT[256];

protected:
	ID3DBlob* m_pBlob; 
	ID3DBlob* m_pErrBlob; 
	unsigned int m_VH; // 5
	unsigned int m_VL; // 0
	SHADERTYPE m_Type;

public:
	// ��� ���� ��ü�� Ŭ������ ��Ű���� �Ѵ�.
	enum CBTYPE
	{
		NONE,
		TRANS, // �̳༮�� Link�� �������� �ڵ����� �Ǵ� ��ũ��
		LIGHT, 
		LINK,
		NEW,
	};

	class CBDATA
	{
	public:
		std::wstring m_Name;
		Shader::SHADERTYPE m_Shader;
		Shader::CBTYPE     m_CBType;
		unsigned int		m_Size;
		unsigned int		m_uiReg;
		// HPTR<H3DBUFFER>     m_H3DBUFFER;
		// ID3D11Buffer*		m_Buffer;
	};

	// ���÷��� �־���� �ȴٴ� ���� �˷��ִ� ������
	class SMPDATA
	{
	public:
		std::wstring m_Name;
		Shader::SHADERTYPE m_Shader;
		unsigned int m_uiReg;
	};

	// �ؽ�ó�� �ʿ��ϴٴ� ���� �˷��ִ� ������.
	class TEXDATA
	{
	public:
		std::wstring m_Name;
		Shader::SHADERTYPE m_Shader;
		unsigned int m_uiReg;
	};

private:
	//static std::map<unsigned int, HPTR<H3DBUFFER>> m_BufferPool[SHADERTYPE::SHT_END];
	//static HPTR<H3DBUFFER> CBBufferCheck(HSHADER::SHADERTYPE _Type, unsigned int _Byte);


private:
	std::unordered_set<int> m_AllCBIndex;
	std::unordered_map<std::wstring, CBDATA> m_AllCB;
	std::unordered_set<int> m_AllSMPIndex;
	std::unordered_map<std::wstring, SMPDATA> m_AllSMP;
	std::unordered_set<int> m_AllTEXIndex;
	std::unordered_map<std::wstring, TEXDATA> m_AllTEX;

public:
	SHADERTYPE ShaderType()
	{
		return m_Type;
	}

	const std::unordered_map < std::wstring, CBDATA>& AllCB()
	{
		return m_AllCB;
	}

	const std::unordered_map < std::wstring, TEXDATA>& AllTEX()
	{
		return m_AllTEX;
	}

	const std::unordered_map < std::wstring, SMPDATA>& AllSMP()
	{
		return m_AllSMP;
	}

public:
	template<typename T>
	void CreateCB(const wchar_t* _Name, UINT _Reg,  CBTYPE _Type = CBTYPE::NONE)
	{
		CreateCB(_Name, (unsigned int)sizeof(T), _Reg, _Type);
	}

public:
	void CreateCB(const wchar_t* _Name, unsigned int _Byte, UINT _Reg, CBTYPE _Type = CBTYPE::NONE);
	void CreateSMPDATA(const wchar_t* _Name, UINT _Reg);
	void CreateTEXDATA(const wchar_t* _Name, UINT _Reg);

	bool IsOver(Shader* _pShader);

public:
	virtual void Update() = 0;

public:
	Shader(SHADERTYPE _Type);
	~Shader();
};

