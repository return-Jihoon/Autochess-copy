#pragma once
#include <Scene.h>


class TestSceneUpdater : public Scene::Updater
{
private:
	HPTR<Actor> m_MainCam;
	HPTR<Camera> camCom;

	HPTR<BloomFilter> BFilter;
	HPTR<Light> LightCheck01;

	HPTR<Actor> chessBoardActor;
	HPTR<Terrain> chessBoardTerrain;

private:
	void Loading()		override;
	void SceneUpdate()	override;
	void ChangeEnd()	override;
	void ChangeStart()	override;
	void DebugRender()	override;


public:
	TestSceneUpdater();
	~TestSceneUpdater();
};

