#include "ColliderManager.h"
#include "Collider.h"

// ������ �̵�
// ��ã�� �˰���...
// �ѹ��� ã�´�.
// ��� ü������ �ؾ��Ѵ�.

void ColliderManager::ColliderGroup::COL() 
{
	m_OtherStart = m_OtherList.begin();
	m_OtherEnd = m_OtherList.end();

	for (; m_OtherStart != m_OtherEnd; ++m_OtherStart)
	{
		if (this != *m_OtherStart)
		{
			OTHERGROUPCOL(*m_OtherStart);
		}
		else 
		{
			THISGROUPCOL();
		}
	}
}

void ColliderManager::ColliderGroup::OTHERGROUPCOL(ColliderGroup* _OtherGroup) 
{
	// ����� ������ �ʴ´�.
	m_ThisColStart = m_ColList.begin();
	m_ThisColEnd = m_ColList.end();

	for (; m_ThisColStart != m_ThisColEnd; ++m_ThisColStart)
	{
		if (false == (*m_ThisColStart)->IsUpdate())
		{
			continue;
		}

		m_OtherColStart = _OtherGroup->m_ColList.begin();
		m_OtherColEnd = _OtherGroup->m_ColList.end();

		for (; m_OtherColStart != m_OtherColEnd; ++m_OtherColStart)
		{
			if (false == (*m_OtherColStart)->IsUpdate())
			{
				continue;
			}

			(*m_ThisColStart)->ColCheck((*m_OtherColStart));
		}
	}
}

void ColliderManager::ColliderGroup::THISGROUPCOL() 
{
	m_ThisColStart = m_ColList.begin();
	m_ThisColEnd = m_ColList.end();

	for (; m_ThisColStart != m_ThisColEnd; ++m_ThisColStart)
	{
		if (false == (*m_ThisColStart)->IsUpdate())
		{
			continue;
		}

		m_OtherColStart = m_ThisColStart;
		++m_OtherColStart;
		// end�� �ٷ� ����Ű�� �Ǹ�
		m_OtherColEnd = m_ColList.end();

		for (; m_OtherColStart != m_OtherColEnd; ++m_OtherColStart)
		{
			if (false == (*m_OtherColStart)->IsUpdate())
			{
				continue;
			}

			(*m_ThisColStart)->ColCheck((*m_OtherColStart));
		}
	}
}

void ColliderManager::ColliderGroup::Release()
{
	m_ThisColStart = m_ColList.begin();
	m_ThisColEnd = m_ColList.end();

	for (; m_ThisColStart != m_ThisColEnd; )
	{
		if (true == (*m_ThisColStart)->IsDeath())
		{
			m_ThisColStart = m_ColList.erase(m_ThisColStart);
		}
		else {
			++m_ThisColStart;
		}
	}
}

void ColliderManager::ColliderGroup::OverRelease()
{
	m_ThisColStart = m_ColList.begin();
	m_ThisColEnd = m_ColList.end();

	for (; m_ThisColStart != m_ThisColEnd; )
	{
		if (true == (*m_ThisColStart)->GetActor()->IsOverReady())
		{
			m_ThisColStart = m_ColList.erase(m_ThisColStart);
		}
		else {
			++m_ThisColStart;
		}
	}
}

/////////////////////////////////////// CMGR

ColliderManager::ColliderManager()
{
}


ColliderManager::~ColliderManager()
{
}


void ColliderManager::Col() 
{
	ColOrderStart = m_COLMAP.begin();
	ColOrderEnd = m_COLMAP.end();

	for (; ColOrderStart != ColOrderEnd; ++ColOrderStart)
	{
		ColOrderStart->second->COL();
	}
}

void ColliderManager::PushCol(const HPTR<Collider>& _COL)
{
	// 2�� ������ �׳� ����... 
	std::map<int, HPTR<ColliderGroup>>::iterator FindIter
		= m_COLMAP.find(_COL->GetOrder());

	if (FindIter == m_COLMAP.end())
	{
		m_COLMAP.insert(std::map<int, HPTR<ColliderGroup>>::value_type(_COL->GetOrder(), new ColliderGroup()));
		FindIter = m_COLMAP.find(_COL->GetOrder());
	}

	FindIter->second->PushCol(_COL);
}

HPTR<ColliderManager::ColliderGroup> ColliderManager::FindGroup(const int& _Key) 
{
	std::map<int, HPTR<ColliderGroup>>::iterator FindIter
		= m_COLMAP.find(_Key);

	if (FindIter == m_COLMAP.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

void ColliderManager::Link(const int& _Src, const int& _Dest) 
{
	ColliderGroup* SRC = FindGroup(_Src);
	ColliderGroup* DEST = FindGroup(_Dest);

	if (nullptr == SRC)
	{
		SRC = new ColliderGroup();
		m_COLMAP.insert(std::map<int, HPTR<ColliderGroup>>::value_type(_Src, SRC));
	}

	if (nullptr == DEST)
	{
		DEST = new ColliderGroup();
		m_COLMAP.insert(std::map<int, HPTR<ColliderGroup>>::value_type(_Dest, DEST));
	}

	SRC->PushOtherGroup(DEST);
}

void ColliderManager::Release()
{
	ColOrderStart = m_COLMAP.begin();
	ColOrderEnd = m_COLMAP.end();

	for (; ColOrderStart != ColOrderEnd; ++ColOrderStart)
	{
		ColOrderStart->second->Release();
	}
}

void ColliderManager::OverRelease() 
{
	ColOrderStart = m_COLMAP.begin();
	ColOrderEnd = m_COLMAP.end();

	for (; ColOrderStart != ColOrderEnd; ++ColOrderStart)
	{
		ColOrderStart->second->Release();
	}
}