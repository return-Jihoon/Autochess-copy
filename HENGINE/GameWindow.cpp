#include "GameWindow.h"
#include "Sound.h"
#include <KeyInput.h>
#include "RenderManager.h"

//////////////////////////////////// static

std::map<std::wstring, HPTR<GameWindow>>::iterator GameWindow::StartGameWin;
std::map<std::wstring, HPTR<GameWindow>>::iterator GameWindow::EndGameWin;
std::map<std::wstring, HPTR<GameWindow>> GameWindow::g_GameWinMap;
GameWindow* GameWindow::m_MainGameWin = nullptr;

void GameWindow::EngineLoop()
{
	// �ε��� ��������
	// ó��.
	Sound::Init();
	Time::Reset();
	Window::BasicPeekLoop(WindowUpdate);
}

void __stdcall GameWindow::WindowUpdate()
{
	Sound::Update();
	Time::Update();
	Input::Update();
	Vector4::TimeUpdate();

	StartGameWin = g_GameWinMap.begin();
	EndGameWin = g_GameWinMap.end();

	for (; StartGameWin != EndGameWin; ++StartGameWin)
	{
		// ���콺 ���� ���
		StartGameWin->second->Update();
		// ������ ������Ʈ �ϴµ�.
		StartGameWin->second->SceneUpdate();
	}
}

GameWindow::GameWindow() : NextScene(nullptr), CurScene(nullptr)
{
}


GameWindow::~GameWindow()
{
}


void GameWindow::SceneUpdate() 
{
	// �� ó��
	if (nullptr != NextScene)
	{
		if (NextScene == CurScene)
		{
			BOOM;
		}

		// ���� ���� ������.
		if (nullptr != CurScene)
		{
			CurScene->ChangeEnd();
			NextScene->OverActorPush(CurScene->ExtractOverActor(NextScene->GetName()));
		}

		// �̹� ���ʹ� �Űܿ� �ִ°� ������.

		NextScene->LoadingCheck();
		CurScene = NextScene;
		CurScene->ChangeStart();
		NextScene = nullptr;
	}

	CurScene->Progress();
}

HPTR<GameWindow> GameWindow::FindGameWin(const wchar_t* _WinName) 
{
	std::map<std::wstring, HPTR<GameWindow>>::iterator FindIter 
		= g_GameWinMap.find(_WinName);

	if (FindIter != g_GameWinMap.end())
	{
		return FindIter->second;
	}

	return nullptr;
}

HPTR<GameWindow> GameWindow::CreateGameWin(const wchar_t* _WinName)
{
	if (nullptr != FindGameWin(_WinName))
	{
		BOOM;
	}

	GameWindow* NewGameWin = new GameWindow();
	NewGameWin->SetName(_WinName);

	// ����� �����ϱ� ��¥ ����� ����.
	if (false == NewGameWin->Create(L"Default", _WinName))
	{
		// �����ߴٸ� ��Ʈ��.
		BOOM;
		return nullptr;
	}

	if (0 == g_GameWinMap.size())
	{
		m_MainWindow = NewGameWin;
		m_MainGameWin = NewGameWin;
	}

	NewGameWin->Show();
	g_GameWinMap.insert(std::map<std::wstring, HPTR<GameWindow>>::value_type(_WinName, NewGameWin));
	InsertOtherWindow(NewGameWin);

	return NewGameWin;
}

void GameWindow::ChangeScene(const wchar_t* _SceneName)
{
	if (nullptr != CurScene && _SceneName == CurScene->CWStringName())
	{
		return;
	}

	std::map<std::wstring, HPTR<Scene>>::iterator FindIter 
		= m_SceneMap.find(_SceneName);

	if (FindIter == m_SceneMap.end())
	{
		BOOM;
	}

	NextScene = FindIter->second;
}

void GameWindow::CreateDevice() 
{
	m_HDevice = new GraphicDevice();
	m_HDevice->Init(this);
	// �����Ŵ����� �̴��� �������ٰ��̴�.
	// ����̽��� �����°� 
}

HPTR<GameWindow> GameWindow::CreateGameWin(const wchar_t* _WinName, HWND _Hwnd) 
{
	if (nullptr == _Hwnd)
	{
		BOOM;
	}

	GameWindow* NewGameWin = new GameWindow();
	NewGameWin->SetName(_WinName);
	NewGameWin->m_HWnd = _Hwnd;
	NewGameWin->Init();
	if (0 == g_GameWinMap.size())
	{
		m_MainWindow = NewGameWin;
		m_MainGameWin = NewGameWin;
	}

	g_GameWinMap.insert(std::map<std::wstring, HPTR<GameWindow>>::value_type(_WinName, NewGameWin));
	InsertOtherWindow(NewGameWin);

	return NewGameWin;
}