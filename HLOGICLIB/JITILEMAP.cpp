#include "JITILEMAP.h"
#include <Mesh.h>
#include <ConstantBuffer.h>
#include <VertexShader.h>
#include <PixelShader.h>
#include <SamplerState.h>
#include <Sprite.h>
#include <Blend.h>
#include <DepthStencilState.h>
#include <RasterizerState.h>
#include <RenderManager.h>
#include <InstanceBuffer.h>
#include <RenderManager.h>

void JITILEMAP::HPATHNODE::CalValue(
	JITILEMAP::HPATHNODE* _Parent, HGAMETILE* _Tile, HGAMETILE* _End)
{
	Parent = _Parent;
	Tile = _Tile;

	if (nullptr != _Parent)
	{
		if (_Parent->Tile == _Tile)
		{
			BOOM;
		}
	}

	// ���� 1�ۿ� �ȳ��´�.
	if (nullptr != _Parent)
	{
		H = (float)(abs((_Parent->Tile->Index.ix - Tile->Index.ix)
			+ (_Parent->Tile->Index.iy - Tile->Index.iy)))
			+ _Parent->H;
	}
	else {
		H = 0.0f;
	}
	// �׳� ���� ���� ���ͷ� ���̸� ���߾�� �Ѵ�.
	G = (float)(abs(_End->Index.ix - _Tile->Index.ix) 
		+ abs(_End->Index.iy - _Tile->Index.iy));

	F = H + G;
}

JITILEMAP::JITILEMAP()
{
}


JITILEMAP::~JITILEMAP()
{
}

