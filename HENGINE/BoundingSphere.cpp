#include "Transform.h"
#include "BoundingSphere.h"
#include "BoundingBox.h"
#include "GraphicDebug.h"

BoundingSphere::BoundingSphere()
{
}


BoundingSphere::~BoundingSphere()
{
}


void BoundingSphere::ColBefore()
{
	// xyz�� ���� ū�༮�� ����
	DebugCheck();
	UpdateTransform();

	m_ColliderData.Center = GetPosition().xmFloat3;
	m_ColliderData.Radius = GetScale().x * 0.5f;

	if (GraphicDebug::IsDebugCheck())
	{
		GraphicDebug::DrawSphere(Camera::GetMainCam(), GetWorldMatrix());
	}
}

bool BoundingSphere::GeometryCheck(Collider* _Other)
{
	if (true == _Other->IsType<BoundingSphere>())
	{
		return m_ColliderData.Intersects(((BoundingSphere*)_Other)->m_ColliderData);
	}
	else if (true == _Other->IsType<BoundingBox>())
	{
		return m_ColliderData.Intersects(((BoundingBox*)_Other)->m_ColliderData);
	} 

	return false;
}