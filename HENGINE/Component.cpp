#include "Component.h"

Component::Component() 
{
}


Component::~Component()
{
}

void Component::ComponentInit() 
{
	m_pTrans = m_pActor->GetTransform();
}

void Component::SceneChangeStart() 
{
	// ���Ϳ� �ٲ���� ���õ� ������ ����ȴ�
	// ����� ��������.
}