#pragma once

#include <Windows.h>
#include <math.h>
#include <vector>
#include "JTemplate.h"

#include "Debug.h"
#include <DirectXCollision.h> // �浹�� ����
#include <DirectXCollision.inl>
#include <DirectXPackedVector.h> // d3dvector ���͸� ����ϱ� ���� ����ü

// _XM_NO_INTRINSICS_ SSE���� ������� �ʰڴٴ� ��.
//#ifdef X32
//#define _XM_NO_INTRINSICS_
//#endif

class Constant 
{
public:
	// ���ȿ� �̰� �����ָ� ��׸��� �ȴ�.
	// (180.0f / ����)
	static const float PI;
	// 3.14���ȿ� �̰� �����ָ�? 180F
	// 180;
	static const float R2D;
	// 90���� �̰� �����ָ�? 1.57                  
	// 180���� �̰� �����ָ�? 3.14
	static const float D2R;
};

struct BoardIndex
{
public:
	union
	{
		struct
		{
			int x;
			int z;
		};
	};

public:
	BoardIndex operator-(int _Num)
	{
		BoardIndex temp;
		temp.x -= _Num;
		temp.z -= _Num;


		return temp;
	}

	BoardIndex operator-(BoardIndex& _Other)
	{
		BoardIndex temp;

		temp.x =  /*this.*/x - _Other.x;
		temp.z =  /*this.*/z - _Other.z;

		return temp;
	}

	void operator-=(int _Value)
	{
		x -= _Value;
		z -= _Value;
	}

	bool operator==(BoardIndex& _Other)
	{
		return (this->x == _Other.x) && (this->z == _Other.z);
	}

	bool operator!=(BoardIndex& _Other)
	{
		return (this->x != _Other.x) || (this->z != _Other.z);
	}

public:

	BoardIndex() : x(0), z(0)
	{
	}
	BoardIndex(size_t _Z, size_t _X) : x((int)_X), z((int)_Z)
	{
	}

	BoardIndex(int _Z, int _X) : x(_X), z(_Z)
	{
	}
};

struct Vector2 
{
public:
	union 
	{
		struct 
		{
			float x;
			float y;
		};

	};

	Vector2() : x(0.0F), y(0.0F)
	{
	}


	Vector2(float _x, float _y) : x(_x), y(_y)
	{	
	}
};

class Vector3 
{
public:
	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};
		Vector2 Vec2;
	};
};

// class HMAT;
struct Vector4 
{
private:
	friend class GameWindow;

private:
	static const Vector4 ILEFTCON();
	static const Vector4 IDOWNCON();
	static const Vector4 IRIGHTCON();
	static const Vector4 IUPCON();

public:
	static const Vector4 ILEFT;
	static const Vector4 IDOWN;
	static const Vector4 IRIGHT;
	static const Vector4 IUP;
	
	static const Vector4 ARRIDIR[4];

	static const Vector4 LEFT;
	static const Vector4 RIGHT;
	static const Vector4 UP;
	static const Vector4 DOWN;
	static const Vector4 FORWARD;
	static const Vector4 BACK;
	static const Vector4 ZERO;

	static Vector4 RED;
	static Vector4 BLUE;
	static Vector4 GREEN;
	static Vector4 WHITE;
	static Vector4 GRAY;
	static Vector4 BLACK;
	static Vector4 MAGENTA;

public:
	static Vector4 DLEFT;
	static Vector4 DRIGHT;
	static Vector4 DUP;
	static Vector4 DDOWN;
	static Vector4 DFORWARD;
	static Vector4 DBACK;

private:
	static void TimeUpdate();

public:
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};

		struct
		{
			Vector2 Pos;
			Vector2 Size;
		};

		float Arr[4];
		Vector2 Vec2;
		Vector3 Vec3;
		DirectX::XMFLOAT4 xmFloat4;
		DirectX::XMFLOAT3 xmFloat3;
		// DirectX::XMVECTOR XMVEC;

#ifdef X64
		DirectX::XMVECTOR xmVector;
#endif


		struct
		{
			int ix;
			int iy;
			int iz;
			int iw;
		};

		struct
		{
			__int64 KeyPos;
			__int64 KeyScale;
		};

	};

