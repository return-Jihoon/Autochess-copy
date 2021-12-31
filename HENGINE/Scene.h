#pragma once
#include <map>
#include <list>

#include <Name.h>
#include <JTime.h>

#include "UpdateBase.h"
#include "Transform.h"
#include "Actor.h"
#include "GraphicDevice.h"
#include "RenderManager.h"
#include "ColliderManager.h"

// ��� ���̻� ��������.
class Scene final : public Reference, public UpdateBase, public Name
{
private:
	friend class GameWindow;
	friend class RenderManager;

public:
	class Updater : public Reference
	{
	public:
		friend Scene;

	private:
		Scene* pScene; // �ڱ⸦ ������ �ִ� ��
		void SetScene(Scene* _pScene)
		{
			pScene = _pScene;
		}

	public:
		Scene* GetScene()
		{
			return pScene;
		}

	private:
		bool IsLoading;

	protected:
		Updater() : IsLoading(false) {}
		virtual void Loading() = 0 {} // �ε��ɶ�
		virtual void SceneUpdate() {} // �� ������Ʈ���� �������� ����.
		virtual void ChangeEnd() {} // ���� ���� �������
		virtual void ChangeStart() {} // ���� ���ο� ���ξ��� �Ǿ�����
		virtual void DebugRender() {} // ���� ���ο� ���ξ��� �Ǿ�����

		bool MouseInTheBox(Actor* _Box);
	};

private:
	GameWindow* pWindow;
	void Window(GameWindow* _Window)	{		pWindow = _Window;	}

public:
	GameWindow* Window()	{		return pWindow;	}

private:
	// ���ÿ� �ΰ��� ��������� ���ٰ� �����ϰ� ����ڽ��ϴ�.
	std::list<HPTR<Updater>> m_UpdaterList;
	std::list<HPTR<Updater>>::iterator m_UpdaterBegin;
	std::list<HPTR<Updater>>::iterator m_UpdaterEnd;

private:
	virtual void LoadingCheck()
	{
		m_UpdaterBegin = m_UpdaterList.begin();
		m_UpdaterEnd = m_UpdaterList.end();

		for (; m_UpdaterBegin != m_UpdaterEnd; ++m_UpdaterBegin)
		{
			if (false == (*m_UpdaterBegin)->IsLoading)
			{
				(*m_UpdaterBegin)->Loading();
				(*m_UpdaterBegin)->IsLoading = true;
			}
		}

		// �ð� �ٽ� ����
		// �ε��ð��� ����Ѵ�.
		Time::Reset();
	} // �ε��ɶ�

public:
	template<typename Com>
	void AddUpdater() 
	{
		Com* NewT = new Com();
		AddUpdater(NewT);
	}

private:
	void AddUpdater(HPTR<Updater> _pCom);

/////////////////////////////////////////////////// Actor

private:
	// ������ �����Ϸ���
	std::list<HPTR<Actor>>::iterator m_ActorBegin;
	std::list<HPTR<Actor>>::iterator m_ActorEnd;
	std::list<HPTR<Actor>> m_ActorList;

public:
	HPTR<Actor> CreateActor(const wchar_t* _Name = L"GameObject");


	
	// HPTR<HACTOR> CreateNoneTransActor(const wchar_t* _Name = L"GameObject");


public:
	void ChangeEnd(); // ���� ���� �������
	void ChangeStart(); // ���� ���ο� ���ξ��� �Ǿ�����

private:
	void Progress();
	void SceneComUpdate();

	void ActorCheck();

	void UpdateBefore()override;
	void Update()override;
	void UpdateAfter()override;
	void FinalUpdate()override;
	void RenderBefore()override;
	void RenderAfter()override;
	void ColBefore()override;
	void ColAfter()override;
	void Release()override;
	void ReleaseAfter()override;
	void DebugRender() ;


///////////////////////////////////// Render
public:
	RenderManager RMGR;

private:
	void SceneRender();

///////////////////////////////////// Col 
public:
	ColliderManager CMGR;

private:
	void SceneCol();

	//////////////////////////////////// OverList
private:
	std::list<HPTR<Actor>> ExtractOverActor(const wchar_t* _NextSceneName);
	void OverActorPush(std::list<HPTR<Actor>>&& _List);

private:
	Scene();
	~Scene();
};