#include "SpriteRender.h"
#include "Mesh.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "SamplerState.h"
#include "Sprite.h"
#include "Blend.h"
#include "DepthStencilState.h"
#include "RasterizerState.h"

#include "Renderer.h"

SpriteRender::SpriteRender() : m_Sprite(nullptr), m_Vec(0.0f), m_SpriteIndex(0), m_UIData(1.0f)
{
}


SpriteRender::~SpriteRender()
{
}

//void SpriteRenderer::Init()
//{
//	//RenderData(L"DTEXMESH", L"BASESPRITEPATH");
//}
void SpriteRender::Init()
{
	Renderer::Init();
}

void SpriteRender::DataCreate(int _Order)
{
	Renderer::DataCreate(_Order);


	//RenderData(L"DTEXMESH", L"BASESPRITEPATH", 0, 0);

	//// TEX(L"PS_MAPTEX", L"BUMPTEST.png");
	//// TEX(L"PS_BUMPTEX", L"BUMPTEST_N.png");
	
	
	//LinkSampler(L"PS_LSMP", L"LSMP");
	//LinkSampler(L"PS_PSMP", L"PSMP");

	//m_Vec.x = 1.0f;
	//LinkCB(L"UIDATA", &m_Vec);

}

void SpriteRender::UpdateSubTrans(const HPTR<Camera>& _Cam)
{
	m_UIData.x = 1.0f;

	m_MatData.ARRMAT[HMAT_WORLD] = GetWorldMatrix();
	m_MatData.ARRMAT[HMAT_SCALE] = m_ScaleMat;

	if (true == m_BillBoard)
	{
		
		m_MatData.ARRMAT[HMAT_VIEW] = _Cam->GetViewMatrix();
		m_MatData.ARRMAT[HMAT_PROJ] = _Cam->PMAT();

		Vector4 Pos = m_MatData.ARRMAT[HMAT_WORLD].ArrVec[3];

		m_MatData.ARRMAT[HMAT_WORLD] = m_MatData.ARRMAT[HMAT_VIEW];
		m_MatData.ARRMAT[HMAT_WORLD].ArrVec[3] = Vector4::BLACK;
		m_MatData.ARRMAT[HMAT_WORLD].Inverse();

		m_MatData.ARRMAT[HMAT_WORLD] = m_MatData.ARRMAT[HMAT_SCALE] * m_MatData.ARRMAT[HMAT_WORLD];
		m_MatData.ARRMAT[HMAT_WORLD].ArrVec[3] = Pos;

		m_MatData.CAMPOS = m_MatData.ARRMAT[HMAT_VIEW].MulOne(_Cam->GetTransform()->GetPosition());
		m_MatData.CAMPOS.w = 1.0f;
		// m_MatData.LIGHTDATA.x = (float)m_LightMode;
		m_MatData.CalSubTrans();
		m_MatData.AllTP();
	}
	else 
	{
		m_MatData.ARRMAT[HMAT_VIEW] = _Cam->GetViewMatrix();

		m_MatData.ARRMAT[HMAT_PROJ] = _Cam->PMAT();
		m_MatData.CAMPOS = m_MatData.ARRMAT[HMAT_VIEW].MulOne(_Cam->GetTransform()->GetPosition());
		m_MatData.CAMPOS.w = 1.0f;
		// m_MatData.LIGHTDATA.x = (float)m_LightMode;
		m_MatData.CalSubTrans();
		m_MatData.AllTP();
	}



	// m_MatData.ARRMAT[HMAT_WVP] = W * V * P;
}


void SpriteRender::SetSprite(const wchar_t* _SpriteName, int _SpriteIndex)
{
	m_SpriteIndex = _SpriteIndex;
	m_Sprite = Resources::Find<Sprite>(_SpriteName);

	//LinkTexture(L"PS_MAPTEX", _SpriteName);
	
	//CreateCB(L"VS_CUTDATA", m_Sprite->GetCutData(m_SpriteIndex));
	//LinkCB(L"VS_CUTDATA", &m_Sprite->GetCutData(m_SpriteIndex));
	
	m_Vec = m_Sprite->GetCutData(m_SpriteIndex);

	m_LastIdx = m_Sprite->GetLastIdx();

	// TEX()
}

void SpriteRender::SetSpriteIdx(int _SpriteIndex)
{
	m_SpriteIndex = _SpriteIndex;

	m_Vec = m_Sprite->GetCutData(_SpriteIndex);

	/*if (nullptr == m_Sprite)
	{
		BOOM;
	}*/
	//LinkCB(L"VS_CUTDATA", &m_Sprite->GetCutData(m_SpriteIndex));
	//CreateCB(L"VS_CUTDATA", m_Sprite->GetCutData(m_SpriteIndex));
	//LinkCB(L"VS_CUTDATA", &m_Sprite->GetCutData(m_SpriteIndex));
}

void SpriteRender::CalCutData(int _SpriteIndex)
{
	//m_SpriteIndex = _SpriteIndex;

	m_Vec = m_Sprite->GetCutData(_SpriteIndex);
}