public:
	float HX() { return x * 0.5f; }
	float HY() { return y * 0.5f; }
	float HZ() { return z * 0.5f; }
	float HW() { return w * 0.5f; }

	int IX() { return (int)x; }
	int IY() { return (int)y; }
	int IZ() { return (int)z; }
	int IW() { return (int)w; }
	unsigned int UIX() { return (unsigned int)x; }
	unsigned int UIY() { return (unsigned int)y; }
	unsigned int UIZ() { return (unsigned int)z; }
	unsigned int UIW() { return (unsigned int)w; }

public:
	void CheckToModifyMax(float _MinValue, float _MaxValue) 
	{
		if (x < _MinValue) { x = _MinValue; }
		if (x > _MaxValue) { x = _MaxValue; }
		if (y < _MinValue) { y = _MinValue; }
		if (y > _MaxValue) { y = _MaxValue; }
		if (z < _MinValue) { z = _MinValue; }
		if (z > _MaxValue) { z = _MaxValue; }
		if (w < _MinValue) { w = _MinValue; }
		if (w > _MaxValue) { w = _MaxValue; }
	}

	UINT ConToUIntColorRGBA() const
	{
		Vector4 ColorVec4 = *this;

		ColorVec4.CheckToModifyMax(0.0f, 1.0f);

		UINT Color = 0;
		unsigned char* P = (unsigned char*)&Color;

		P[0] = (unsigned char)(ColorVec4.x * 255);
		P[1] = (unsigned char)(ColorVec4.y * 255);
		P[2] = (unsigned char)(ColorVec4.z * 255);
		P[3] = (unsigned char)(ColorVec4.w * 255);

		return Color;
	}

	static Vector4 Normalization(const Vector4& _Value)
	{
		float dis = _Value.Distance();
		return { _Value.x / dis, _Value.y / dis, _Value.z / dis };
	}

	// ��ȯ��Ģ�� �������� �ʴ´�.
	static Vector4 CrossProduct(const Vector4& _Left, const Vector4& _Right)
	{
		// ������ ���ΰ� �����Ͷ�� 0���Ͱ� ���´�.
		return DirectX::XMVector3Cross(_Left, _Right);
		// ����ȯ ������ 
		 ;

		//Return.x = (_Left.y * _Right.z) - (_Left.z * _Right.y);
		//Return.y = (_Left.z * _Right.x) - (_Left.x * _Right.z);
		//Return.z = (_Left.x * _Right.y) - (_Left.y * _Right.x);
		//Return.w = 0.0f;
	}

	// ������ ����� �׻� ��Į��.
	static float DotProduct(const Vector4& _Left, const Vector4& _Right)
	{
		// ������ ���ΰ� �����Ͷ�� 0���Ͱ� ���´�.

		// DotResult �ȿ� ����ִ� 4���� ����??? ��δ� ���� ��. 
		DirectX::XMVECTOR DotResult = DirectX::XMVector3Dot(_Left, _Right);
		return DotResult.m128_f32[0];
		// return _Left.x * _Right.x + _Left.y * _Right.y + _Left.z * _Right.z;
	}

public:
	// ���ΰ� �� float�϶� int�� �������ִ� �Լ�
	void ConToInt(float _DefValue = 0.0f)
	{
		ix = (int)(x + _DefValue);
		iy = (int)(y + _DefValue);
		iz = (int)(z + _DefValue);
		iw = (int)(w + _DefValue);
	}

	void Set(const float _Value) 
	{
		x = y = z = _Value;
	}

	void RtoQ(Vector4 Rot)
	{
#ifdef X64
		*this = Rot;
		xmVector = DirectX::XMQuaternionRotationRollPitchYaw(x, y, z);
#else
		*this = Rot;
		DirectX::XMStoreFloat4(&XMF4, DirectX::XMQuaternionRotationRollPitchYaw(x, y, z));
#endif
	}

	void RtoQ()
	{
		// ��Ÿ����� ����
		// ������ x * x + y*y

#ifdef X64
		xmVector = DirectX::XMQuaternionRotationRollPitchYaw(x, y, z);
#else
		DirectX::XMStoreFloat4(&XMF4, DirectX::XMQuaternionRotationRollPitchYaw(x, y, z));
#endif


		;
		// X Y

	}

	void QtoR()
	{
		Vector4 Q = *this;
		QtoR(Q);
	}

	void QtoR(const Vector4& _Q)
	{
		float dx = _Q.x;
		float dy = _Q.y;
		float dz = _Q.z;
		float dw = _Q.w;

		float sqx = _Q.x * _Q.x;
		float sqy = _Q.y * _Q.y;
		float sqz = _Q.z * _Q.z;
		float sqw = _Q.w * _Q.w;


		x = asinf(2.0f * (dw * dx - dy * dz));
		y = atan2f(2.0f * (dx * dz + dw * dy), -sqx - sqy + sqz + sqw);
		z = atan2f(2.0f * (dx * dy + dw * dz), -sqx + sqy - sqz + sqw);
	}


	float Distance() const // ||v|| ������ ����
	{
		// ��Ÿ����� ����
		// ������ x * x + y*y

		return sqrtf((x * x) + (y * y) + (z * z));
		// X Y

	}

	void Normalization()
	{
		float Len = Distance();

		if (0 != Len)
		{
			x /= Len;
			y /= Len;
			z /= Len;
			w = 1.0f;
		}
	}

	void Normal3DToWZero()
	{
		float Len = Distance();

		if (0 != Len)
		{
			x /= Len;
			y /= Len;
			z /= Len;
			w = 0.0f;
		}
	}

	Vector4 ReturnNormalization()
	{
		// ��Ÿ����� ����
		// ������ x * x + y*y
		Vector4 Vec = *this;
		Vec.Normalization();
		return Vec;
		// X Y

	}

