#pragma once
#include "Collider.h"
// 2Ʋ ���� ����������� 4�� 
// �ƹ��� ���Ƶ� ������.
// #include ""

class BoundingBox : public Collider
{
public:
	friend class BoundingSphere;

private:
	DirectX::BoundingOrientedBox m_ColliderData;
	Vector4 Rot;

public:
	void ColBefore() override;
	bool GeometryCheck(Collider* _Other) override;

public:
	BoundingBox();
	~BoundingBox();
};

