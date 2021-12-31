#pragma once
#include "Component.h"

#include <d3d11.h>

#define LIGHTMAX 512


// �����Ǿ�� �Ѵ�.
class RenderTarget;
class DepthStencilBuffer;
class RenderManager;
class Light : public Component
{
public:
	enum LIGHTTYPE
	{
		LT_DIR,
		LT_POINT,
	};

public:
	friend RenderManager;

public:
	struct LightData
	{
		// ���� ���δ� ǥ���Ϸ��� ��������Ƿ�
		Vector4 Color; // ���� ����
		Vector4 LightPos; // ���� ��ġ (�𷺼� ����Ʈ�� �ǹ̰� ����)
		Vector4 LightDir; // ���� �ٶ󺸴� ����(����Ʈ ����Ʈ�� �׶��׶����� ���� �𷺼��̸� �׻� �Ȱ���)
		Vector4 LightDirInv; // -LightDir (������Ʈ ������Ŀ��� L)
		//HVEC4 ViewLightPos; // ���� ��ġ (�𷺼� ����Ʈ�� �ǹ̰� ����)
		//HVEC4 ViewLightDir; // ���� ��ġ (�𷺼� ����Ʈ�� �ǹ̰� ����)
		//HVEC4 ViewLightDir; // ���� ��ġ (�𷺼� ����Ʈ�� �ǹ̰� ����)
		float Range; // ����
		float DiffPower; // ���� ���� // ���������� �������
		float SpecPower; // ���� ���� // ���� �ٶ󺸴� ����� ���� 
		int Type;
		int SpecPow;
		int temp1;
		int temp2;
		int temp3;
	};

	// �ظ��ϸ� int �ϳ� �־ 16����Ʈ�� ���弼��.
	struct ALLLIGHTDATA
	{
		LightData ArrData[LIGHTMAX];
		int LightSettingData[4];
	};


	// �̳༮�� ����������� �޴´�.
	unsigned int m_Index;
	std::set<int> m_GroupList;

	// ���� 2�� 3�� 5�� ���� �׷��� ����ϴ�.
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
	void Init() override;

private:
	Light::LightData m_LightData;

public:
	void RenderBefore() override;
	void Update() override;

public:
	void SetLightType(LIGHTTYPE _Light)
	{
		m_LightData.Type = (int)_Light;
	}

	void SetRange(float _Value)
	{
		m_LightData.Range = _Value;
	}

	void SetSpecPow(int _Value)
	{
		m_LightData.SpecPow = _Value;
	}

	void SpecPower(float _Value)
	{
		m_LightData.SpecPower = _Value;
	}


	void SetDiffPow(float _Value)
	{
		m_LightData.DiffPower = _Value;
	}

	void SetDiffPowMul(float _Value)
	{
		m_LightData.DiffPower *= _Value;
	}

public:
	class ShadowData
	{
	public:
		Matrix LightVP;		//����Ʈ ����Ʈ��� 
		Matrix CamInvView;
		Vector4 m_ShadowData;
	};

	HPTR<RenderTarget> m_ShadowTarget;
	HPTR <DepthStencilBuffer> m_DepthBuffer;

	ShadowData m_ShadowData;
	void ShadowUpdate();

	Matrix m_VIEW;
	Matrix m_PROJ;
	Matrix m_VIEWTRANSPOSE;
	Matrix m_PROJTRANSPOSE;
	Matrix m_VP;
	float m_Width, m_Height, m_Near, m_Far;

	//HPTR<Texture> m_BoneTex;
	

	D3D11_VIEWPORT m_LightViewPort;

	Matrix PMAT() { return m_PROJ; }
	Matrix VMAT() { return m_VIEW; }
	Matrix VPMAT() { return m_VP; }


public:
	Light();
	~Light();
};

