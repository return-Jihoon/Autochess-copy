#pragma once
#include "Resources.h"
#include "Shader.h"

class SamplerState : public Resources
{
// public:
	// friend class HRES::HRESMGR<HSMP>;

private:
	D3D11_SAMPLER_DESC m_Decs;
	ID3D11SamplerState* m_pState; // ƒ¡≈ÿΩ∫

public:
	ID3D11SamplerState* State() {
		return m_pState;
	}

public:
	bool Create();
	bool Create(const D3D11_SAMPLER_DESC& m_Decs);
	void Update(Shader::SHADERTYPE _ShaderType, int _SetIndex);

public:
	SamplerState();
	~SamplerState();
};

