#include "StartSceneUpdater.h"

#include <KeyInput.h>
#include <GameWindow.h>

#include <GraphicDebug.h>

#include <LOGICHEADER.h>
#include <GameThread.h>
#include <Video.h>
#include <Sound.h>

CriticalSection CS;
unsigned __stdcall StartThread(Thread* _Thread, void* _Arg)
{
	
		std::wcout << L"��ŸƮ ������ ������" << std::endl;
	
	
	return 0;
}


StartSceneUpdater::StartSceneUpdater()
{
}


StartSceneUpdater::~StartSceneUpdater()
{
}

void StartSceneUpdater::Loading()
{
	//Video loadingVideo;
	//loadingVideo.SetVideoFileDirectory(L"..\\BIN\\VIDEO\\StartMovie.avi");
	//loadingVideo.PlayVideoFile();
	//int a = 0;

	
}
void StartSceneUpdater::SceneUpdate()
{/*
	if (Input::Down(L"PLAY") == true)
	{
		GameWindow::MainGameWin()->ChangeScene(L"PlayScene");
	}*/
	int a = 0;

	GameWindow::MainGameWin()->ChangeScene(L"PlayScene");
}
void StartSceneUpdater::ChangeEnd()
{

}
void StartSceneUpdater::ChangeStart()
{

}
void StartSceneUpdater::DebugRender()
{
	GraphicDebug::DrawFontUI(L"START SCENE", Vector4(0.0f, 0.0f, 0.0f, 1.0f));
}