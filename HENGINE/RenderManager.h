#pragma once
#include "Light.h"
#include "Camera.h"
#include "Renderer.h"
#include <map>
#include <vector>

class Mesh;
class RenderManager;
class Instancing : public Reference
{
public:
	friend RenderManager;

private:
	RenderPath			m_RenderPath;
	HPTR<Mesh>			m_HMESH;

public:
	void SetRenderPath(const RenderPath& _RenderPath) {
		m_RenderPath = _RenderPath;
	}

	RenderPath& GetRenderPath() 
	{
		return m_RenderPath;
	}

	template<typename T>
	void PushData(const T& _Data) 
	{
		m_HMESH->INSTBUFFER()->PushData(_Data);
	}

	void UpdateInstData() 
	{
		m_HMESH->INSTBUFFER()->UpdateInstData();
	}

	void Render() 
	{
		m_RenderPath.Update();
		m_HMESH->UpdateAllVB();
		m_HMESH->UpdateIB(0);
		m_HMESH->RenderInstancing(0);
		m_HMESH->INSTBUFFER()->ResetDataCount();
	}



public:
	void SetMesh(const wchar_t* _Name);
};

// HCAM�� ����� ���� � ������ �η��鸸 �����.
class Camera;
class Light;
class Scene;
class Renderer;
class RenderManager
{
public:
	static void LightCBInit();

public:
	enum GSORTTYPE
	{
		// ī�޶� ����ؼ� ó���ؾ� �Ѵ�.
		// ī�޶� �����̸� �ǹ̰� ����.
		GT_NONE, // ���̴����� ���� ó�� �ϰڴ�.
		GT_Z, // Z�� �����ض�.
		GT_Y,
		GT_X, 
		GT_CAMZ, // VIEW����� ������ ���¿����� ��.
		GT_CAMY,
		GT_CAMX,
		GT_MAX,
	};

public:
	friend Camera;
	friend Light;
	// ���� �༮���� ���⿡ FRIEND
	// 3DMESHRENDER���� �༮���� FRIEND�ɸ� �� �߸�.
	// SOLID �� ������ ������Ģ�� ����� ���°�.
	friend Renderer;
	friend Scene;

private:
	Scene* m_Scene;

private:
	// CAM
	// �ʰ� ����Ʈ�� ������ �ִ� ���� ��Ƽ���̶��
	// Ű�� ����Ʈ
	// ��Ƽ���� Ű�� ��ĥ�� �ִ� ���̴�.
	// ������ ������Ʈ�� ������ �浹�� ��������
	// ���̶� ���Ͱ� �ִ�.
	// ���Ͷ� �浹�� �ִ� ���߿���
	// ���� ������ �ϰ� �ʹ�.

	//      
	std::map<int, std::list<HPTR<Camera>>>::iterator CamGroupFinder;
	std::map<int, std::list<HPTR<Camera>>> m_CAMLIST;
	std::map<int, GSORTTYPE> m_SORTTYPE;

	std::list<HPTR<Camera>>::iterator m_ALLCAMSTART;
	std::list<HPTR<Camera>>::iterator m_ALLCAMEND;
	std::list<HPTR<Camera>> m_ALLCAMLIST;


	std::list<HPTR<Camera>>::iterator CamStart;
	std::list<HPTR<Camera>>::iterator CamEnd;

	std::map<int, std::list<HPTR<Light>>>::iterator LightGroupFinder;
	std::map<int, std::list<HPTR<Light>>> m_LIGHTLIST;

	static Light::ALLLIGHTDATA m_ALLLIGHTDATA;
	static std::vector<HPTR<ConstantBuffer>> m_LIGHTCBLIST;

	std::map<int, std::list<HPTR<Renderer>>>::iterator RenderGStart;
	std::map<int, std::list<HPTR<Renderer>>>::iterator RenderGEnd;

	std::list<HPTR<Renderer>>::iterator RenderStart;
	std::list<HPTR<Renderer>>::iterator RenderEnd;
	std::map<int, std::list<HPTR<Renderer>>> m_RenderList;

	std::list<Renderer::HRENDERDATA*>::iterator RenderDataStart;
	std::list<Renderer::HRENDERDATA*>::iterator RenderDataEnd;

	std::map<int, std::list<Renderer::HRENDERDATA*>>::iterator RenderForwardGStart;
	std::map<int, std::list<Renderer::HRENDERDATA*>>::iterator RenderForwardGEnd;
	std::map<int, std::list<Renderer::HRENDERDATA*>> m_FORWARDRenderList;

