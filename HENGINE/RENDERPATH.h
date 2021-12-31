#pragma once
#include <vector>
#include "Mesh.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Texture.h"
#include "SamplerState.h"
#include "Blend.h"
#include "DepthStencilState.h"
#include "RasterizerState.h"
#include "ConstantBuffer.h"
#include <unordered_map>

// ���� -> ī�޶� 

// �Ž��� �־ �������� �ȴ�.

// ���̶� �ᱹ ���� ���õ� ����.
// ���� -> (�ؽ�ó)

// �Ž��� 

// �����н��� ���׸��� ���� ��Ȱ��
// � ���� ������ �Ұ��̳ĸ� ó���ϰ� �Ǵµ�
// ������ۿ� �ؽ�ó �̷� ���õ� ������
// ��� ������ ������ �ؽ��� �ٸ��ų�
// �����н��� ó���Ҽ� �ְ� �����
// �����е��� ���� ����� �ްų� �׷��ٸ�
// �� ����� �̿��ؼ� ������ ��.

// ������ �ش��Ѵ�. ��Ƽ���� ��Ƽ���� ���׸���
// ���׸��� ���ִ� �����н��� ������ �ʿ�� ����.
enum RENDERTYPE
{
	RT_FORWARD,
	RT_DEFERRED,
};

enum LIGHTMODE
{
	VTX,
	PIX,
};

enum BUMPMODE
{
	BUMPNONE,
	BUMPOK,
};

class Renderer;
class Shader;
class Texture;
class RenderPath : public Resources
{
private:
	friend Renderer;

public:
	Renderer* m_Parent;
	RENDERTYPE m_Type;
	LIGHTMODE m_LIGHT;
	BUMPMODE m_BUMP;

private:
	class TextureInfo : public Reference
	{
	public:
		Shader::TEXDATA m_Data; 
		HPTR<Texture> m_Tex;
		ID3D11ShaderResourceView* m_pSRV;
		void(TextureInfo::*ShUpdateFunc)();

	public:
		void Init();
		void Update();
		void VSUpdate();
		void HSUpdate();
		void DSUpdate();
		void GSUpdate();
		void PSUpdate();

	public:
		TextureInfo(const Shader::TEXDATA& _Data) : m_Data(_Data), m_Tex(nullptr)
		{
		}

		TextureInfo(const Shader::TEXDATA& _Data, HPTR<Texture> _Tex) : m_Data(_Data), m_Tex(_Tex)
		{
			Init();
		}
	};

	class ConstBufferInfo : public Reference
	{
	public:
		Shader::CBDATA m_Data;
		D3D11_MAPPED_SUBRESOURCE m_tMapSub;
		void(ConstBufferInfo::*ShUpdateFunc)();
		HPTR<D3DBuffer> m_H3DBUFFER;
		ID3D11Buffer* m_Buffer;

		bool IsChange;
		void* m_SetData;

		void Init();
		void Update();
		void VSUpdate(); 
		void HSUpdate(); 
		void DSUpdate(); 
		void GSUpdate(); 
		void PSUpdate(); 

	public:
		ConstBufferInfo() : IsChange(true) 
		{

		};

		~ConstBufferInfo() 
		{
			if (m_Data.m_CBType == Shader::CBTYPE::NEW)
			{
				delete[] (char*)m_SetData;
			}
		};
	};

	class SamplerInfo : public Reference
	{
	public:
		Shader::SMPDATA m_Data;
		HPTR<SamplerState> m_Smp;
		void(SamplerInfo::*ShUpdateFunc)();
		ID3D11SamplerState* m_pState;

		void Init();
		void Update();
		void VSUpdate();
		void HSUpdate();
		void DSUpdate();
		void GSUpdate();
		void PSUpdate();
	};

private:
	bool m_Original;

	HPTR<Blend>				m_BLEND;
	HPTR<DepthStencilState>				m_DSSTATE;
	HPTR<RasterizerState>				m_RSSTATE;
	D3D11_PRIMITIVE_TOPOLOGY	m_DrawMode;

	std::vector<Shader*> m_AllShader;

	// HSHADER::SHADERTYPE;
	// ���ؽ� ���̴���
	// 0�� ���Կ�

	// � ������۸� ������
	// �������� ���õǴ� ������ ����� ���� �Ѵ�.
	std::unordered_map<std::wstring, HPTR<ConstBufferInfo>>::iterator CBInfoStart;
	std::unordered_map<std::wstring, HPTR<ConstBufferInfo>>::iterator CBInfoEnd;
	std::unordered_map<std::wstring, HPTR<ConstBufferInfo>> m_CBInfoSheet;

	std::unordered_map<std::wstring, HPTR<TextureInfo>>::iterator TexInfoStart;
	std::unordered_map<std::wstring, HPTR<TextureInfo>>::iterator TexInfoEnd;
	std::unordered_map<std::wstring, HPTR<TextureInfo>> m_TexInfoSheet;

	std::unordered_map<std::wstring, HPTR<SamplerInfo>>::iterator SmpInfoStart;
	std::unordered_map<std::wstring, HPTR<SamplerInfo>>::iterator SmpInfoEnd;
	std::unordered_map<std::wstring, HPTR<SamplerInfo>> m_SmpInfoSheet;

	// ���ð� ������ ����� �մϴ�.
	// ���þ��س��ų� ���� �ȵ� �༮�� ������ ��Ʈ�� ���̴�.

public:
	void SetRenderType(RENDERTYPE _Type) 
	{
		m_Type = _Type;
	}

	bool IsCB(const wchar_t* _Name) 
	{
		return m_CBInfoSheet.end() != m_CBInfoSheet.find(_Name);
	}
	bool IsTEX(const wchar_t* _Name) 
	{
		return m_TexInfoSheet.end() != m_TexInfoSheet.find(_Name);
	}
	bool IsSMP(const wchar_t* _Name) {
		return m_SmpInfoSheet.end() != m_SmpInfoSheet.find(_Name);
	}

	bool IsOriginal() {
		return m_Original;
	}

	void SetDrawMode(D3D11_PRIMITIVE_TOPOLOGY _DrawMode) 
	{
		m_DrawMode = _DrawMode;
	}

	void SetBlend(const wchar_t* _Name);
	void SetDSState(const wchar_t* _Name);
	void SetRSState(const wchar_t* _Name);
	void SetVtxShader(const wchar_t* _Name);
	void SetPxlShader(const wchar_t* _Name);

private:
	void ShaderSetting(Shader* _Shader);

public:
	void Init(Renderer* _Parent);

public:
	void Update();
	void LinkCB(const wchar_t* _Name, void* _LinkData);
	void LinkTEX(const wchar_t* _Name, const wchar_t* _TexName);
	void LinkSMP(const wchar_t* _Name, const wchar_t* _SmpName);
	void LinkTEX(const wchar_t* _Name, HPTR<Texture> _Tex);

public:
	HPTR<RenderPath> Clone();

	RenderPath();
	~RenderPath();
};