// + and +=

	//operator int() {
	//}

	operator DirectX::XMVECTOR() const
	{
#ifdef X64
		return xmVector;
#else
		// 16����Ʈ ���ķ� �����Ѱ� ����.
		return DirectX::XMLoadFloat4(&XMF4);
#endif
	}

	bool operator==(const Vector4& _Other)
	{
		return x == _Other.x && y == _Other.y && z == _Other.z;
	}

	bool operator!=(const Vector4& _Other)
	{
		return !operator==(_Other);
	}

	Vector4 operator+(const float _Scale)
	{
		return { x + _Scale, y + _Scale, z + _Scale };
	}
	Vector4 operator/(const float _Scale)
	{
		return { x / _Scale, y / _Scale, z / _Scale };
	}

	Vector4 operator+(const Vector2& _Scale)
	{
		return { x + _Scale.x, y + _Scale.y };
	}

	Vector4 operator+(const Vector3& _Scale)
	{
		return { x + _Scale.x, y + _Scale.y, z + _Scale.z };
	}

	Vector4 operator+(const Vector4& _Scale)
	{
		return { x + _Scale.x, y + _Scale.y, z + _Scale.z };
	}


	Vector4& operator+=(const float _Scale)
	{
		x += _Scale;
		y += _Scale;
		z += _Scale;

		return *this;
	}

	Vector4& operator+=(const Vector2& _Scale)
	{
		x += _Scale.x;
		y += _Scale.y;

		return *this;
	}

	Vector4& operator+=(const Vector3& _Scale)
	{
		x += _Scale.x;
		y += _Scale.y;
		z += _Scale.z;
		return *this;
	}

	Vector4& operator+=(const Vector4& _Scale)
	{
		x += _Scale.x;
		y += _Scale.y;
		z += _Scale.z;
		return *this;
	}


// - and -=
	Vector4 operator-() const
	{
		return { -x, -y, -z};
	}

	Vector4 operator-(const float _Scale) const
	{
		return { x - _Scale, y - _Scale, z - _Scale };
	}

	Vector4 operator-(const Vector2& _Scale) const
	{
		return { x - _Scale.x, y - _Scale.y };
	}

	Vector4 operator-(const Vector3& _Scale) const
	{
		return { x - _Scale.x, y - _Scale.y, z - _Scale.z };
	}
	
	Vector4 operator-(const Vector4& _Scale) const
	{
		return { x - _Scale.x, y - _Scale.y, z - _Scale.z };
	}


	Vector4& operator-=(const float _Scale)
	{
		x -= _Scale;
		y -= _Scale;
		z -= _Scale;

		return *this;
	}

	Vector4& operator-=(const Vector2& _Scale)
	{
		x -= _Scale.x;
		y -= _Scale.y;

		return *this;
	}

	Vector4& operator-=(const Vector3& _Scale)
	{
		x -= _Scale.x;
		y -= _Scale.y;
		z -= _Scale.z;
		return *this;
	}

	Vector4& operator-=(const Vector4& _Scale)
	{
		x -= _Scale.x;
		y -= _Scale.y;
		z -= _Scale.z;
		return *this;
	}

