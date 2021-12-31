#include "Maths.h"
#include "JTime.h"

const float Constant::PI = 3.14159265359f;
const float Constant::R2D = 180.0F / PI;
const float Constant::D2R = PI / 180.0F;

Vector4 Vector4::DLEFT;
Vector4 Vector4::DRIGHT;
Vector4 Vector4::DUP;
Vector4 Vector4::DDOWN;
Vector4 Vector4::DFORWARD;
Vector4 Vector4::DBACK;

const Vector4  Vector4::ILEFTCON() 
{
	Vector4 Value;
	Value.ix = -1;
	Value.iy = 0;
	return Value;
}
const Vector4  Vector4::IDOWNCON() 
{
	Vector4 Value;
	Value.ix = 0;
	Value.iy = -1;
	return Value;
}
const Vector4  Vector4::IRIGHTCON() 
{
	Vector4 Value;
	Value.ix = 1;
	Value.iy = 0;
	return Value;
}
const Vector4  Vector4::IUPCON() 
{
	Vector4 Value;
	Value.ix = 0;
	Value.iy = 1;
	return Value;
}

const Vector4 Vector4::ILEFT = ILEFTCON();
const Vector4 Vector4::IDOWN = IDOWNCON();
const Vector4 Vector4::IRIGHT = IRIGHTCON();
const Vector4 Vector4::IUP = IUPCON();

const Vector4 Vector4::ARRIDIR[4] = { Vector4::ILEFT, Vector4::IDOWN , Vector4::IRIGHT, Vector4::IUP };

const Vector4 Vector4::LEFT = Vector4(-1.0F, 0.0F, 0.0F, 1.0F);
const Vector4 Vector4::RIGHT = Vector4(1.0F, 0.0F, 0.0F, 1.0F);
const Vector4 Vector4::UP = Vector4(0.0F, 1.0F, 0.0F, 1.0F);
const Vector4 Vector4::DOWN = Vector4(0.0F, -1.0F, 0.0F, 1.0F);
const Vector4 Vector4::FORWARD = Vector4(0.0F, 0.0F, 1.0F, 1.0F);
const Vector4 Vector4::BACK = Vector4(0.0F, 0.0F, -1.0F, 1.0F);
const Vector4 Vector4::ZERO = Vector4(0.0F, 0.0F, 0.0F, 0.0F);

Vector4 Vector4::RED = Vector4(1.0F, 0.0F, 0.0F, 1.0F);
Vector4 Vector4::BLUE = Vector4(0.0F, 0.0F, 1.0F, 1.0F);
Vector4 Vector4::GREEN = Vector4(0.0F, 1.0F, 0.0F, 1.0F);
Vector4 Vector4::WHITE = Vector4(1.0F, 1.0F, 1.0F, 1.0F);
Vector4 Vector4::GRAY = Vector4(0.35F, 0.35F, 0.35F, 1.0F);
Vector4 Vector4::BLACK = Vector4(0.0F, 0.0F, 0.0F, 1.0F);
Vector4 Vector4::MAGENTA = Vector4(1.0F, 0.0F, 1.0F, 1.0F);

//bool HMATH::RectToRect()
//{
//	//// ȸ������ �ʴ� ����ü AABB
//	//DirectX::BoundingBox BB1;
//	//DirectX::BoundingBox BB2;
//	//// BB1.Center;
//	//// BB1.Extents;
//	//BB1.Intersects(BB2);
//
//	//// �и��� �̷�.
//	//// ȸ�� �Ҽ� �ִ� ����ü OBB
//	//DirectX::BoundingOrientedBox BOB1;
//	//DirectX::BoundingOrientedBox BOB2;
//	//BB2.Intersects(BOB1);
//
//	//// �и��� �̷�.
//	//// ��������ī�޶��� �浹ü
//	//DirectX::BoundingFrustum BF1;
//	//DirectX::BoundingFrustum BF2;
//	//BB2.Intersects(BOB1);
//
//	//// ��
//	//DirectX::BoundingSphere BS1;
//	//DirectX::BoundingSphere BS2;
//	//BS1.Intersects(BS2);
//
//	//// ��
//	//// DirectX::TriangleTests::Intersects( BS1;
//	//// DirectX::BoundingSphere BS2;
//	//BS1.Intersects(BS2);
//
//}

void Vector4::TimeUpdate()
{
	DLEFT = LEFT * Time::DeltaTime();
	DRIGHT = RIGHT * Time::DeltaTime();
	DUP = UP * Time::DeltaTime();
	DDOWN = DOWN * Time::DeltaTime();
	DFORWARD = FORWARD * Time::DeltaTime();
	DBACK = BACK * Time::DeltaTime();
}