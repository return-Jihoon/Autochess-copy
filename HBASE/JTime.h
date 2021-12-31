#pragma once

#include <Windows.h>
// ���� 

// 1�ʿ� RUN�� 
// deltatime
// ��ǻ���� ������ ���� ������ 
// ���ǽð����� ������ �ð�.
//  
// A ��ǻ�� 2 (2 * deltatime(0.5)) = 1
// B ��ǻ�� 1 (1 * deltatime(1.0)) = 1

// ��ǻ�Ϳ��� CPU�� ���������� 
// �׻� ��Ȯ�� 1�ʸ��� ��Ȯ�� ���� ���� ��Ȯ�� �Ȱ��� �ݺ������� ���� �ִ´�.
// 1�ʿ� 100���� ����.
// ConstTime = 100;

// ConstTime = 1�ʿ��󸶻����ִ�();
// Start = �ð��󸶴�() 50;
// Prev = �ð��󸶴�();


// Start = �����ð��󸶴�() 50;
//  50    -  0    / 100
// (Start - Prev) / ConstTime; 0.5 
// Prev = Start;

// Start = �����ð��󸶴�() 100;
//  100    -  50    / 100
// (Start - Prev) / ConstTime; 0.5 
// Prev = Start;

// Start = �����ð��󸶴�() 150;
//  150    -  100    / 100
// (Start - Prev) / ConstTime; 0.5 
// Prev = Start;

class Time
{
public:
	class Timer 
	{
	public:
		friend Time;

	private:
		// __int64
		// 64��Ʈ ��Ʈ
		LARGE_INTEGER m_CountingTime;	// 1�ʿ� ���� ���� �ִ���?
		LARGE_INTEGER m_CurTime;		// ���� �󸶳�?
		LARGE_INTEGER m_PrevTime;		// ������ �󸶿���?
		double m_DDeltaTime;
		float m_DeltaTime;

	public:
		float Update();
		void Reset();

	private:
		Timer();
		~Timer();
	};

private:
	// �����е鿡�Դ� �������ϸ��� �����ַ��� �Ѵ�.
	// ���� ������ �ð��� ��� �뵵.
	static Timer MainTimer; 

public:
	// �ʹ� ������ �Լ��� ����ȿ� �״µ�
	// ���ο� �ξ ����� ����.
	// inline �Լ��� ���ؼ� �̷а����غ�����.
	static float DeltaTime()
	{
		return MainTimer.m_DeltaTime;
	}

	static float SDeltaTime(float _Speed)
	{
		return MainTimer.m_DeltaTime * _Speed;
	}

public:
	static void Update();
	static void Reset();


private:
	Time() {}
	~Time() {}
};

