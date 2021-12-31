#pragma once
#include "Renderer.h"

// 2D스프라이트에 특화된 렌더러를 만든다.
class Mesh;
class ConstantBuffer;
class VertexShader;
class PixelShader;
class SamplerState;
class Sprite;
class Blend;
class DepthStencilState;
class RasterizerState;
class SpriteRender : public Renderer
{
public:
	friend Actor;

private:
	bool m_BillBoard;
	int m_SpriteIndex;

	HPTR<Sprite> m_Sprite;
	Vector4 m_Vec;

	Vector4 m_UIData;
	
	int m_LastIdx;

public:
	void BillBoardOn()
	{
		m_BillBoard = true;
		//FrontOn();
	}

	void BillBoardOff()
	{
		m_BillBoard = false;
	}

	void FrontOn()
	{
		m_Vec.x = 1.0f;
	}

	void FrontOff()
	{
		m_Vec.x = 0.0f;
	}

	Vector4& GetCutData()
	{
		return m_Vec;
	}

	Vector4& GetUIData()
	{
		return m_UIData;
	}

	int GetLastIdx()
	{
		return m_LastIdx;
	}

public:
	void Init() override;
	void DataCreate(int _Order);

public:
	void UpdateSubTrans(const HPTR<Camera>& _Cam) override;
	
	void SetSprite(const wchar_t* _SpriteName, int _SpriteIndex = 0);
	void SetSpriteIdx(int _SpriteIndex);
	void CalCutData(int _SpriteIndex);

public:
	SpriteRender();
	~SpriteRender();
};

