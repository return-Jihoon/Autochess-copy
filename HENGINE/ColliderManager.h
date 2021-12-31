#pragma once
#include <Ref.h>
#include <Debug.h>

#include <map>
#include <list>
// ������ �浹ó��
// ȭ�� �ٱ����� ������ ���ؾ��� ��찡 �ִµ�.
// �ᱹ ������ �˾ƾ� �ϳ�?
// CAM
class Collider;
class Scene;
class ColliderManager
{
public:
	friend Collider;
	friend Scene;

private:
	class ColliderGroup : public Reference
	{
	public:
		friend ColliderManager;

	public:
		std::list<HPTR<Collider>>::iterator m_ThisColStart;
		std::list<HPTR<Collider>>::iterator m_ThisColEnd;
		std::list<HPTR<Collider>>::iterator m_OtherColStart;
		std::list<HPTR<Collider>>::iterator m_OtherColEnd;

	public:
		// ���� �浹�� �ٸ� �׷���� �����ϰ� �ִ°�.
		std::list<ColliderGroup*>::iterator m_OtherStart;
		std::list<ColliderGroup*>::iterator m_OtherEnd;
		std::list<ColliderGroup*> m_OtherList;

	private:
		std::list<HPTR<Collider>> m_ColList;

		void PushCol(const HPTR<Collider>& _COL) 
		{
			if (nullptr == _COL) { BOOM; }
			m_ColList.push_back(_COL);
		}

		void PushOtherGroup(ColliderGroup* _OtherGroup) 
		{
			if (nullptr == _OtherGroup) { BOOM; }
			m_OtherList.push_back(_OtherGroup);
		}

	public:
		void Release();
		void OverRelease();
		void COL();
		void OTHERGROUPCOL(ColliderGroup* _OtherGroup);
		void THISGROUPCOL();
	};

private:
	std::map<int, HPTR<ColliderGroup>>::iterator ColOrderStart;
	std::map<int, HPTR<ColliderGroup>>::iterator ColOrderEnd;
	std::map<int, HPTR<ColliderGroup>> m_COLMAP;

private:
	HPTR<ColliderGroup> FindGroup(const int& _Key);

	void PushCol(const HPTR<Collider>& _COL);

private:
	void Col();
	void Release();
	void OverRelease();

public:
	// �̰� ȣ�� ���ϸ� �׷찣 �浹 x
	void Link(const int& _Src, const int& _Dest);

public:
	ColliderManager();
	~ColliderManager();
};