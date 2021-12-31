#include "GridRender.h"
#include "GraphicDebug.h"


GridRender::GridRender()
{
}


GridRender::~GridRender()
{
}
void GridRender::Init() 
{
	Renderer::Init();

	m_Data.Color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Data.Borader = 1.0f;

	RenderData(L"GRIDMESH", L"GRIDPATH");
	LinkCB(L"GRIDDATA", &m_Data);

}
void GridRender::Update() 
{
	// m_Data.Color = HVEC4(1.0f, 0.0f, 0.0f, 1.0f);
}

void GridRender::RenderDataUpdate(const HPTR<Camera>& _CAM, HRENDERDATA* _Data)
{

	float CamPosY = _CAM->GetTransform()->GetPosition().y;
	int Check = (int)_CAM->GetTransform()->GetPosition().y;
	int Count = 0;

	if (10 >= Check)
	{
		Check = 10;
	}

	// 110

	while (Check >= 10)
	{
		++Count;
		Check /= 10;
	}

	Check = 1;

	for (int i = 0; i < Count; i++)
	{
		Check *= 10;
	}

	// 10�϶� 0.5
	// 100    5

	// 
	// 10 - 10
	// 100 - 10
	// 0 ~ 10 5
	// 10 ~ 100 50 - 10
	// 10 �϶� ���� 1
	// 100 �ϴ� 0�� ������� �Ѵ�.

	m_Data.MaxA = (CamPosY - (Check / 10)) / (Check * 10 - (Check * 10 / 10));
	m_Data.MinA = 1.0f - m_Data.MaxA;

	m_Data.Borader = 0.5f;

	m_Data.Step = (float)Check;
	m_Data.CamPos = _CAM->GetTransform()->GetPosition();

}

void GridRender::Render(const HPTR<Camera>& _CAM)
{
	Renderer::Render(_CAM);
}