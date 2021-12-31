#pragma once
#include "EngineMeshData.h"
#include "GraphicDevice.h"
#include <vector>
#include "Texture.h"


// �̳༮�� ����Ÿ�� �ϳ�
class RenderTarget : public Resources
{
private:
	friend class MultiRenderTarget;

	HPTR<Texture> m_Tex;
	ID3D11RenderTargetView* m_pRTV;   // ��ȭ�� 
	ID3D11ShaderResourceView* m_pSRV;   // ��ȭ�� 
	Vector4 m_ClearColor;
	

public:
	HPTR<Texture> GetTex() {
		return m_Tex;
	}

	// ��� ����� ���ô�.
	// _eFormat 32��Ʈ png
	// _eFormat 32323232 png
	bool Create(Vector4 _ClearColor, UINT _W, UINT _H, DXGI_FORMAT _eFormat, UINT _BindFlag);
	void OmSet(ID3D11DepthStencilView* _pDSV);
	void ShaderUpdate(Shader::SHADERTYPE _Type, int _Index);
	void Copy(RenderTarget* _Other);
	// void DebugRender(HVEC4 Pos, HVEC4 Size);

public:
	void Clear();

public:
	RenderTarget();
	~RenderTarget();
};