// * and *=
	Vector4 operator*(const float _Scale) const 
	{
		return {x * _Scale, y * _Scale, z * _Scale};
	}

	Vector4 operator*(const Vector2& _Scale) const
	{
		return { x * _Scale.x, y * _Scale.y};
	}

	Vector4 operator*(const Vector3& _Scale) const
	{
		return { x * _Scale.x, y * _Scale.y, z * _Scale.z };
	}

	Vector4 operator*(const Vector4& _Scale) const
	{
		return { x * _Scale.x, y * _Scale.y, z * _Scale.z };
	}


	Vector4& operator*=(const float _Scale)
	{
		x *= _Scale;
		y *= _Scale;
		z *= _Scale;

		return *this;
	}

	Vector4& operator*=(const Vector2& _Scale)
	{
		x *= _Scale.x;
		y *= _Scale.y;

		return *this;
	}

	Vector4& operator*=(const Vector3& _Scale)
	{
		x *= _Scale.x;
		y *= _Scale.y;
		z *= _Scale.z;
		return *this;
	}

	Vector4& operator*=(const Vector4& _Scale)
	{
		x *= _Scale.x;
		y *= _Scale.y;
		z *= _Scale.z;
		return *this;
	}

// Rot
	// ȸ����Ű�� �ʹ�.
	// 40�� ȸ����
	// ���� 1�� ���Ͱ� �������� ȸ���� ���͸� �����.
	Vector4& RotateX_Degree(float _Deg)
	{
		return RotateX_Radian(_Deg * Constant::D2R);
	}

	Vector4& RotateX_Radian(float _Rad)
	{
		// ���⼭ ȸ����� ���� �׳� MUL�ع�����.

		Vector4 TempAngle = *this;

		// ȸ���� ������ ���ͷ� ����ȴ�.
		y = (TempAngle.y * cosf(_Rad)) - (TempAngle.z * sinf(_Rad));
		z = (TempAngle.y * sinf(_Rad)) + (TempAngle.z * cosf(_Rad));
		return *this;
	}

	Vector4& RotateY_Degree(float _Deg)
	{
		return RotateY_Radian(_Deg * Constant::D2R);
	}

	Vector4& RotateY_Radian(float _Rad)
	{
		Vector4 TempAngle = *this;

		// ȸ���� ������ ���ͷ� ����ȴ�.
		x = (TempAngle.x * cosf(_Rad)) - (TempAngle.z * sinf(_Rad));
		z = (TempAngle.x * sinf(_Rad)) + (TempAngle.z * cosf(_Rad));
		return *this;
	}

	Vector4& RotateZ_Degree(float _Deg)
	{
		return RotateZ_Radian(_Deg * Constant::D2R);
	}

	Vector4& RotateZ_Radian(float _Rad)
	{
		Vector4 TempAngle = *this;

		// ȸ���� ������ ���ͷ� ����ȴ�.
		x = (TempAngle.x * cosf(_Rad)) - (TempAngle.y * sinf(_Rad));
		y = (TempAngle.x * sinf(_Rad)) + (TempAngle.y * cosf(_Rad));
		return *this;
	}

	Vector4& RotationDegree(Vector4& _Deg) 
	{
		return RotationRadian(_Deg * Constant::D2R);
	}

	Vector4& RotationRadian(const Vector4& _Rad)
	{
		RotateX_Radian(_Rad.x);
		RotateY_Radian(_Rad.y);
		RotateZ_Radian(_Rad.z);
		return *this;
	}

	// UP��������
	static Vector4 CalDToDir2D(float _Deg)
	{
		return CalRToDir2D(_Deg * Constant::D2R);
	}

	static Vector4 CalRToDir2D(float _Rad)
	{
		Vector4 Return;
		Return.x = cosf(_Rad);
		Return.y = sinf(_Rad);
		return Return;
	}

	Vector4& DToDir2D(float _Deg)
	{
		return RToDir2D(_Deg * Constant::D2R);
	}

	Vector4& RToDir2D(float _Rad)
	{
		x = cosf(_Rad);
		y = sinf(_Rad);
		return *this;
	}

public:
	Vector4() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {	}
	Vector4(float _Value) : x(_Value), y(_Value), z(_Value), w(1.0f) {	}
	Vector4(float _x, float _y) : x(_x), y(_y), z(0.0f), w(1.0f) {	}
	Vector4(float _x, float _y, float _z) : x(_x), y(_y), z(_z), w(1.0f)	{	}
	Vector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {	}

	Vector4(const DirectX::XMVECTOR& _XMVEC) 
	{	
#ifdef X64
		xmVector = _XMVEC;
#else
		DirectX::XMStoreFloat4(&XMF4, _XMVEC);
#endif
	}