void JITILEMAP::Init()
{
	// �Ž��� ����Ž��� ������ �Ѵ�.
	// 


	if (nullptr == Resources::Find<VertexShader>(L"TEXSHADERINST.fx"))
	{

		// �ν��Ͻ̿� ���̴�
		HPTR<VertexShader> VTXSH = Resources::Load<VertexShader>(Path::FindPathToString(L"SHADER") + L"\\TEXSHADERINST.fx", 5, 0, "VS_TEX");
		VTXSH->AddLayOut("POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0);
		VTXSH->AddLayOut("TEXCOORD", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, 0);
		VTXSH->AddLayOut("COLOR", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0);

		// 1
		VTXSH->AddLayOut("WVP", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 1/*(����� 1�̶� �ν��Ͻ� ������ �ΰ��̴�.)*/, D3D11_INPUT_PER_INSTANCE_DATA);
		VTXSH->AddLayOut("WVP", 1, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 1/*(����� 1�̶� �ν��Ͻ� ������ �ΰ��̴�.)*/, D3D11_INPUT_PER_INSTANCE_DATA);
		VTXSH->AddLayOut("WVP", 2, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 1/*(����� 1�̶� �ν��Ͻ� ������ �ΰ��̴�.)*/, D3D11_INPUT_PER_INSTANCE_DATA);
		VTXSH->AddLayOut("WVP", 3, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 1/*(����� 1�̶� �ν��Ͻ� ������ �ΰ��̴�.)*/, D3D11_INPUT_PER_INSTANCE_DATA);
		VTXSH->EndLayOut("SPRITEUV", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 1/*(����� 1�̶� �ν��Ͻ� ������ �ΰ��̴�.)*/, D3D11_INPUT_PER_INSTANCE_DATA);
	}


	if (nullptr == Resources::Find<InstanceBuffer>(L"TILEINSTBUFFER"))
	{
		Resources::Create<InstanceBuffer>(L"TILEINSTBUFFER", 1000, &typeid(TILEINSTDATA), sizeof(TILEINSTDATA));
	}

	if (nullptr == Resources::Find<Mesh>(L"TILEINSTMESH"))
	{
		HPTR<Mesh> NEWMESH = Resources::Create<Mesh>(L"TILEINSTMESH");
		NEWMESH->AddVB(L"DTEXVBBUFFER");
		NEWMESH->AddINST(L"TILEINSTBUFFER");
		NEWMESH->AddIB(L"DTEXIBBUFFER");
	}






	//// TILEINSTDATA ������� �ν��Ͻ��� �Ұ��̴�.
	//InstBuffer = HRENMGR::CreateInstancing(L"TileMapInst", L"TILEINSTMESH");
	//InstBuffer->RenderPath().BLEND(L"DBLEND");
	//InstBuffer->RenderPath().DSSTATE(L"DDSSTATE");
	//InstBuffer->RenderPath().RSSTATE(L"DRSSTATE");
	//InstBuffer->RenderPath().VTXSHADER(L"TEXSHADERINST.fx");
	//InstBuffer->RenderPath().PIXSHADER(L"TEXSHADER.fx");
	//InstBuffer->RenderPath().SMP(HSHADER::SHADERTYPE::SHT_PS, 0, L"DSMP");
	//InstBuffer->RenderPath().DrawMode(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//

	Renderer::Init();

	return;

	// ����� pushrENDER�� �ȴ�.

	m_SMP = Resources::Find<SamplerState>(L"DSMP");
	m_HMESH = Resources::Find<Mesh>(L"DTEXMESH");
	m_HCB = Resources::Find<ConstantBuffer>(L"MATBUF");
	m_HCBUV = Resources::Find<ConstantBuffer>(L"CUTBUF");
	m_HVTXSHADER = Resources::Find<VertexShader>(L"TEXSHADER.fx");
	m_HPIXSHADER = Resources::Find<PixelShader>(L"TEXSHADER.fx");
	m_BLEND = Resources::Find<Blend>(L"DBLEND");
	m_DSSTATE = Resources::Find<DepthStencilState>(L"DDSSTATE");
	m_RSSTATE = Resources::Find<RasterizerState>(L"DRSSTATE");
}


void JITILEMAP::TileSprite(const wchar_t* _Name) 
{
	m_TileSprite = Resources::Find<Sprite>(_Name);

	if (nullptr == m_TileSprite)
	{
		BOOM;
	}

	// InstBuffer->RenderPath().TEX(_Name, HSHADER::SHADERTYPE::SHT_PS, 0);

}

void JITILEMAP::FloorSprite(const wchar_t* _Name) 
{
	m_FloorSprite = Resources::Find<Sprite>(_Name);
}

void JITILEMAP::AddTileWorld(Vector4 _Pos) 
{
	//_Pos.x = _Pos.x / m_TileScale.x;
	//_Pos.y = _Pos.y / m_TileScale.y;

	Vector4 Idx;
	Idx.x = (_Pos.x / m_TileMoveSize.x + _Pos.y / m_TileMoveSize.y) / 2.0f;
	Idx.y = (_Pos.y / m_TileMoveSize.y + -(_Pos.x / m_TileMoveSize.x)) / 2.0f;

	Idx.ix = std::lroundf( Idx.x);
	Idx.iy = std::lroundf(Idx.y);
	AddTile(Idx.KeyPos);
}

Vector4 JITILEMAP::PosToIndex(Vector4 _Pos) 
{
	Vector4 Idx;
	Idx.x = (_Pos.x / m_TileMoveSize.x + _Pos.y / m_TileMoveSize.y) / 2.0f;
	Idx.y = (_Pos.y / m_TileMoveSize.y + -(_Pos.x / m_TileMoveSize.x)) / 2.0f;

	Idx.ix = std::lroundf(Idx.x);
	Idx.iy = std::lroundf(Idx.y);

	return Idx;
}


HPTR<JITILEMAP::HGAMETILE> JITILEMAP::FindTile(Vector4 _Pos) 
{
	std::map<__int64, HPTR<HGAMETILE>>::iterator FindIter = m_TileMap.find(PosToIndex(_Pos).KeyPos);

	if (FindIter == m_TileMap.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

HPTR<JITILEMAP::HGAMETILE> JITILEMAP::FindTile(__int64 _KeyPos)
{
	std::map<__int64, HPTR<HGAMETILE>>::iterator FindIter = m_TileMap.find(_KeyPos);

	if (FindIter == m_TileMap.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

void JITILEMAP::ChangeFloor(Vector4 _Pos, int _Floor)
{
 	HPTR<HGAMETILE> Tile = FindTile(_Pos);

	if (nullptr != Tile)
	{
		Tile->Floor = _Floor;
		Tile->Pos = Tile->BasePos;
		Tile->Pos.y = Tile->BasePos.y + Tile->Floor * m_TileMoveSize.y;
		// Value ���� ��������� Ȥ�� ���� �����ڰ� �ڵ����� ȣ��� ���̴�.
		// Ư���� ���� ��������� �ʾ����ϱ�.
	}
}

void JITILEMAP::ChangeLeftFloor(Vector4 _Pos, int _Floor)
{
	HPTR<HGAMETILE> Tile = FindTile(_Pos);

	if (nullptr != Tile)
	{
		Tile->LeftFloorSpriteIndex = _Floor;
		// Value ���� ��������� Ȥ�� ���� �����ڰ� �ڵ����� ȣ��� ���̴�.
		// Ư���� ���� ��������� �ʾ����ϱ�.
	}
}

void JITILEMAP::ChangeRightFloor(Vector4 _Pos, int _Floor)
{
	HPTR<HGAMETILE> Tile = FindTile(_Pos);

	if (nullptr != Tile)
	{
		Tile->RightFloorSpriteIndex = _Floor;
		// Value ���� ��������� Ȥ�� ���� �����ڰ� �ڵ����� ȣ��� ���̴�.
		// Ư���� ���� ��������� �ʾ����ϱ�.
	}
}

void JITILEMAP::AddTileF(Vector4 _Index) 
{
	_Index.ConToInt();

	_Index.ix, _Index.iy;

	AddTile(_Index.KeyPos);
}

void JITILEMAP::AddTile(int _X, int _Y) 
{
	__int64 Key = 0;
	int* pKey = (int*)&Key;
	(*pKey) = _X;
	++pKey;
	(*pKey) = _Y;

	//HVEC4 Key = {0,};
	//Key.ix = _X;
	//Key.iy = _Y;

	AddTile(Key);
}

void JITILEMAP::AddTile(__int64 _Index)
{
	if (nullptr == m_TileSprite)
	{
		BOOM;
	}

	if (m_TileMap.end() != m_TileMap.find(_Index))
	{
		return;
	}

	HPTR<HGAMETILE> Value = new HGAMETILE();

	Vector4 Idx;
	Idx.KeyPos = _Index;
	Vector4 Pos;
	// floor�� ������� z���̴�.
	Pos.x = (Idx.ix - Idx.iy) * m_TileMoveSize.x;
	Pos.y = (Idx.ix + Idx.iy) * m_TileMoveSize.y;
	// Pos.y += 0 * m_TileMoveSize.y;
	Pos.z = Pos.y;

	Value->Index.KeyPos = _Index;
	Value->BasePos = Pos;
	Value->Pos = Pos;

	// Value ���� ��������� Ȥ�� ���� �����ڰ� �ڵ����� ȣ��� ���̴�.
	// Ư���� ���� ��������� �ʾ����ϱ�.
	m_TileMap.insert(std::map<__int64, HPTR<HGAMETILE>>::value_type(_Index, Value));
}

void JITILEMAP::Render(const HPTR<Camera>& _CAM)
{
	InstRender(_CAM);
}

// char Arr[10000000];
// �޸� Ǯ�� ������ƮǮ�� ������ �ٸ������̴�.
// ������ ���Ѱ�
// ���� new 
void JITILEMAP::PushNode(HPTR<JITILEMAP::HPATHNODE> _Node) 
{
	if (nullptr == _Node)
	{
		BOOM;
	}

	NodePool.push_back(_Node);
}

HPTR<JITILEMAP::HPATHNODE> JITILEMAP::NewNode(JITILEMAP::HPATHNODE* _Parent, HGAMETILE* _Tile, HGAMETILE* _End)
{
	// 2000�� �̻� ã�ƺôµ��� ���� ������.
	// ���� ��ã�Ҵٶ�� �����Ұ�.
	if (0 == NodePool.size())
	{
		return nullptr;
	}

	std::list<HPTR<HPATHNODE>>::iterator Start = NodePool.begin();
	HPTR<JITILEMAP::HPATHNODE> Node = (*Start);
	Node->CalValue(_Parent, _Tile, _End);
	NodePool.pop_front();
	return Node;
}

void JITILEMAP::AStarMaxSetting(int _Count)
{
	for (size_t i = 0; i < _Count; i++)
	{
		NodePool.push_back(new JITILEMAP::HPATHNODE());
	}
}

HPTR<JITILEMAP::HPATHNODE> JITILEMAP::FirstOpenPop()
{
	HPTR<JITILEMAP::HPATHNODE> FirstNode = OpenList.begin()->second;
	if (nullptr == FirstNode->Tile)
	{
		BOOM;
	}

	OpenListSet.erase(FirstNode->Tile);
	OpenList.erase(OpenList.begin());
	CloseList.insert(std::map<__int64, HPTR<HPATHNODE>>::value_type(FirstNode->Tile->Index.KeyPos, FirstNode));
	return FirstNode;
}

void JITILEMAP::AddOpenList(HPTR<HPATHNODE> _NewNode) 
{
	if (nullptr == _NewNode->Tile)
	{
		BOOM;
	}

	OpenListSet.insert(_NewNode->Tile);
	OpenList.insert(std::multimap<float, HPTR<HPATHNODE>>::value_type(_NewNode->F, _NewNode));
}

// 4����
// ���ϵǰ� �ٲ�.
HPTR<JITILEMAP::HPATHNODE> JITILEMAP::OpenNodeFind(HPTR<HPATHNODE> _Node, HGAMETILE* _End)
{
	for (size_t i = 0; i < 4; i++)
	{
		Vector4 Idx;
		Idx.ix = _Node->Tile->Index.ix + Vector4::ARRIDIR[i].ix;
		Idx.iy = _Node->Tile->Index.iy + Vector4::ARRIDIR[i].iy;

		HGAMETILE* _Tile = FindTile(Idx.KeyPos);

		// ���̰� 2�̻��� ���
		// ��Ÿ���� ���
		// Ÿ���� ���� ���
		if (nullptr == _Tile)
		{
			continue;
		}

		// �� Ÿ���� ���� ����Ʈ�� ����ִ� Ÿ���̴�.
		if (OpenListSet.end() != OpenListSet.find(_Tile))
		{
			continue;
		}

		// ��Ÿ���� Ŭ���� ����Ʈ�� ����ִ� Ÿ���̴�.
		if (CloseList.end() != CloseList.find(_Tile->Index.KeyPos))
		{
			continue;
		}

		// std::find()
		// ���� �־���.
		// ���⵵ �ٲ�.
		// ���� �ص� Ÿ���̸� ������.
		HPTR<JINODE> Node = NewNode(_Node, _Tile, _End);
		AddOpenList(Node);

		if (Node->Tile == _End)
		{
			return Node;
		}
	}

	return nullptr;
}

void JITILEMAP::PathReset() 
{
	OpenListSet.clear();
	{
		std::multimap<float, HPTR<HPATHNODE>, std::less<float>>::iterator Start = OpenList.begin();
		std::multimap<float, HPTR<HPATHNODE>, std::less<float>>::iterator End = OpenList.end();

		for (; Start != End; ++Start)
		{
			NodePool.push_back(Start->second);
		}

		OpenList.clear();
	}
	{
		std::map<__int64, HPTR<HPATHNODE>>::iterator Start = CloseList.begin();
		std::map<__int64, HPTR<HPATHNODE>>::iterator End = CloseList.end();

		for (; Start != End; ++Start)
		{
			NodePool.push_back(Start->second);
		}
		CloseList.clear();
	}

}

std::list<JITILEMAP::HGAMETILE*> JITILEMAP::AStarPathFind(Vector4 _Start, Vector4 _End) 
{
	HPTR<JITILEMAP::HGAMETILE> StartTile = FindTile(_Start);
	HPTR<JITILEMAP::HGAMETILE> EndTile = FindTile(_End);

	// �̰͵� �߰� ����ó��
	if (nullptr == StartTile || nullptr == EndTile)
	{
		return std::list<HGAMETILE*>();
	}

	if (StartTile == EndTile)
	{
		return std::list<HGAMETILE*>();
	}

	// ���⼭ ������ ��������
	// JINODE* Node = NewNode(nullptr, StartTile, EndTile);
	HPTR<JINODE> Node = NewNode(nullptr, StartTile, EndTile);
	AddOpenList(Node);

	HPTR<JINODE> LastNode = nullptr;

	while (0 != OpenList.size())
	{
		LastNode = OpenNodeFind(FirstOpenPop(), EndTile);

		if (0 == NodePool.size())
		{
			break;
		}

		if (nullptr != LastNode)
		{
			break;
		}
	}

	std::list<HGAMETILE*> NewList;

	if (nullptr != LastNode)
	{
		while (nullptr != LastNode->Parent)
		{
			NewList.push_front(LastNode->Tile);
			LastNode = LastNode->Parent;
		}
	}

	// �� Ǯ�� �ٽ� ������� �Ѵ�.
	PathReset();

	return NewList;
	// ������ ���ư��� ���� ���´�.
	// 

}

void JITILEMAP::BaseRender(const HPTR<Camera>& _CAM)
{


	TileStart = m_TileMap.begin();
	TileEnd = m_TileMap.end();

	// ��� Ÿ���� �θ���
	UpdateTransform();
	Matrix W = GetWorldMatrix();
	Matrix V = _CAM->GetViewMatrix();
	Matrix P = _CAM->PMAT();
	Matrix WVP = W * V * P;

	m_HVTXSHADER->Update();
	m_HPIXSHADER->Update();
	GraphicDevice::MainContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_SMP->Update(Shader::SHADERTYPE::SHT_PS, 0);
	m_DSSTATE->Update();
	m_RSSTATE->Update();
	m_HMESH->Update(0, 0);
	m_BLEND->Update();

	Vector4 Idx;
	Vector4 Pos;
	Vector4 LFPos;
	Vector4 RFPos;
	Matrix ScaleMAT;
	Matrix PosMAT;
	Matrix ResultMat;

	for (; TileStart != TileEnd; ++TileStart)
	{
		m_TileSprite->Update(Shader::SHADERTYPE::SHT_PS, 0);
		ScaleMAT.Scaling(m_TileScale);
		PosMAT.Translation(TileStart->second->Pos);
		ResultMat = ScaleMAT * PosMAT * WVP;
		ResultMat.TransPose();

		m_HCB->DataSetting(&ResultMat, sizeof(Matrix));
		m_HCB->Update();
		TEXUV = m_TileSprite->GetCutData(TileStart->second->SpriteIndex);
		m_HCBUV->DataSetting(&TEXUV, sizeof(TEXUV));
		m_HCBUV->Update();
		m_HMESH->Render(0);

		// InstBuffer->PushData<>

		// TILEINSTDATA Data;
		// Data.MAT = ResultMat; // Ʈ���� ���� �ϸ� �ȵȴ�.
		// Data.SPRITEUV = TEXUV; // Ʈ���� ���� �ϸ� �ȵȴ�.
		// HRENMGR::PushInstData<TILEINSTDATA>(L"TileMapInst", Data);

		// ����
		m_FloorSprite->Update(Shader::SHADERTYPE::SHT_PS, 0);
		ScaleMAT.Scaling(m_FloorScale);


		LFPos = TileStart->second->Pos;
		LFPos.x -= m_FloorScale.x * 0.5f;
		LFPos.y -= (m_FloorScale.y * 0.5f)/* - (m_TileScale.y * 0.5f)*/;
		PosMAT.Translation(LFPos);
		ResultMat = ScaleMAT * PosMAT * WVP;
		ResultMat.TransPose();

		TEXUV = m_FloorSprite->GetCutData(TileStart->second->LeftFloorSpriteIndex);
		m_HCBUV->DataSetting(&TEXUV, sizeof(TEXUV));
		m_HCBUV->Update();

		m_HCB->DataSetting(&ResultMat, sizeof(Matrix));
		m_HCB->Update();
		m_HMESH->Render(0);

		//m_HCB->DataSetting(&ResultMat, sizeof(HMAT));
		//m_HCB->Update();

		// ������

		RFPos = TileStart->second->Pos;
		RFPos.x += m_FloorScale.x * 0.5f;
		RFPos.y -= (m_FloorScale.y * 0.5f)/* - (m_TileScale.y * 0.5f)*/;
		PosMAT.Translation(RFPos);
		ResultMat = ScaleMAT * PosMAT * WVP;
		ResultMat.TransPose();

		TEXUV = m_FloorSprite->GetCutData(TileStart->second->RightFloorSpriteIndex);
		m_HCBUV->DataSetting(&TEXUV, sizeof(TEXUV));
		m_HCBUV->Update();

		m_HCB->DataSetting(&ResultMat, sizeof(Matrix));
		m_HCB->Update();
		m_HMESH->Render(0);
	}

}


void JITILEMAP::InstRender(const HPTR<Camera>& _CAM)
{
	TileStart = m_TileMap.begin();
	TileEnd = m_TileMap.end();

	// ��� Ÿ���� �θ���
	UpdateTransform();
	Matrix W = GetWorldMatrix();
	Matrix V = _CAM->GetViewMatrix();
	Matrix P = _CAM->PMAT();
	Matrix WVP = W * V * P;

	Vector4 Idx;
	Vector4 Pos;
	Vector4 LFPos;
	Vector4 RFPos;
	Matrix ScaleMAT;
	Matrix PosMAT;
	Matrix ResultMat;

	TILEINSTDATA Data;

	for (; TileStart != TileEnd; ++TileStart)
	{
		m_TileSprite->Update(Shader::SHADERTYPE::SHT_PS, 0);
		ScaleMAT.Scaling(m_TileScale);
		PosMAT.Translation(TileStart->second->Pos);
		ResultMat = ScaleMAT * PosMAT * WVP;
		TEXUV = m_TileSprite->GetCutData(TileStart->second->SpriteIndex);

		Data.WVP = ResultMat;
		Data.SPRITEUV = TEXUV;

		InstBuffer->PushData(Data);
	}

}