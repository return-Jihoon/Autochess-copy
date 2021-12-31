#include "RectRender.h"
#include "Mesh.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "SamplerState.h"
#include "Sprite.h"
#include "Blend.h"
#include "RasterizerState.h"
#include "DepthStencilState.h"

RectRender::RectRender()
{
}


RectRender::~RectRender()
{
}


void RectRender::Init()
{
	Renderer::Init();

	m_COLOR = 1.0f;

	m_SMP = Resources::Find<SamplerState>(L"LSMP");
	m_HMESH = Resources::Find<Mesh>(L"DTEXMESH");
	m_HCB = Resources::Find<ConstantBuffer>(L"MATBUF");
	m_HCBCOLOR = Resources::Find<ConstantBuffer>(L"RECTCOLOR");
	m_HVTXSHADER = Resources::Find<VertexShader>(L"COLORRECT.fx");
	m_HPIXSHADER = Resources::Find<PixelShader>(L"COLORRECT.fx");
	m_BLEND = Resources::Find<Blend>(L"DBLEND");
	m_DSSTATE = Resources::Find<DepthStencilState>(L"DDSSTATE");
	m_RSSTATE = Resources::Find<RasterizerState>(L"DRSSTATE");
}

void RectRender::Render(const HPTR<Camera>& _CAM)
{
	DebugCheck();
	// MATW�� �𸥴�.
	UpdateTransform();

	Matrix W = GetWorldMatrix();
	Matrix V = _CAM->GetViewMatrix();
	Matrix P = _CAM->PMAT();

	Matrix WVP = W * V * P;

	Matrix WVPT = WVP;

	WVPT.TransPose();

	// �ִ��� �� ȣ���ϴ� ���� �������̴�.
	m_HCB->DataSetting(&WVPT, sizeof(Matrix));
	m_HCB->Update();
	m_BLEND->Update();
	// �̳༮�� ������Ʈ�� ����� �ȵƴ�.
	// ���� ���µ� �����ƴ�.

	// 5 ~ 15 ��°����

	// 0, 5,
	// 1, 10
	// 1 / 12.0F, 1 / 5.0F

	GraphicDevice::MainContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	// TEXUV = HVEC4(0.0f, 0.0f, 1 / 12.0F, 1 / 5.0F);
	m_HCBCOLOR->DataSetting(&m_COLOR, sizeof(m_COLOR));
	m_HCBCOLOR->Update();

	m_HVTXSHADER->Update();
	m_HPIXSHADER->Update();

	m_SMP->Update(Shader::SHADERTYPE::SHT_PS, 0);

	m_DSSTATE->Update();
	m_RSSTATE->Update();
	m_HMESH->Update(0, 0);
	// ������ �ٸ��κи� �������ش�.
	m_HMESH->Render(0);

}