public:
	POINT ConvertPOINT() 
	{
		POINT ReturnPoint;
		ReturnPoint.x = (int)x;
		ReturnPoint.y = (int)y;

		return ReturnPoint;
	}
};

// 1x3�� ���⿡ ���Ҽ� �־� ����?
// 4X4�� ����ȭ�� �ڵ常 ���⿡ ĥ���̴�. 
class Matrix 
{
public:
	union
	{
		float Arr2D[4][4];
		struct
		{
			float _00;
			float _01;
			float _02;
			float _03;
			float _10;
			float _11;
			float _12;
			float _13;
			float _20;
			float _21;
			float _22;
			float _23;
			float _30;
			float _31;
			float _32;
			float _33;
		};
		DirectX::XMFLOAT4X4 DXF4;
		// 16����Ʈ 
		// �̳༮�� 64��Ʈ�϶��� �־�� �Ѵ�.
#ifdef X64
		DirectX::XMMATRIX DXMAT;
#endif

		Vector4 ArrVec[4];
		float Arr1D[16];
		Vector2 Vec2;
		Vector3 Vec3;
	};

public:
	operator DirectX::XMMATRIX() const
	{
#ifdef X64
		return DXMAT;
#else
		// 16����Ʈ ���ķ� �����Ѱ� ����.
		return DirectX::XMLoadFloat4x4(&DXF4);
#endif
	}

public:
	Matrix& operator=(float _Value) 
	{
		// 32��Ʈ������ 128¥���� �������� �ʴ´�.
		// int128 Test;

		for (size_t i = 0; i < 16; i++)
		{
			Arr1D[i] = _Value;
		}
		return *this;
	}

	Matrix operator*(const Matrix& _Other)
	{
		Matrix NewMat;
#ifdef X64
		NewMat.DXMAT = DirectX::XMMatrixMultiply(DXMAT, _Other.DXMAT);
#else
		DirectX::XMStoreFloat4x4(&NewMat.DXF4, DirectX::XMMatrixMultiply(*this, _Other));
#endif

		return NewMat;
	}



	Vector4 operator*(const Vector4& _Other) 
	{
		Vector4 NewVec;
		for (size_t y = 0; y < 1; y++)
		{
			for (size_t x = 0; x < 4; x++)
			{
				float Sum = 0.0f;
				for (size_t i = 0; i < 4; i++)
				{
					Sum += _Other.Arr[i] * Arr2D[i][x];
				}

				NewVec.Arr[x] = Sum;
			}
		}

		return NewVec;
	}


	Matrix& operator = (const DirectX::XMMATRIX& _Other)
	{
#ifdef X64
		DXMAT = _Other;
#else
		DirectX::XMStoreFloat4x4(&DXF4, _Other);
#endif
		return *this;
	}


	Matrix& operator*=(const Matrix& _Other)
	{
#ifdef X64
		DXMAT = DirectX::XMMatrixMultiply(DXMAT, _Other.DXMAT);
#else
		DirectX::XMStoreFloat4x4(&DXF4, DirectX::XMMatrixMultiply(*this, _Other));
#endif
		return *this;
	}

public:
	Vector4 Foword() 
	{
		return ArrVec[2];
	}

	Vector4 Up() 
	{
		return ArrVec[1];
	}

	Vector4 Right() 
	{
		return ArrVec[0];
	}


public:

	void Identity()
	{
#ifdef X64
		DXMAT = DirectX::XMMatrixIdentity();
#else
		DirectX::XMStoreFloat4x4(&DXF4, DirectX::XMMatrixIdentity());
#endif
	}

	void Inverse()
	{
#ifdef X64
		DXMAT = DirectX::XMMatrixInverse(nullptr, DXMAT);
#else
		DirectX::XMStoreFloat4x4(&DXF4, DirectX::XMMatrixInverse(nullptr, DXMAT));
#endif
		//Arr2D[0][0] = cosf(_Rad);
		//Arr2D[0][2] = -sinf(_Rad);
		//Arr2D[2][0] = sinf(_Rad);
		//Arr2D[2][2] = cosf(_Rad);
	}

