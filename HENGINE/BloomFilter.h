#pragma once
#include "Camera.h"


class BloomFilter : public Camera::Filter
{
public:
	Vector4 FilterSize;
	Vector4 SFilterSize;

	D3D11_VIEWPORT m_SmallViewPort;// ����Ʈ��Ŀ� ����.
	D3D11_VIEWPORT m_SSmallViewPort;// ����Ʈ��Ŀ� ����.
	HPTR<RenderTarget> SmallTaregt;
	HPTR<RenderTarget> SSmallTaregt;
	HPTR<RenderTarget> SpecCopyTarget;
	HPTR<RenderPath> m_BloomSmallPath;
	HPTR<RenderPath> m_BloomSmallEffectPath;
	HPTR<RenderPath> m_BloomEffectPath;
	HPTR<Mesh> m_Mesh;

public:
	void InitFilter() override;

private:
	void MergeBeforeEffect() override;
	void MergeAfterEffect() override;

public:
	BloomFilter();
	~BloomFilter();
};

