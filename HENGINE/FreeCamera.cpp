#include "FreeCamera.h"
#include <KeyInput.h>
#include "GameWindow.h"
#include <JTime.h>


FreeCamera::FreeCamera() : m_Speed(30.0f), m_RotXSpeed(100.0f), m_RotYSpeed(100.0f), isInit(false)
{
}


FreeCamera::~FreeCamera()
{
}

void FreeCamera::Trace(HPTR< Transform> _Trace, Vector4 _Pos, Vector4 _Rot)
{
	m_Trace = _Trace;
	GetActor()->SetParent(m_Trace->GetActor());

	GetTransform()->SetLoclaPosition(_Pos);
	GetTransform()->SetLocalRot(_Rot);
}


void FreeCamera::Init()
{
	if (nullptr == GetActor()->GetComponent<Camera>())
	{
		BOOM;
	}

	// GetActor()->Trans()->LRotY(45.0f);
	


	// ����ī�޶�� ������ Ű�� �����̹Ƿ�
	// ���࿡ �׿� �ش��ϴ� Ű�� ���ٸ�
	// ���⼭ ����� �����Ѵ�.
	if (false == Input::IsKey(L"CAMLEFT")) { Input::CreateKey(L"CAMLEFT", 'A'); }
	if (false == Input::IsKey(L"CAMRIGHT")) { Input::CreateKey(L"CAMRIGHT", 'D'); }
	if (false == Input::IsKey(L"CAMFORWARD")) { Input::CreateKey(L"CAMFORWARD", 'W'); }
	if (false == Input::IsKey(L"CAMBACK")) { Input::CreateKey(L"CAMBACK", 'S'); }
	if (false == Input::IsKey(L"CAMUP")) { Input::CreateKey(L"CAMUP", 'E'); }
	if (false == Input::IsKey(L"CAMDOWN")) { Input::CreateKey(L"CAMDOWN", 'Q'); }
	if (false == Input::IsKey(L"CAMMOVE")) { Input::CreateKey(L"CAMMOVE", VK_RBUTTON); }
	if (false == Input::IsKey(L"CLICK")) { Input::CreateKey(L"CLICK", VK_LBUTTON); }
	if (false == Input::IsKey(L"CAMBOOST")) { Input::CreateKey(L"CAMBOOST", VK_LSHIFT); }
	if (false == Input::IsKey(L"SPACE")) { Input::CreateKey(L"SPACE", VK_SPACE); }
}
void FreeCamera::Update()
{
	if (nullptr != m_Trace)
	{
		return;
	}

	if (true == Input::Press(L"CAMMOVE"))
	{
		// ���콺�� �������ٸ�
		if (GameWindow::MainGameWin()->MouseDir() != Vector4::ZERO)
		{
			// ȭ��������� 
			// ȭ�� �ʺ� ���� �ΰ��� ���� �ٸ���.
			GetActor()->GetTransform()->LocalRotYSum(GameWindow::MainGameWin()->MouseDir().x * Time::SDeltaTime(m_RotXSpeed));
			GetActor()->GetTransform()->LocalRotXSum(GameWindow::MainGameWin()->MouseDir().y * Time::SDeltaTime(m_RotYSpeed));
		}

		if (true == Input::Press(L"CAMBOOST"))
		{
			// ����Ʈ ����Ʈ ���ٿ��� ����?

			m_Speed = 300.0f;
		}
		else {
			m_Speed = 30.0f;
		}

		if (true == Input::Press(L"CAMLEFT"))
		{
			// ����Ʈ ����Ʈ ���ٿ��� ����?

			GetActor()->GetTransform()->LocalTranslate(GetActor()->GetTransform()->LocalLookLeft() * Time::SDeltaTime(m_Speed));

		}
		if (true == Input::Press(L"CAMRIGHT"))
		{
			GetActor()->GetTransform()->LocalTranslate(GetActor()->GetTransform()->LocalLookRight() * Time::SDeltaTime(m_Speed));
		}
		if (true == Input::Press(L"CAMFORWARD"))
		{
			GetActor()->GetTransform()->LocalTranslate(GetActor()->GetTransform()->LocalLookForward() * Time::SDeltaTime(m_Speed));
		}
		if (true == Input::Press(L"CAMBACK")) {
			GetActor()->GetTransform()->LocalTranslate(GetActor()->GetTransform()->LocalLookBack() * Time::SDeltaTime(m_Speed));
		}
		if (true == Input::Press(L"CAMUP")) {
			GetActor()->GetTransform()->LocalTranslate(GetActor()->GetTransform()->LocalLookUp() * Time::SDeltaTime(m_Speed));
		}
		if (true == Input::Press(L"CAMDOWN")) {
			GetActor()->GetTransform()->LocalTranslate(GetActor()->GetTransform()->LocalLookDown() * Time::SDeltaTime(m_Speed));
		}

	}
	else
	{
		//if (isInit == false)
		//{
		//	m_StartPos = GetActor()->GetTransform()->GetLocalPosition();
		//	m_StartRot = GetActor()->GetTransform()->GetLocalRotation();

		//	isInit = true;
		//}


		//GetActor()->GetTransform()->SetLoclaPosition(m_StartPos);
		//GetActor()->GetTransform()->SetLocalRot(m_StartRot);

	}

}
