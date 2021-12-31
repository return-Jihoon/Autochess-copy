#pragma once
#include "Renderer.h"

class Mesh;
class ConstantBuffer;
class VertexShader;
class PixelShader;
class SamplerState;
class Sprite;
class Blend;
class DepthStencilState;
class RasterizerState;
class RectRender :
	public Renderer
{
private:
	Vector4 m_COLOR;
	HPTR<Mesh> m_HMESH;
	HPTR<ConstantBuffer> m_HCB;
	HPTR<ConstantBuffer> m_HCBCOLOR;
	HPTR<VertexShader> m_HVTXSHADER;
	HPTR<PixelShader> m_HPIXSHADER;
	HPTR<SamplerState> m_SMP;
	HPTR<Blend> m_BLEND;
	HPTR<DepthStencilState> m_DSSTATE;
	HPTR<RasterizerState> m_RSSTATE;

public:
	void Init() override;
	void Render(const HPTR<Camera>& _CAM) override;

public:
	// ¼÷Á¦·Î ºÓÀº»ö ±â¿îÀÌ ¶çµµ·Ï
	void SetColor(const Vector4& _COLOR)
	{
		m_COLOR = _COLOR;
	}


public:
	RectRender();
	~RectRender();
};

