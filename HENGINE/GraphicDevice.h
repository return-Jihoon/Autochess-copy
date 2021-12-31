#pragma once
#include <Maths.h>
// ������ 10���ʹ� ������ ����ü�� ���������� ���̷�Ʈ�� ���̰� �ֱ� ������
// ������ ��� c++������ stdlib�������� �̹� �� include ���Ա��� �� �Ǿ��ִ�.

#define D3D2

#include <d3d11_4.h> 

#include <d3dcompiler.h> // ���̴���°� �������ϴµ� ���Ǵ� ���
#include <JWindow.h>
#include <map>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")

#ifdef X32
#ifdef DEBUGMODE
#pragma comment(lib, "\\X32\\BASED32.lib")
#elif RELEASEMODE
#pragma comment(lib, "\\X32\\BASER32.lib")
#endif
#elif X64
#ifdef DEBUGMODE
#pragma comment(lib, "\\X64\\BASED64.lib")
#elif RELEASEMODE
#pragma comment(lib, "\\X64\\BASER64.lib")
#endif
#endif


// �׷���ī���� ����� ����ϱ� ���� ���̺귯����
// D3DX�� ����� ��Ƴ��� Ŭ����	
class Window;
class GraphicDevice : public Reference
{
/////////////// static
	// HWINDOW�� ������ ���� ���� ����. 
private:
	static GraphicDevice* m_MainDevice;
	static ID3D11Device* m_pMainDevice; // �׷���ī���� ��� �ڿ��� ���� ������ ���. (o)
	static ID3D11DeviceContext* m_pMainContext; // �׷���ī���� ��� ���꿡 ���� ������ ����Ѵ�.(����) (o)
	static bool m_PathInit;


public:
	static HPTR<GraphicDevice> Inst() 
	{
		return m_MainDevice;
	}

	static ID3D11Device* MainDevice()
	{
		return m_pMainDevice;
	}

	static void MainReset();

	static ID3D11DeviceContext* MainContext()
	{
		return m_pMainContext;
	}

//////////////// MEMBER
private:
	Window* m_TargetWindow;

	UINT m_MQ; // ��Ƽ���ø� ���� �����°�
	UINT m_MC; // ��Ƽ���ø� ���� �����°�
	// �׷���ī�带 ���̷�Ʈ�� ���α׷����ϴ� �Ϳ� ���� 
	// ������ �Ʒ��� �ΰ��� �����͸� ���ؼ� �Ѵ�.
	ID3D11Device* m_pDevice; // �׷���ī���� ��� �ڿ��� ���� ������ ���. (o)
	ID3D11DeviceContext* m_pContext; // �׷���ī���� ��� ���꿡 ���� ������ ����Ѵ�.(����) (o)
	// ���� �������
	// �� ����� �׳� ��ü������ �����Ѵ�.
	IDXGISwapChain* m_pSwapChain; // ���̹��� ������������������ �ܰ迡 �����Ѵ�.

	// ID3D11RenderTargetView* m_pBackBufferView[3]; // ���̹��� ������������������ �ܰ迡 �����Ѵ�.

	ID3D11RenderTargetView* m_pBackBufferView; // ���̹��� ������������������ �ܰ迡 �����Ѵ�.
	ID3D11DepthStencilView* m_pDepthStencilView; // ���̹��� ������������������ �ܰ迡 �����Ѵ�.
	ID3D11Texture2D* m_pDepthStencilTex; // ���̹��� ������������������ �ܰ迡 �����Ѵ�.
	
	

	Vector4 m_BackColor;
	D3D11_VIEWPORT m_ViewPortInfo; // ����Ʈ��Ŀ� ����.

	
	bool m_BaseInit;
	void BaseResInit();

public:
	ID3D11Device* GetDevice()
	{
		return m_pDevice;
	}

	ID3D11DeviceContext* GetContext()
	{
		return m_pContext;
	}

	ID3D11DepthStencilView* GetDSV()
	{
		return m_pDepthStencilView;
	}

public:
	void Init(Window* _TargetWindow);

	void ClearTarget();
	void Present();

private:
	// ���̷�Ʈ x������ �츮�� ���� �����ʿ䰡 ���� ȭ�� ���� �ý����� �������ش�.
	bool CreateSwapChain();
	bool CreateDepthStencilView();
	bool CreateViewPort();

public:
	void DefRenderTargetSetting();
	void DefViewPortSetting();

public:
	GraphicDevice();
	~GraphicDevice();
};

