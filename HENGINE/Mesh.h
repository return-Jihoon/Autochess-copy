#pragma once
#include "EngineMeshData.h"
#include "GraphicDevice.h"
#include <vector>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "InstanceBuffer.h"

class Mesh : public Resources
{
private:

private:
	//class HINSTANCINGBUFFER : public VBUFFER
	//{
	//};


private:
	// ��ǲ ������� �����ϴ� �뵵
	std::vector<HPTR<IndexBuffer>> m_ArrIB;
	std::vector<HPTR<VertexBuffer>> m_ArrVB;

	std::vector<ID3D11Buffer*> m_ArrVBBuffer;
	std::vector<unsigned int> m_ArrVBOffSet; // ���۰�
	std::vector<unsigned int> m_ArrVBSize;

	std::vector<ID3D11Buffer*> m_ArrIBBuffer;
	std::vector<unsigned int> m_ArrIBOffSet;

	// �ϳ��� �ν��Ͻ� ���۸� ������ �ִ´�.
	HPTR<InstanceBuffer> m_INSTBUFFER;

public:
	HPTR<InstanceBuffer> INSTBUFFER() {
		return m_INSTBUFFER;
	}

public:
	bool Create()
	{
		return true;
	}

	void AddVB(const wchar_t* _Name);
	void AddINST(const wchar_t* _Name);
	void AddIB(const wchar_t* _Name);


public:
	void UpdateAllVB();
	void UpdateVB(UINT _Index);
	void UpdateIB(UINT _Index);
	void UpdateIB();

	void Update(UINT _VtxIndex, UINT _IdxIndex);

	void Render(UINT _IdxIndex);

	void RenderInstancing(UINT _IdxIndex);

	void RenderAuto();


public:
	Mesh();
	~Mesh();
};