	void Translation(const Vector4& _Other)
	{
		Identity();
#ifdef X64
		DXMAT = DirectX::XMMatrixTranslation(_Other.x, _Other.y, _Other.z);
#else
		DirectX::XMStoreFloat4x4(&DXF4, DirectX::XMMatrixTranslation(_Other.x, _Other.y, _Other.z));
#endif

		//Arr2D[3][0] = _Other.x;
		//Arr2D[3][1] = _Other.y;
		//Arr2D[3][2] = _Other.z;
	}

	void Scaling(const Vector4& _Other)
	{
		Identity();
#ifdef X64
		DXMAT = DirectX::XMMatrixScaling(_Other.x, _Other.y, _Other.z);
#else
		DirectX::XMStoreFloat4x4(&DXF4, DirectX::XMMatrixScaling(_Other.x, _Other.y, _Other.z));
#endif
	}

	void RotateX_Degree(const float& _Deg)
	{
		return RotateX_Radian(_Deg * Constant::D2R);
	}

	void RotateX_Radian(const float& _Rad) 
	{
		Identity();

#ifdef X64
		DXMAT = DirectX::XMMatrixRotationX(_Rad);
#else
		DirectX::XMStoreFloat4x4(&DXF4, DirectX::XMMatrixRotationX(_Rad));
#endif
		//Arr2D[1][1] = cosf(_Rad);
		//Arr2D[1][2] = sinf(_Rad);
		//Arr2D[2][1] = -sinf(_Rad);
		//Arr2D[2][2] = cosf(_Rad);
	}

	void RotateY_Degree(const float& _Deg)
	{
		return RotateY_Radian(_Deg * Constant::D2R);
	}

	void RotateY_Radian(const float& _Rad)
	{
		Identity();

#ifdef X64
		DXMAT = DirectX::XMMatrixRotationY(_Rad);
#else
		DirectX::XMStoreFloat4x4(&DXF4, DirectX::XMMatrixRotationY(_Rad));
#endif
		//Arr2D[0][0] = cosf(_Rad);
		//Arr2D[0][2] = -sinf(_Rad);
		//Arr2D[2][0] = sinf(_Rad);
		//Arr2D[2][2] = cosf(_Rad);
	}

	void RotateZ_Degree(const float& _Deg)
	{
		return RotateZ_Radian(_Deg * Constant::D2R);
	}

	void RotateZ_Radian(const float& _Rad)
	{
		Identity();
#ifdef X64
		DXMAT = DirectX::XMMatrixRotationZ(_Rad);
#else
		DirectX::XMStoreFloat4x4(&DXF4, DirectX::XMMatrixRotationZ(_Rad));
#endif
		//Arr2D[0][0] = cosf(_Rad);
		//Arr2D[0][1] = sinf(_Rad);
		//Arr2D[1][0] = -sinf(_Rad);
		//Arr2D[1][1] = cosf(_Rad);
	}

	void RotationDegree(const Vector4& _Deg)
	{
		RotationRadian(_Deg * Constant::D2R);
	}

	void RotationRadian(const Vector4& _Rad)
	{
		Identity();

#ifdef X64
		DXMAT = DirectX::XMMatrixRotationRollPitchYaw(_Rad.x, _Rad.y, _Rad.z);
#else
		DirectX::XMStoreFloat4x4(&DXF4, DirectX::XMMatrixRotationRollPitchYaw(_Rad.x, _Rad.y, _Rad.z));
#endif

		//HMAT X;
		//HMAT Y;
		//HMAT Z;

		//X.DRotX(_Rad.x);
		//Y.RotateY_Degree(_Rad.y);
		//Z.RotateZ_Degree(_Rad.z);

		//*this = X * Y * Z;
	}

	// XYZ -> ��׸� ���Ϸ� ���־��ش�.
	// -> ���� ���Ϸ� ������
	// -> ���ʹϾ����� ����.
	// -> �� ���ʹϾ����� ȸ��.
	void QuaternionRotate_Degree(const Vector4& _Deg)
	{
		Vector4 Rot = (_Deg * Constant::D2R);
		
		
		RtoQRot(Rot);
	}

	void QuaternionRotate_Radian(const Vector4& _Rad)
	{
#ifdef X64
		DXMAT = DirectX::XMMatrixRotationQuaternion(_Rad);
#else
		DirectX::XMStoreFloat4x4(&DXF4, DirectX::XMMatrixRotationQuaternion(_Rad));
#endif
	}

