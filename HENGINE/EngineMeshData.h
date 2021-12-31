#pragma once
#include <Maths.h>
#include <d3d11_4.h>

class EngineVertex
{
private:
	EngineVertex() {}
	~EngineVertex() {}
public:
	class VertexDebug
	{
	public:
		Vector4 Pos;

	public:
		static unsigned int MEMSIZE()
		{
			return (unsigned int)sizeof(VertexDebug);
		}
	};


	class VertexColor
	{
	public:
		Vector4 Pos;

	public:
		static unsigned int MEMSIZE()
		{
			return (unsigned int)sizeof(VertexColor);
		}
	};


	class VertexGrid
	{
	public:
		Vector4 Pos;
		Vector2 vUv; // ���߿� ����

	public:
		static unsigned int MEMSIZE()
		{
			return (unsigned int)sizeof(VertexGrid);
		}
	};


	class Vertex2D
	{
	public:
		Vector4 Pos;
		Vector2 vUv; // ���߿� ����
		Vector4 Color;

	public:
		static unsigned int MEMSIZE()
		{
			return (unsigned int)sizeof(Vertex2D);
		}
	};

	class Vertex3D
	{
	public:
		Vector4 Pos;
		Vector2 vUv; // ���߿� ����
		Vector4 Color;
		Vector4 Normal; // ���� �ݻ��� ���� ������
		Vector4 BiNormal; // ����Ʈ
		Vector4 Tangent; // ��

	public:
		static unsigned int MEMSIZE()
		{
			return (unsigned int)sizeof(Vertex3D);
		}
	};

	class VertexFBX
	{
	public:
		Vector4 Pos;
		Vector4 UV;
		Vector4 Color;
		Vector4 Normal;
		Vector4 Tangent;
		Vector4 Binormal;
		Vector4 BlendWeight; // ���� ����ġ ���� �ִϸ��̼��� ���� ��ŭ ������ �޴���
		Vector4 BlendIndex;  // ���� � ���� ������ 

	public:
		static unsigned int MEMSIZE()
		{
			return (unsigned int)sizeof(VertexFBX);
		}
	};
};

class EngineIndex
{
private:
	EngineIndex() {}
	~EngineIndex() {}
public:
	// ���� �Ⱦ���.
	class IDX16
	{
		unsigned short _0, _1, _2;
	};

	// ��������� �ﰢ�� �׸��µ� 3���� ������ �ʿ��ϱ� ������
	// �̷� Ŭ������ ����ͻ�.
	// UINT Arr[3][2]
	class Index32
	{
	public:
		unsigned int m_0, m_1, m_2;

	public:
		static unsigned int MEMCOUNT()
		{
			return 3;
		}

		static unsigned int MEMSIZE()
		{
			return (unsigned int)sizeof(unsigned int);
		}

		static DXGI_FORMAT FORMAT()
		{
			return DXGI_FORMAT_R32_UINT;
		}

	public:
		Index32(unsigned int _0, unsigned int _1, unsigned int _2)
			: m_0(_0), m_1(_1), m_2(_2)
		{

		}

	};
};

