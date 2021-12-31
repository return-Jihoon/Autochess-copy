#pragma once
#include "SubTransform.h"
#include "Camera.h"
#include "Actor.h"
#include "Transform.h"
#include "RENDERPath.h"
#include "RenderHeader.h"





// �̰� ��ӹ޾Ƽ� ������� �ϸ� �ȵ˴ϴ�.
class Camera;
class Mesh;
class Light;
class Renderer : public SubTransform
{
public:
	class HRENDERDATA : public Reference
	{
	public:
		Renderer*			m_Parent;
		
		int		VBIndex;
		int		IBIndex;
		HPTR<Mesh>			m_Mesh; // ��ǲ �����.
		HPTR<RenderPath>	m_Path; // ��ǲ �����.

		std::vector<DrawIndex> m_Index;
		std::vector<HPTR<RenderPath>> m_Draw;

		bool m_bShadow;
		bool m_bShadowAni;


		HRENDERDATA(Renderer* _Parent,
		unsigned int _VBIndex,
		unsigned int _IBIndex,
		HPTR<Mesh> _Mesh, HPTR<RenderPath> _Path) :
			m_Parent(_Parent),
			m_Mesh(_Mesh),
			m_Path(_Path), m_bShadow(false), m_bShadowAni(false)
		{

		}

	};

public:
	// ���漱��� ������ ���ÿ� �ȴ�.
	friend class RenderManager;

public:
	virtual void Init();

private:
	std::vector<HPTR<HRENDERDATA>> m_AllRenderData;

	int m_Order;

	int GetOrder()
	{
		return m_Order;
	}

	void SetOrder(int _Order) {
		m_Order = _Order;
	}

protected:
	// ���� 10�� �ִ�.
	// �� 1 2 3�� ���� ������ �޾ƿ�.
	MatrixData m_MatData;

public:
	const MatrixData& GetMatrixData()
	{
		return m_MatData;
	}

	HRENDERDATA* GetRenderData(int _Path)
	{
		return m_AllRenderData[_Path];
	}

public:
	virtual void UpdateSubTrans(const HPTR<Camera>& _Cam);
	virtual void UpdateShadowTrans(const HPTR<Light>& _Light);

public:
	HRENDERDATA* RenderData(const wchar_t* _Mesh, const wchar_t* _Path, unsigned int _VBIndex = 0, unsigned int _IBIndex = 0);

protected:
	// ������ ���������� �̰� ������ �����ϰ� �Ұ��̴�.
	virtual void RenderUpdate() {};
	virtual void RenderDataUpdate(const HPTR<Camera>& _CAM, HRENDERDATA* _Data) {}
	virtual void Render(const HPTR<Camera>& _CAM);
	virtual void TextRenderUpdate() {};

public:
	void DataCreate(int _Order = 0);

public:
	template<typename T>
	void CreateCB(const wchar_t* _Name, const T& _CopyData) { CreateCB<T>(0, _Name, _CopyData); }
	
	void LinkCB(const wchar_t* _Name, void* _LinkData) { LinkCB(0, _Name, _LinkData); }
	void LinkTexture(const wchar_t* _Name, const wchar_t* _TexName) { LinkTexture(0, _Name, _TexName); }
	void LinkSampler(const wchar_t* _Name, const wchar_t* _SmpName) { LinkSampler(0, _Name, _SmpName); }

	template<typename T>
	void CreateCB(int _PathIndex, const wchar_t* _Name, const T& _CopyData)
	{
		if (false == m_AllRenderData[_PathIndex]->m_Path->IsCB(_Name))
		{
			BOOM;
		}

		m_AllRenderData[_PathIndex]->m_Path->CBInfoStart = m_AllRenderData[_PathIndex]->m_Path->m_CBInfoSheet.find(_Name);

		int NewSize = m_AllRenderData[_PathIndex]->m_Path->CBInfoStart->second->m_Data.m_Size;

		if (NewSize != sizeof(T))
		{
			BOOM;
		}

		if (nullptr == m_AllRenderData[_PathIndex]->m_Path->CBInfoStart->second->m_SetData)
		{
			m_AllRenderData[_PathIndex]->m_Path->CBInfoStart->second->m_Data.m_CBType = Shader::CBTYPE::NEW;
			m_AllRenderData[_PathIndex]->m_Path->CBInfoStart->second->m_SetData = new char[NewSize];
		}
				

		memcpy_s(m_AllRenderData[_PathIndex]->m_Path->CBInfoStart->second->m_SetData, sizeof(T), (void*)&_CopyData, sizeof(T));
	}

	void LinkCB(int _PathIndex, const wchar_t* _Name, void* _LinkData);
	void LinkTexture(int _PathIndex, const wchar_t* _Name, const wchar_t* _TexName);
	void LinkSampler(int _PathIndex, const wchar_t* _Name, const wchar_t* _SmpName);

public:
	void SceneChangeStart() override;

public:
	Renderer();
	~Renderer();
};

