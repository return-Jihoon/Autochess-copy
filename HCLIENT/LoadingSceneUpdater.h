#pragma once
#include <Scene.h>

class LoadingSceneUpdater : public Scene::Updater
{
private:
	void Loading()		override;
	void SceneUpdate()	override;
	void ChangeEnd()	override;
	void ChangeStart()	override;
	void DebugRender()	override;

private:
	HPTR<Actor> LoadingBar;
	HPTR<Actor> LoadingCircle;
	HPTR<EngineFont> Font;
	HPTR<SpriteRender> LoadingBarSR;

public:
	static bool LobyReady;
	static bool CollectReady;
	static bool StartReady;
	static bool PlayReady;
	static bool EndingReady;

private:
	int Sceneidx;
	int curidx;

	bool loadingSpriteCheck;

public:
	LoadingSceneUpdater();
	~LoadingSceneUpdater();
};

