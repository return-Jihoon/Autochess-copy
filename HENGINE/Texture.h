#pragma once
#include "Resources.h"
#include "Shader.h"
#include <Windows.h>
#include <DirectXTex.h>


#ifdef X32
#ifdef DEBUGMODE
#pragma comment(lib, "DirectXTexD32.lib")
#elif RELEASEMODE
#pragma comment(lib, "DirectXTexR32.lib")
#endif
#elif X64
#ifdef DEBUGMODE
#pragma comment(lib, "DirectXTexD64.lib")
#elif RELEASEMODE
#pragma comment(lib, "DirectXTexR64.lib")
#endif
#endif

class Texture : public Resources
{

private:
	// �̰� �ϴ� ����
	DirectX::ScratchImage m_Image;
	UINT m_Width;
	UINT m_Height;

	ID3D11Resource*		  m_pTex;

	// ����Ÿ�� ���?????
	ID3D11RenderTargetView* m_pRTV;   // ��ȭ�� 
	ID3D11DepthStencilView* m_pDSV;   // ���⿡ ���̹��۸� ������� �ִ�.
	ID3D11ShaderResourceView* m_pSRV; // ���̴��� �������ٶ� �ʿ��� �������̽�

public:
	ID3D11RenderTargetView* GetRTV() {	return m_pRTV;	}
	ID3D11DepthStencilView* GetDSV() { return m_pDSV; }
	ID3D11ShaderResourceView* GetSRV() { return m_pSRV; }

public:
	UINT GetWidth() {
		return m_Width;
	}

	UINT GetHeight() {
		return m_Height;
	}

public:
	void Update(Shader::SHADERTYPE _ShaderType, int _SetIndex);

	// class 
	// {
	// char a;
	// char r;
	// char g;
	// char b;
	// };
	// HVEC4 GetColorToByte(int _X, int _Y);
	Vector4 GetColorToFloat(int _X, int _Y);


	// �� ����Ÿ���� OMSETRENDERTargetVIEW�� ����µ�.
	// ���� ���� �ʾҴµ�. ���̴� ����ְڴٴ� ���� �Ұ����ϴٴ� �̾߱��.
	//ID3D11RenderTargetView* m_pRTV;   // ��ȭ�� 
	//ID3D11DepthStencilView* m_pDSV;   // ���⿡ ���̹��۸� ������� �ִ�.
	//ID3D11ShaderResourceView* m_pSRV; // ���̴��� �������ٶ� �ʿ��� �������̽�

public:
	bool Load();
	bool Create(UINT _W, UINT _H, DXGI_FORMAT _Format, UINT _BindFlag, D3D11_USAGE _eUsage);
	void SetPixel(void* _Data, UINT _ByteSize);
	void Copy(HPTR<Texture> _Other);

private:

	void SettingData(UINT _BindFlag);

public:
	Texture();
	~Texture();
};