	std::map<int, std::list<Renderer::HRENDERDATA*>>::iterator RenderDeferredGStart;
	std::map<int, std::list<Renderer::HRENDERDATA*>>::iterator RenderDeferredGEnd;
	std::map<int, std::list<Renderer::HRENDERDATA*>> m_DEFERREDRenderList;



	///////////////////////////////////////////// CAM
private:
	void PushCamera(const HPTR<Camera>& _CAM);

	/////////////////////////////////////////////// LIGHT
private:
	void PushLight(const HPTR<Light>& _Light);

private:
	// ����
	// std::list<HPTR<HRENDER>> Z���� ���� �������ַ��� �ϴ°�. 

private:
	void PushRender(Renderer* _RENDER);
	void PushForwardender(Renderer::HRENDERDATA* _RENDER);
	void PushDeferredRender(Renderer::HRENDERDATA* _RENDER);

	void PopForwardender(Renderer::HRENDERDATA* _RENDER);

public:
	void Render();
	void Release();
	void OverRelease();
	

	// �����Լ�.
public:

	static bool CamSort(const HPTR<Camera>& _Left, const HPTR<Camera>& _Right);
	static bool ZSort(const HPTR<Renderer>& _Left, const HPTR<Renderer>& _Right);
	static bool YSort(const HPTR<Renderer>& _Left, const HPTR<Renderer>& _Right);
	static bool XSort(const HPTR<Renderer>& _Left, const HPTR<Renderer>& _Right);
	static bool(*SortFunc[GT_MAX])(const HPTR<Renderer>&, const HPTR<Renderer>&);

/////////////////////////// Inst;

private:
	// �ν��Ͻ��� ���� ���ӵ��� �ʴ´�.
	// �׷��� stati
	static std::map<std::wstring, HPTR<Instancing>>::iterator FindInstIter;

	static std::map<std::wstring, HPTR<Instancing>>::iterator StartInst;
	static std::map<std::wstring, HPTR<Instancing>>::iterator EndInst;
	static std::map<std::wstring, HPTR<Instancing>> m_InstMap;

public:
	template<typename T>
	static void PushData(const wchar_t* _Name, const T& _Data)
	{
		// �Ź� ������ ���������� ã�ƾ� ���ϴ°�.
		HPTR<Instancing> pInst = FindInstancing(_Name);

		if (nullptr != pInst)
		{
			BOOM;
		}
		pInst->PushData<T>(_Data);
	}

	static HPTR<Instancing> FindInstancing(const wchar_t* _Name)
	{
		FindInstIter = m_InstMap.find(_Name);

		if (FindInstIter == m_InstMap.end())
		{
			return nullptr;
		}
		return FindInstIter->second;
	}


	static HPTR<Instancing> CreateInstancing(const wchar_t* _Name
		, const wchar_t* _Mesh
		, unsigned int _InstCount = 1000)
		// �ڵ�Ȯ���ϰ� ����ڴ�.
	{
		HPTR<Instancing> pInst = FindInstancing(_Name);

		if (nullptr != pInst)
		{
			BOOM;
		}

		pInst = new Instancing();
		pInst->SetMesh(_Mesh);

		if (nullptr == pInst->m_HMESH->INSTBUFFER())
		{
			BOOM;
		}

		m_InstMap.insert(std::map<std::wstring, HPTR<Instancing>>::value_type(_Name, pInst));

		return pInst;
	}

	static HPTR<Instancing> CreateInstancing(const wchar_t* _Name
		, const wchar_t* _Mesh
		, const RenderPath& _Path
		, unsigned int _InstCount = 1000)
		// �ڵ�Ȯ���ϰ� ����ڴ�.
	{
		HPTR<Instancing> pInst = FindInstancing(_Name);

		if (nullptr != pInst)
		{
			BOOM;
		}

		pInst = new Instancing();
		pInst->SetMesh(_Mesh);
		pInst->SetRenderPath(_Path);

		if (nullptr == pInst->m_HMESH->INSTBUFFER())
		{
			BOOM;
		}

		m_InstMap.insert(std::map<std::wstring, HPTR<Instancing>>::value_type(_Name, pInst));

		return pInst;
	}

public:
	void LightSetting(int _Order, HPTR<Camera>& _Cam);
	void ShadowRender(int _Order, HPTR<Camera>& _Cam);
	void LightRender(HPTR<Camera>& _Cam);
	

public:
	RenderManager(Scene* _Scene);
	~RenderManager();
};