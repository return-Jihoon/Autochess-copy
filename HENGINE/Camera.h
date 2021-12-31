#pragma once
#include "GraphicDevice.h"
#include "Component.h"
#include <set>
#include "Transform.h"

enum PROJMODE
{
	PM_PERS, // ����
	PM_ORTH //  ����
};

class Light;
class RenderPath;
class Mesh;
class RenderTarget;
class DepthStencilBuffer;
class MultiRenderTarget;
class Camera final : public Component
{
	// �ӽ÷� ����� ���ڽ��ϴ�.
public:
	friend class RenderManager;

private:
	static Camera* m_MainCam;
	static Camera* m_UICam;

public:
	static Camera* GetMainCam() 
	{
		return m_MainCam;
	}

	static Camera* GetUICam()
	{
		return m_UICam;
	}


	static void SetUICam(Camera* _Camera)
	{
		m_UICam = _Camera;
	}

private:
	PROJMODE m_Mode;
	Matrix m_WORLD;
	Matrix m_VIEW;
	Matrix m_PROJ;
	Matrix m_VIEWTRANSPOSE;
	Matrix m_PROJTRANSPOSE;
	Matrix m_VP;


	std::set<int> m_GroupList; // 1 2 3 5
	float m_Fov;
	float m_StartX;
	float m_StartY;
	float m_Width;
	float m_Height;
	float m_Near;
	float m_Far;

	D3D11_VIEWPORT m_CamViewPort;// ����Ʈ��Ŀ� ����.
	// �̳༮�� 0�� �ؽ�ó�� ������ �ָ� �ȴ�.
	HPTR<DepthStencilBuffer> m_DepthBuffer;

	HPTR<RenderTarget>			m_CamTarget;
	HPTR<MultiRenderTarget>	m_DEFERREDTarget;
	HPTR<MultiRenderTarget>	m_LightTarget;

	HPTR<Mesh> m_CamRenderMesh;

	HPTR<RenderPath> m_CamRenderPath;
	HPTR<RenderPath> m_DEFERREDLightPath;
	HPTR<RenderPath> m_LightMergePath;

	Vector4 m_ViewCamPos;

	MatrixData m_DATA;


public:
	HPTR<RenderTarget> CamTarget() {
		return m_CamTarget;
	}
	HPTR<MultiRenderTarget> GetDeferredTarget() {
		return m_DEFERREDTarget;
	}
	HPTR<MultiRenderTarget> GetLightTarget() {
		return m_LightTarget;
	}

	void SetNearValue(float _Near) 
	{
		m_Near = _Near;
	}

	void SetFarValue(float _Far)
	{
		m_Far = _Far;
	}

	void SetViewPortSize(float _PosX, float _PosY, float _SizeX, float _SizeY)
	{
		m_CamViewPort.TopLeftX = _PosX;
		m_CamViewPort.TopLeftY = _PosY;
		m_CamViewPort.Width = _SizeX;
		m_CamViewPort.Height = _SizeY;
	}

	D3D11_VIEWPORT GetViewPort()
	{
		return m_CamViewPort;
	}

	void SetArea(float _Width, float _Height) {
		SetWidth(_Width);
		SetHeight(_Height);
	}

	void SetWidth(float _Width)
	{
		m_Width = _Width;
	}

	void SetHeight(float _Height)
	{
		m_Height = _Height;
	}

	void SetFov(float _Fov) {
		m_Fov = _Fov;
	}

	void SetProjMode(PROJMODE _Mode)
	{
		m_Mode = _Mode;
	}

	

private:
	bool m_IsAllView;
	bool IsAllView()
	{
		return m_IsAllView;
	}


public:
	int m_Order;
	int Order() 
	{
		return m_Order;
	}
	void Order(int _Order);

	void Update();
	

public:
	inline bool IsRender(int _Order) 
	{
		return m_GroupList.find(_Order) != m_GroupList.end();
	}

	// Ž�������� �ǹ̰� ������ ����Ѵ�.
	// �Ű�� �־�.
	// map�� value�� ���� �ڷᱸ��.
	// map<int, ����> 1 �� �ִ� ������Ʈ�� ��.
	// set<int> 1���� �־�? �׷� ����.

