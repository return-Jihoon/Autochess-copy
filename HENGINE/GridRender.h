#pragma once
#include "Renderer.h"

class Camera;
class GridRender : public Renderer
{
public:
	// ����Ʈ �е�
	class GRIDDATA 
	{
	public:
		// �־��ݽô�.
		float Step; // 100~ 1000 ~ 10000
		float Borader; // ����
		float MinA; // ����
		float MaxA; // ����
		Vector4 Color;
		Vector4 CamPos;
	};

private:
	GRIDDATA m_Data;

public:
	void SetColor(Vector4 _Color) 
	{
		m_Data.Color = _Color;
	}



public:
	void RenderDataUpdate(const HPTR<Camera>& _CAM, HRENDERDATA* _Data) override;
	void Render(const HPTR<Camera>& _CAM) override;

public:
	void Init() override;
	void Update() override;


public:
	GridRender();
	~GridRender();
};

