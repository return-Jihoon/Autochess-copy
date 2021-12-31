#include "InitFunc.h"
#include <Path.h>
#include <Resources.h>
#include <KeyInput.h>
#include <Texture.h>
#include <Sprite.h>
#include <Scene.h>
#include <GameWindow.h>

#include "LobySceneUpdater.h"
#include "PlaySceneUpdater.h"
#include "LoadingSceneUpdater.h"
#include "StartSceneUpdater.h"
#include "CollectSceneUpdater.h"
#include "EndingSceneUpdater.h"
#include "TestSceneUpdater.h"

#include <LOGICHEADER.h>

#include <Debug.h>

void ClientInit() 
{
	LOGICVALUE::Init();

	GameWindow::MainGameWin()->CreateScene(L"LoadingScene",	new LoadingSceneUpdater());
	GameWindow::MainGameWin()->CreateScene(L"LobyScene",	new LobySceneUpdater());
	GameWindow::MainGameWin()->CreateScene(L"CollectScene",	new CollectSceneUpdater());
	GameWindow::MainGameWin()->CreateScene(L"StartScene",	new StartSceneUpdater());
	GameWindow::MainGameWin()->CreateScene(L"PlayScene",	new PlaySceneUpdater());
	GameWindow::MainGameWin()->CreateScene(L"EndingScene",	new EndingSceneUpdater());


	GameWindow::MainGameWin()->CreateScene(L"TestScene", new TestSceneUpdater());

	GameWindow::MainGameWin()->ChangeScene(L"TestScene");


}