	// 1�� �׷��� �����Ѵ�.

	// ī�޶�� ���� � �����׷��� ���� ī�޶����� �˾ƾ� �Ѵ�.

	// �����׷� 1��

	// std::set<std::wstring>
	// FOR ���ͷ����ͷ� FOR�� �������� �ȴ�.
	// UNORDEREDMAP ���� �ȵ�
	// ���ĵ�

	// ������ ������ ����.
	// �����е� ������
	// �̷��ʵ� �ٽô� �������̴�.
	// �����е��� ���� ����.
	// �̷¼� �ڼҼ� ����Ұ��� ������

	// ���� �� ������� -> �̰ź��� 
	// ������ų� <- 
	// �� ����� ���ؼ� ���� �ʴ� ���δ�
	// ���� �����ϱ⿡�� �� �������.
	// ASTAR �̷��� ���� �Ű澵 �ʿ� ����.
	// Ÿ�Ͽ��� ��ã�°��ӵ�.

	// ������ �ٴ��ͼ�
	// ������ ������������.
	// �ֵ��� �ʹ� ���� �����.
	// �����ϴٰ� �����ϸ� ����� �ȴ�.
	// 1��ȿ� �����ؾ� �Ѵ�.
	// ��ȸ�縸 ���� ���� ���̴�.
	// ���� ���� �л����� Ư¡��.
	// ���� ���� �� ����Ų��.

	// ĳ���;ִϸ��̼� ���
	// �ִϸ��̼� FSM ���� �ؾ� �Ѵ�.

	// �ð��� ����.
	// �翬�ϰ� ����� ���� ����
	// ����Ʈ ���� �����
	// ���� ���������
	// ����Ʈ ���������
	// �˰���

	// �̳༮�� �ι� ȣ������� �Ҽ��� �ֳ�.
	template<class... Types>
	void DataCreate(Types&&... _Args)
	{
		PushRenderGroup(_Args...);
		return;
	}

	// ��ǲ�Ŵ��� ��.
	template<class... Types>
	void PushRenderGroup(int _Order, Types&&... _Args)
	{
		if (m_GroupList.find(_Order) != m_GroupList.end())
		{
			BOOM;
			return;
		}

		m_GroupList.insert(_Order);

		PushRenderGroup(_Args...);
	}

	// �̰� ����� ���� �Ѵ�.
	void PushRenderGroup();


public:
	Matrix PMAT() { return m_PROJ; }
	Matrix GetViewMatrix() { return m_VIEW; }
	Matrix VPMAT() {		return m_VP;	}
	//Matrix GetWorldMatrix() { return m_w; }

	// �����϶��� ����
	Vector4 OrthMousePos();
	// ��� �ƴ϶��
	// ���� �����
	// HVEC4 WorldMousePos(float ZDis);

public:
	void Init() override;

	// ���ڰ��� �ϳ��� ���ٸ�
	// 0�� �־��ְڴ�.
	// 1 2 3 4 5 6

public:
	void FORWARDTargetSet();
public:
	void DEFERREDTargetSet();

private:
	void DEFERREDMerge();

	void RenderBefore() override;
	void CamRender();
	void DEFERREDLightRender(HPTR<Light> _Light);

	void CamClear();

public:
	class Filter : public Reference
	{
	public:
		friend Camera;

	protected:
		Camera* m_Cam;

	private:
		void Init(Camera* _Cam) { m_Cam = _Cam; }

	public:
		virtual void InitFilter() = 0 {}
		virtual void MergeBeforeEffect() = 0 {}
		virtual void MergeAfterEffect() = 0 {}

	};

private:
	std::list<HPTR<Filter>> m_Filters;
	// HLIGHT::SHADOWRENDERDATA SData;
public:
	template<typename T>
	HPTR<T> CreateFilter()
	{
		T* NewFilter = new T();
		NewFilter->Init(this);
		NewFilter->InitFilter();
		m_Filters.push_back(NewFilter);
		return NewFilter;
	}

private:
	void MergeBefore();
	void MergeAfter();


public:
	Camera();
	~Camera();
};

