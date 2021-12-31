#pragma once
#include "VertexBuffer.h"

// �⺻�����δ� ���鶧 ���ؽ� �����̴�.
class InstanceBuffer : public VertexBuffer
{
private:
	const type_info*	DataType;
	unsigned int		m_CurDataCount;
	std::vector<char>	Data; // �ν��Ͻ̿� �����͸� ��Ƴ��� �뵵.

public:
	void ResetDataCount()
	{
		m_CurDataCount = 0;
	}

	unsigned int CurDataCount() 
	{
		return m_CurDataCount;
	}

	template<typename T>
	void PushData(const T& _Data)
	{
		if (DataType != &typeid(T))
		{
			BOOM;
		}

		if (((m_CurDataCount + 1) * m_VTXSize) > Data.size())
		{
			Data.resize(m_CurDataCount * 2 * m_VTXSize);
		}

		char* p = &Data[0];
		T* DataPointer = (T*)p;
		DataPointer[m_CurDataCount] = _Data;

		++m_CurDataCount;
	}


public:
	bool Create(unsigned int _MaxCount, const type_info* _Type, size_t _TypeSize);
	void UpdateInstData();

public:
	InstanceBuffer();
	~InstanceBuffer();
};