	void RtoQRot(const Vector4& _Rad)
	{
#ifdef X64
		DXMAT = DirectX::XMMatrixRotationQuaternion(DirectX::XMQuaternionRotationRollPitchYaw(_Rad.x, _Rad.y, _Rad.z));
#else
		DirectX::XMStoreFloat4x4(&DXF4, DirectX::XMMatrixRotationQuaternion(DirectX::XMQuaternionRotationRollPitchYaw(_Rad.x, _Rad.y, _Rad.z)));
#endif
	}

	void TransPose() 
	{
#ifdef X64
		DXMAT = DirectX::XMMatrixTranspose(*this);
#else
		DirectX::XMStoreFloat4x4(&DXF4, DirectX::XMMatrixTranspose(*this));
#endif

		//float Temp;
		//for (size_t y = 0; y < 4; y++)
		//{
		//	for (size_t x = y; x < 4; x++)
		//	{
		//		//if (y == x)
		//		//{
		//		//	continue;
		//		//}

		//		Temp = Arr2D[x][y];
		//		Arr2D[x][y] = Arr2D[y][x];
		//		Arr2D[y][x] = Temp;
		//	}
		//}
	}

	void SetViewMatrix(Vector4 _EyePos, Vector4 _EyeDir, Vector4 _EyeUp)
	{
		Identity();

#ifdef X64
		DXMAT = DirectX::XMMatrixLookToLH(_EyePos, _EyeDir, _EyeUp);
#else
		DirectX::XMStoreFloat4x4(&DXF4, DirectX::XMMatrixLookToLH(_EyePos, _EyeDir, _EyeUp));
#endif


		// ���� �ܾƿ� ����� ������.
		// ������ �ȵǸ� ������.

		// View�����
		// ������ ������ΰ�?
		// ī�޶� ����ü�� ����� ������̴�.

		// _Dir�� ���ͷμ��� ���� 1�ϰ͸� ����Ǹ� �ȴ�.
		// _Up�� ���ͷμ��� ���̰� 1�ϰ͸� ����Ǹ� �ȴ�.

		// _Posī�޶��� ��ġ
		// _Dir�ٶ󺸴� ����
		// Y�� ��������
		// _Up�ٶ󺸴� ���⿡�� x������ 90�� �� ����
		//_EyeDir.Normal3D();
		//_EyeUp.Normal3D();
		//ArrVec[2] = _EyeDir;
		//ArrVec[1] = _EyeUp;
		//// ���� �� �Ӽ��� 2���� ���͸� �־��ָ� 
		//// �κ��� ��ο� ������ ���͸� �������ִ� �����̴�.
		//ArrVec[0] = HVEC4::Cross3D(ArrVec[1], ArrVec[2]);

		//TransPose();


		//// ���带 �������� �̵��ϴ� ������Ʈ����
		//// ������� ������ �������� �̵��� �ϱ� ������.
		//// ArrVec[3] = -_EyePos;
		//ArrVec[3] = 
		//{
		//	// ArrVec[0~2]�� ũ�Ⱑ 1�̹Ƿ� ���翵�� �������̴�.
		//	// ������ ���翵�� ���ظ��ϸ� ����ĵ� �����Ҽ� ����.
		//	-HVEC4::Dot3D(ArrVec[0], _EyePos), // 
		//	-HVEC4::Dot3D(ArrVec[1], _EyePos), // 0.0F;
		//	-HVEC4::Dot3D(ArrVec[2], _EyePos), // 
		//	1.0f,
		//};
		// ��ġ��� 
		// 12 -> 21
	}


	// �����������
	// ���ٰ� ���
	// Z�࿡ ���ؼ� X�� Y �� �ٲ�� ����� �̳༮
	// float _Width ������ �ʺ� �ƴѴ�. (������ �ʺ� �־��� ������)
	// �ƴϾ �ȴ�.
	// _Near �����
	// _Far �����
	void SetOrthgonalMatrix(float _Width, float _Height, float _Near, float _Far)
	{
		Identity();
		// ���� ����Ϸ��� �Լ� ���ο��� �ϰ� �ҰŴ�.

		// �̷��Լ����� ������.
		// �� �Լ����� ���ο��� �� Ư���� ������ �Ѵ�.
		// SSE �����̶�� �ϴµ�.
		// FLOAT4���� 4X4 
		// �� ������ ����Ϸ��� 16����Ʈ�� ������ �޸𸮰� ���ĵǾ� �־�� �Ѵ�.

#ifdef X64
		DXMAT = DirectX::XMMatrixOrthographicLH(_Width, _Height, _Near, _Far);
#else
		DirectX::XMStoreFloat4x4(&DXF4, DirectX::XMMatrixOrthographicLH(_Width, _Height, _Near, _Far));
#endif
	}

