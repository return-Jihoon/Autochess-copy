#pragma once
#include "D3DBuffer.h"

class IndexBuffer	: public D3DBuffer
{
private:
	DXGI_FORMAT m_IBType; // �ε��� ���� Ÿ�� �ڷ����� ����?
	UINT m_IDXSize; // �ε��� ���� ���� 1���� ������;
	UINT m_IDXCount; // ���� x���� ��ü �׳� ������ ���????;

public:
	DXGI_FORMAT IBType()
	{
		return m_IBType;
	}

	unsigned int IDXCount() 
	{
		return m_IDXCount;
	}


public:
	template<typename T>
	bool Create(std::vector<T>& _Data, D3D11_USAGE _VtxUsage)
	{
		if (0 >= _Data.size())
		{
			BOOM;
		}
		return Create(T::FORMAT(), (int)_Data.size() * 3, T::MEMSIZE(), _VtxUsage, &_Data[0]);
	}

	bool Create(std::vector<DWORD>& _Data, D3D11_USAGE _VtxUsage)
	{
		if (0 >= _Data.size())
		{
			BOOM;
		}
		return Create(DXGI_FORMAT_R32_UINT, (int)_Data.size(), sizeof(DWORD), _VtxUsage, &_Data[0]);
	}

	bool Create(std::vector<UINT>& _Data, D3D11_USAGE _VtxUsage)
	{
		if (0 >= _Data.size())
		{
			BOOM;
		}
		return Create(DXGI_FORMAT_R32_UINT, (int)_Data.size(), sizeof(DWORD), _VtxUsage, &_Data[0]);
	}


	bool Create(DXGI_FORMAT _IdxFormat, UINT _iIdxCount, UINT _iIdxSize, D3D11_USAGE _IdxUsage, void* _Data);


public:
	IndexBuffer();
	~IndexBuffer();
};

