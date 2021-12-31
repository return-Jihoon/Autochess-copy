#include "JTime.h"

///////////////////////////////////// Timer

Time::Timer::Timer() : m_DeltaTime(0.0f)
{
	Reset();
}


Time::Timer::~Timer()
{
}

// �ϴ� ��ŸŸ���� ���ϰ� �������ش�.
float Time::Timer::Update() 
{
	// �̶� ���ٸ� 
	QueryPerformanceCounter(&m_CurTime);

	//1000 == 1��
	//   0 == 0��
	// 500 == 0.5��

	m_DDeltaTime = ((double)m_CurTime.QuadPart - (double)m_PrevTime.QuadPart) / ((double)m_CountingTime.QuadPart);
	m_DeltaTime = (float)m_DDeltaTime;
	m_PrevTime = m_CurTime;

	return m_DeltaTime;
}

// üũ������ �� �ɹ��Լ����� �ʱ⿡ �־���� ���·� ������. 
void Time::Timer::Reset() 
{
	// ����� �ٲ��� ���� 
	// 100
	QueryPerformanceFrequency(&m_CountingTime);
	// ���� ������� �󸶸� ���ڸ� ī���� �ߴ�.
	// 38
	QueryPerformanceCounter(&m_CurTime);
	QueryPerformanceCounter(&m_PrevTime);

	// m_CountingTime; // 1�ʿ� ���� ���� �ִ���?
	// m_CurTime; // ���� �󸶳�?
	// m_PrevTime; // ������ �󸶿���?

}

///////////////////////////////////// Time
Time::Timer Time::MainTimer;

void Time::Update() 
{
	MainTimer.Update();
}
void Time::Reset()
{
	MainTimer.Reset();
}