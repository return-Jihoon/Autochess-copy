#include "BoundingCircle.h"
#include "BoundingRect.h"
#include "Transform.h"
#include "GraphicDebug.h"
// ���� ���ο��� �浹ü�� ������ 
// ��Ȱ�� ���ÿ� �Ұ����� üũ�غ���.

BoundingCircle::BoundingCircle()
{
}

BoundingCircle::~BoundingCircle()
{
}

void BoundingCircle::ColBefore()
{
// xyz�� ���� ū�༮�� ����
	DebugCheck();
	UpdateTransform();

	m_ColliderData.Center = GetTransform()->GetPosition().xmFloat3;
	m_ColliderData.Center.z = 0.0f;
	m_ColliderData.Radius = GetScale().x * 0.5f;

	if (GraphicDebug::IsDebugCheck())
	{
		GraphicDebug::DrawCircle(Camera::GetMainCam(), GetWorldMatrix());
	}
}

bool BoundingCircle::GeometryCheck(Collider* _Other)
{
	if (true == _Other->IsType<BoundingCircle>())
	{
		return m_ColliderData.Intersects(((BoundingCircle*)_Other)->m_ColliderData);
	}
	else if (true == _Other->IsType<BoudingRect>())
	{
		return m_ColliderData.Intersects(((BoudingRect*)_Other)->m_ColliderData);
	}

	return false;
}