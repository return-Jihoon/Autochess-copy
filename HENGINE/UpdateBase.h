#pragma once

// �����ο��� \�� ���� �����ڴٴ� ���� �ȴ�.
//#define PLUS(X) X + X; X + X;

#define ITERFOR(Start, End, List, FuncName) \
if (0 != List##.size()) \
{ \
	Start = List##.begin(); \
	End = List##.end(); \
	for (; Start != End; ++Start) \
	{ \
		if (true == (*##Start##)->##IsUpdate##()) \
		{ \
			(*##Start##)->##FuncName##(); \
		} \
	} \
}

// class Collider;
class UpdateBase
{
protected:
	bool m_IsUpdate;
	bool m_IsDeath;

public:
	// �Լ��� �Լ�ü��
	// �Լ� �������� �����Ǿ� �ִ�.

	// inline�� �Լ�ü�� ġȯ���� ������.
	// inline virtual bool IsUpdate() �Լ� ����
	//	{
	//      return true == m_IsUpdate && false == m_IsDeath;
    //  }

	inline virtual bool UpdateOn()
	{
		return m_IsUpdate = true;
	}

	inline virtual bool UpdateOff()
	{
		return m_IsUpdate = false;
	}

	inline virtual bool IsUpdate()
	{
		return true == m_IsUpdate && false == m_IsDeath;
	}
	inline virtual bool IsDeath() {
		return m_IsDeath;
	}

	inline virtual void Die() {
		m_IsDeath = true;
	}
	
public:
	// �����Լ��� �����ٰ� �ϴ�����.
	// ���Լ��� ������ �ع�����.
	virtual void UpdateAfter();
	virtual void Update();
	virtual void UpdateBefore();
	virtual void FinalUpdate();
	virtual void RenderBefore();
	virtual void RenderAfter();
	virtual void ColBefore();
	virtual void ColAfter();
	virtual void Release();
	virtual void ReleaseAfter();

	// ���� �� �Ⱦ����� �ϴ°�??? ��������.
	// TRANS�� �� COLENTER�� ȣ���ؾ� �ϴ°�?
	//virtual void ColEnter(Collider* _This, Collider* _Other) {}
	//virtual void ColStay(Collider* _This, Collider* _Other) {}
	//virtual void ColExit(Collider* _This, Collider* _Other) {}

public:
	UpdateBase();
	virtual ~UpdateBase() = 0;
};

