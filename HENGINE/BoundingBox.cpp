#include "BoundingBox.h"
#include "Transform.h"
#include "BoundingSphere.h"
#include "GraphicDebug.h"


BoundingBox::BoundingBox()
{
}


BoundingBox::~BoundingBox()
{
}


void BoundingBox::ColBefore()
{
	// z���� ���� �Ⱥ��ϼ� �ִ�.

	DebugCheck();
	UpdateTransform();
	// z���� ���� �Ⱥ��ϼ� �ִ�.

	m_ColliderData.Center = GetPosition().xmFloat3;
	m_ColliderData.Extents = (GetScale() * 0.5f).xmFloat3;
	// ������� ���ؼ� �������ش�.
	// ���Ҽ� ����� ȸ�� ���3X3�� �����
	Rot = GetTransform()->GetRadRotation();
	DirectX::XMStoreFloat4(&m_ColliderData.Orientation, DirectX::XMQuaternionRotationRollPitchYaw(Rot.x, Rot.y, Rot.z));
	//Rot = Trans()->WRot();
	//DirectX::XMStoreFloat4(&ColData.Orientation, DirectX::XMQuaternionRotationRollPitchYaw(Rot.x, Rot.y, Rot.z));

	if (GraphicDebug::IsDebugCheck())
	{
		GraphicDebug::DrawBox(Camera::GetMainCam(), GetWorldMatrix());
	}
}

bool BoundingBox::GeometryCheck(Collider* _Other)
{
	if (true == _Other->IsType<BoundingBox>())
	{
		return m_ColliderData.Intersects(((BoundingBox*)_Other)->m_ColliderData);
	} else if (true == _Other->IsType<BoundingSphere>())
	{
		return m_ColliderData.Intersects(((BoundingSphere*)_Other)->m_ColliderData);
	}

	return false;
}