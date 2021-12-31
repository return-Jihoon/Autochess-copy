#include "BoundingRect.h"
#include "Transform.h"
#include "GraphicDebug.h"



BoudingRect::BoudingRect()
{
}


BoudingRect::~BoudingRect()
{
}

void BoudingRect::ColBefore()
{
	DebugCheck();
	UpdateTransform();
	// z���� ���� �Ⱥ��ϼ� �ִ�.

	m_ColliderData.Center = GetPosition().xmFloat3;
	m_ColliderData.Center.z = 0.0f;

	m_ColliderData.Extents = (GetScale() * 0.5f).xmFloat3;
	m_ColliderData.Extents.z = 1.0f;
	// ������� ���ؼ� �������ش�.
	// ���Ҽ� ����� ȸ�� ���3X3�� �����
	// ȸ��

	Rot = GetTransform()->GetRadRotation();
	DirectX::XMStoreFloat4(&m_ColliderData.Orientation, DirectX::XMQuaternionRotationRollPitchYaw(Rot.x, Rot.y, Rot.z));

	if (GraphicDebug::IsDebugCheck())
	{
		GraphicDebug::DrawRect(Camera::GetMainCam(), GetWorldMatrix());
	}
}

bool BoudingRect::GeometryCheck(Collider* _Other)
{
	// hvec4
	// hvec2
	// �������� �ٿ�ĳ������ �Ⱦ��
	if (true == _Other->IsType<BoudingRect>())
	{
		return m_ColliderData.Intersects(((BoudingRect*)_Other)->m_ColliderData);
	}

	return false;
}