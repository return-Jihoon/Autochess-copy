#pragma once
#include "SubTransform.h"
#include <set>
#include <list>
#include <functional>

// ����� �簢���� ȭ�鿡 ������.
// AABBCOL DirectX::BoundingBox
// OBBCOL DirectX::BoundingOrientedBox
// SUB

class ColliderManager;
class Collider : public SubTransform
{
private:
	enum MODE
	{
		COL2D,
		COL3D,
	};

public:
	friend ColliderManager;

private:
	int m_Order;

	int GetOrder()
	{
		return m_Order;
	}

	void SetOrder(int _Order) {
		m_Order = _Order;
	}

private:
	// �̸��� �ٿ��� ���� �����Ϥ���.
	// void(*Ptr)();
	std::list<std::function<void(Collider*, Collider*)>>::iterator m_FuncStart;
	std::list<std::function<void(Collider*, Collider*)>>::iterator m_FuncEnd;
	std::list<std::function<void(Collider*, Collider*)>> m_EnterList;
	std::list<std::function<void(Collider*, Collider*)>> m_StayList;
	std::list<std::function<void(Collider*, Collider*)>> m_ExitList;

public:
	template<typename T>
	void RegEnterFuncPush(void(T::*pFunc)(Collider*, Collider*), T* _Obj)
	{
		std::function<void(Collider*, Collider*)> Func 
			= std::bind(pFunc, _Obj
			, std::placeholders::_1
			, std::placeholders::_2);
		if (nullptr == Func) { BOOM; }
		m_EnterList.push_back(Func);
	}

	// �����Լ�
	void RegEnterFuncPush(void(*_Ptr)(Collider*, Collider*))
	{
		std::function<void(Collider*, Collider*)> Func = _Ptr;
		if (nullptr == Func) { BOOM; }
		m_EnterList.push_back(Func);
	}

	template<typename T>
	void RegStayFuncPush(void(T::*pFunc)(Collider*, Collider*), T* _Obj)
	{
		std::function<void(Collider*, Collider*)> Func
			= std::bind(pFunc, _Obj
				, std::placeholders::_1
				, std::placeholders::_2);
		if (nullptr == Func) { BOOM; }
		m_StayList.push_back(Func);
	}

	// �����Լ�
	void RegStayFuncPush(void(*_Ptr)(Collider*, Collider*))
	{
		std::function<void(Collider*, Collider*)> Func = _Ptr;
		if (nullptr == Func) { BOOM; }
		m_StayList.push_back(Func);
	}

	template<typename T>
	void RegExitFuncPush(void(T::*pFunc)(Collider*, Collider*), T* _Obj)
	{
		std::function<void(Collider*, Collider*)> Func
			= std::bind(pFunc, _Obj
				, std::placeholders::_1
				, std::placeholders::_2);
		if (nullptr == Func) { BOOM; }
		m_ExitList.push_back(Func);
	}

	// �����Լ�
	void RegExitFuncPush(void(*_Ptr)(Collider*, Collider*))
	{
		std::function<void(Collider*, Collider*)> Func = _Ptr;
		if (nullptr == Func) { BOOM; }
		m_ExitList.push_back(Func);
	}

private:
	void ColEnter(Collider* _Other);
	void ColExit(Collider* _Other);
	void ColStay(Collider* _Other);

private:
	// > < ���̳ʸ� ��ġƮ��
	/*, std::greater<Collider*>*/
	std::set<Collider*>::iterator FindIter;
	// ���� �浹�� �༮���� ������ ���°�
	// �������� ���������
	// �浹�� ���۵Ǹ�
	// �����Ѵ�.
	// �浹�� ������
	// ������.
	std::set<Collider*> m_OtherSet;

private:
	void Init() override;

public:
	void DataCreate(int _Order = 0);

private:
	void ColCheck(Collider* _Other);

public:
	// �ٿ� ĳ����
	virtual bool GeometryCheck(Collider* _Other) = 0;

private:
	// �Լ� �����͸� �޴´�.
	// �Լ� �����ͷ� 

public:
	void SceneChangeStart() override;

public:
	Collider();
	~Collider();
};

