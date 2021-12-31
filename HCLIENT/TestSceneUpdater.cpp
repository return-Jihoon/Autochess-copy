#include "TestSceneUpdater.h"

//BASE
#include <KeyInput.h>
#include <GameWindow.h>
#include <Well512Random.h>
#include <JTime.h>

//ENGINE
#include <GraphicDebug.h>
#include <GridRender.h>
#include <Camera.h>
#include <FreeCamera.h>
#include <FbxAnimation.h>
#include <StaticFbxRender.h>
#include <BoundingBox.h>


//LOGIC
#include <LOGICHEADER.h>
#include <ChessBoard.h>
#include <StatusLogic.h>

//CLIENT
#include "LOGICHEADER.h"

#include <GameWindow.h>
#include <FreeCamera.h>
#include <SpriteRender.h>
#include <RectRender.h>
#include <Texture.h>
#include <Sprite.h>
#include <SpriteAnimaion.h>
#include <KeyInput.h>
#include <Sound.h>
#include <Renderer.h>
#include <GridRender.h>
#include <Texture.h>

#include <BoneChaser.h>
#include <BoundingRect.h>
#include <BoundingCircle.h>
#include <BoundingBox.h>
#include <GraphicDebug.h>
#include <Debug.h>
#include <GameThread.h>
#include <MultiRenderTarget.h>
#include <RenderTarget.h>
#include <BloomFilter.h>


#include <GraphicDebug.h>
#include <FbxAnimation.h>


#include <Terrain.h>
#include <FreeCamera.h>

#include <GameThread.h>


//
#include <ChessBoard.h>
#include <MpMagicion.h>
#include <MonsterLogic.h>
#include <Sound.h>

//#include "EndingSceneUpdater.h"

void TestSceneUpdater::Loading()
{
	Directory Dic;
	Dic.ReplaceParentPath();
	Dic.MoveDirectory(L"BIN");
	Dic.MoveDirectory(L"FBX");

	std::vector<File> AllFileList;
	Dic.GetFilesName(AllFileList, L"*.FBXDATA");

	std::wstring Path;
	for (size_t i = 0; i < AllFileList.size(); i++)
	{
		Path = AllFileList[i].GetFullPath();

		
		if (AllFileList[i].GetFileName() == L"EatingDragon.FBXDATA")
		{
			Resources::Load<Fbx>(Path.c_str(), Fbx::LOADMODE::CONVERT);
		}
	}

	//GRID
	HPTR<Actor> OBJ = GetScene()->CreateActor();
	OBJ->GetTransform()->SetLocalScale({ 10000.0F, 10000.0F, 10000.0F });

	HPTR<GridRender> SR = OBJ->AddComponent<GridRender>(RG_GRID);

#pragma region CAMERA
	
		m_MainCam = GetScene()->CreateActor(L"MAINCAM");
		m_MainCam->GetTransform()->SetLoclaPosition({ 0, 100.0f, -100.0f });
		m_MainCam->GetTransform()->SetLocalRot({ 49.1068573f, 0.586260557f, 0.0f });

		camCom = m_MainCam->AddComponent<Camera>(RG_GRID, RG_PLAYER);
		camCom->Order(0);
		camCom->SetFarValue(100000.0f);
		camCom->SetProjMode(PROJMODE::PM_PERS);
		camCom->SetArea((WIN_SIZE_X / 100), (WIN_SIZE_Y / 100));

		HPTR<FreeCamera> freeCamCom = m_MainCam->AddComponent<FreeCamera>();

#pragma region LIGHT
		//HPTR<Actor> Light01 = GetScene()->CreateActor();
		//Light01->GetTransform()->SetLocalRotX(45.0f);
		//Light01->GetTransform()->SetLocalRotY(45.0f);
		//Light01->GetTransform()->SetLoclaPosition({ 0.0f, 100.0f, 0.0f });
		////DIR Light01->GetTransform()->SetLoclaPosition({ 0.0f, 1000.0f, -1000.0f });
		//LightCheck01 = Light01->AddComponent<Light>(RG_PLAYER, RG_UI);
		//LightCheck01->SetLightType(Light::LT_POINT);
		//LightCheck01->SetRange(200.0f);
		//LightCheck01->SetSpecPow(1);
		//LightCheck01->SetDiffPow(1.1f);
		//LightCheck01->SpecPower(1.0f);

		//HPTR<Actor> Light02 = GetScene()->CreateActor();
		//Light02->GetTransform()->SetLocalRotX(45.0f);
		//Light02->GetTransform()->SetLocalRotY(45.0f);
		//Light02->GetTransform()->SetLoclaPosition({ 250.0f, 100.0f, 0.0f });
		////DIR Light01->GetTransform()->SetLoclaPosition({ 0.0f, 1000.0f, -1000.0f });
		//HPTR<Light> LightCheck02 = Light02->AddComponent<Light>(RG_PLAYER, RG_UI);
		//LightCheck02->SetLightType(Light::LT_POINT);
		//LightCheck02->SetRange(200.0f);
		//LightCheck02->SetSpecPow(1);
		//LightCheck02->SetDiffPow(1.1f);
		//LightCheck02->SpecPower(1.0f);

		HPTR<Actor> Light03 = GetScene()->CreateActor();
		Light03->GetTransform()->SetLocalRotX(45.0f);
		Light03->GetTransform()->SetLocalRotY(45.0f);
		Light03->GetTransform()->SetLoclaPosition({ 0.0f, 1000.0f, -1000.0f });
		HPTR<Light> LightCheck03 = Light03->AddComponent<Light>(RG_PLAYER, RG_UI);
		LightCheck03->SetLightType(Light::LT_DIR);
		LightCheck03->SetSpecPow(1);
		LightCheck03->SetDiffPow(1.1f);
		LightCheck03->SpecPower(1.0f);
#pragma endregion  

		Directory dic;
		dic.ReplaceParentPath();

		std::wstring pathD = dic.GetFullPath();
		pathD += L"\\BIN\\FBX\\FbxTexture\\Brick_D_02.tga";
		HPTR<Texture> texD = Resources::Load<Texture>(pathD.c_str());

		std::wstring pathN = dic.GetFullPath();
		pathN += L"\\BIN\\FBX\\FbxTexture\\Brick_N.tga";
		HPTR<Texture> texN = Resources::Load<Texture>(pathN.c_str());

		std::wstring pathH = dic.GetFullPath();
		pathH += L"\\BIN\\FBX\\FbxTexture\\Brick_H.tga";
		HPTR<Texture> texH = Resources::Load<Texture>(pathH.c_str());


		chessBoardActor = GetScene()->CreateActor(L"ChessBoard");
		chessBoardActor->GetTransform()->SetLoclaPosition({ 0.0f, 0.0f, 0.0F });
		// ¸ÊÀÇ Å©±â
		chessBoardActor->GetTransform()->SetLocalScale({ 1000.0F, 1.0F, 1000.0F });
		chessBoardActor->GetTransform()->LocalScaleMul(1.0f);

		chessBoardTerrain = chessBoardActor->AddComponent<Terrain>(RG_PLAYER);
		chessBoardTerrain->CreateTerrain(1, 1, L"Brick_D_02.tga", L"Brick_H.tga", 1000.0f, 1.0f);
		//MAPCOM->FloorTextureSetting(1, L"BUMPTEST.png", L"TILE02_S.png", 0.1F);

		chessBoardTerrain->FloorBumpSetting(0, L"Brick_N.tga");


		HPTR<Actor> chessPlayer = GetScene()->CreateActor();
		chessPlayer->GetTransform()->SetLoclaPosition({ 0.0f, 50.0f, 0.0F });

		HPTR<FbxAnimation> chessPlayerAni = chessPlayer->AddComponent<FbxAnimation>(RG_PLAYER);
		chessPlayerAni->FbxSetting(L"EatingDragon.FBXDATA");
		chessPlayerAni->CreateAnimation(L"ATT", 0, 919, true);
		//SR->CreateAnimation(L"ATT", 886, 909, true);
		chessPlayerAni->ChangeAnimation(L"ATT");


}