	// Normal
	Vector4 MulZero(Vector4 _Value)
	{
		_Value.w = 0.0f;
		_Value = DirectX::XMVector4Transform(_Value, DXMAT);
		return _Value;
	}

	// coord
	Vector4 MulOne(Vector4 _Value)
	{
		_Value.w = 1.0f;
		_Value = DirectX::XMVector3TransformCoord(_Value, DXMAT);
		return _Value;
	}

	// coord
	Vector4 Mul(Vector4 _Value)
	{
		_Value = DirectX::XMVector4Transform(_Value, DXMAT);
		return _Value;
	}

	void SetPerspectiveMatrix(float _Fov, float _Width, float _Height, float _Near, float _Far)
	{
		Identity();
		// ���� �þ߰�
		float A = _Fov * Constant::D2R;
		float R = _Width / _Height;
		// ���� �þ߰�
		// ��� �ֵ��� -1 ~ 1 �������� ����.
		// z�� 0~ 1�������� ����.
		// ���⿡�� ��? Z�� ������?
		// �� ������ �֤���.
		// Z�� 2�� ������ ��ġ�� �ȴ�.
		// ������Ʈ ���ڰ����� 
		// / Z�� �ϸ� �����µ� / Z

		// 1. �� ������ Z�� �ʿ��ѵ�. ���⼭?????
		// ������ �׷��Ƿ�
		// 2. �������� Z�� W���ٰ� �����ִ� ����. Arr2D[2][3] = 1.0f;
		// 3. �� ���⿡���� ���� ������ ���� ���°ų�???
		// �����̱� ������ / Z�� �ؾ� ���� ��ġ�� �����µ�.
		// �� Z�� ���� ����ü�� �Ǳ� ������
		// Z�� �� ���� �����
		// Z�� �� ������ �ٷ�
		// �����ְ� �ȴ�.

		// X
		Arr2D[0][0] = 1 / (R * tanf(A / 2)); // * X / Z : 200.0F
		// Y
		Arr2D[1][1] = 1 / (tanf(A / 2)); // * Y / Z : 200.0F

		// 200.0F�� �־�����
		// ���� Z�� �־�� �Ѵ�.
		// -0.5~0.5f 
		Arr2D[2][2] = _Far/ (_Far - _Near); // / Z
		// + 0~0.5f
		Arr2D[3][2] = -(_Near * _Far) / (_Far - _Near);

		// z�� ����� �������� �����Ų��.
		Arr2D[2][3] = 1.0f;

		// �̰� ����
		// �̰� ���ϸ� w�� 1���� ��������.
		// w�� z�� ��Ƴ��µ� 0.5 * 50 25�� ���;� �ϴµ� 26�� ����.
		Arr2D[3][3] = 0.0f;
	}

	// -1 ~ 1 �� �ɱ۾� ���� �������� 2D ȭ�鿡 �°� �����ִ� �뵵�̴�.
	// ���� 2D ȭ�� 
	void SetViewPortMatrix(float _StartX, float _StartY, float _Width, float _Height, float _MinZ, float _MaxZ)
	{
		Identity();
		Arr2D[0][0] = _Width / 2;
		Arr2D[1][1] = -(_Height / 2); // �̰� Y���� ������Ų��.
		Arr2D[2][2] = _MaxZ - _MinZ;

		// ��ġ���� �����ִ�.
		Arr2D[3][0] = _StartX + Arr2D[0][0];
		Arr2D[3][1] = _StartY + (_Height / 2);
		Arr2D[3][2] = _MinZ;
	}

	void GetWorldMatrix(Vector4 _Scale, Vector4 _Rot, Vector4 _Pos)
	{
		Matrix Scale;
		Matrix Rot;
		Matrix Pos;

		Scale.Scaling(_Scale);
		Rot.RotationDegree(_Rot);
		Pos.Translation(_Pos);

		*this = Scale * Rot * Pos;
	}

public:
	Matrix() 
	{
		Identity();
	}

	Matrix(const DirectX::XMMATRIX& _Other) 
	{ 
#ifdef X64
		DXMAT = _Other;
#else
		DirectX::XMStoreFloat4x4(&DXF4, _Other);
#endif
	}

};
//
//class HMATH
//{
//private:
//	static bool RectToRect();
//
//public:
//	HMATH();
//	~HMATH();
//};
//