void TestSceneUpdater::SceneUpdate()
{
}

void TestSceneUpdater::ChangeEnd()
{
}

void TestSceneUpdater::ChangeStart()
{
}

void TestSceneUpdater::DebugRender()
{
#pragma region DEBUGRENDER

	Vector4 Pos;
	Pos = { -700 , 350 };
	Vector4 Size;
	Size = { 200, 150 };

	GraphicDebug::DrawTexture(camCom->GetDeferredTarget()->Target(0)->GetTex(), Pos, Size);
	Pos.x += Size.x;
	GraphicDebug::DrawTexture(camCom->GetDeferredTarget()->Target(1)->GetTex(), Pos, Size);
	Pos.x += Size.x;
	GraphicDebug::DrawTexture(camCom->GetDeferredTarget()->Target(2)->GetTex(), Pos, Size);
	Pos.x += Size.x;
	GraphicDebug::DrawTexture(camCom->GetDeferredTarget()->Target(3)->GetTex(), Pos, Size);

	//Pos = { -650 , 450 - Size.y };
	Pos.x += Size.x;
	GraphicDebug::DrawTexture(camCom->GetLightTarget()->Target(0)->GetTex(), Pos, Size);
	Pos.x += Size.x;
	GraphicDebug::DrawTexture(camCom->GetLightTarget()->Target(1)->GetTex(), Pos, Size);

	if (nullptr != BFilter)
	{
		Pos.x += Size.x;
		GraphicDebug::DrawTexture(BFilter->SmallTaregt->GetTex(), Pos, Size/*, HVEC4{128, 128}*/);
		Pos.x += Size.x;
		GraphicDebug::DrawTexture(BFilter->SSmallTaregt->GetTex(), Pos, Size/*, HVEC4{128, 128}*/);
	}

	if (nullptr != LightCheck01)
	{
		Pos.x += Size.x;
		GraphicDebug::DrawTexture(LightCheck01->m_ShadowTarget->GetTex(), Pos, Size/*, HVEC4{128, 128}*/);
	}

	Pos = { -700 , 350 };
	Pos.y -= Size.y;
	GraphicDebug::DrawTexture(camCom->GetDeferredTarget()->Target(4)->GetTex(), Pos, Size);
	
	//Pos = { -700 , 350 };
	Pos.x += Size.x;
	GraphicDebug::DrawTexture(camCom->GetDeferredTarget()->Target(5)->GetTex(), Pos, Size);

#pragma endregion
}

TestSceneUpdater::TestSceneUpdater()
{
}


TestSceneUpdater::~TestSceneUpdater()
{
}
