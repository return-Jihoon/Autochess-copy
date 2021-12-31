#pragma once
#include <Logic.h>

class FireMagicionSkill : public Logic
{
public:
	void SetTarget(Actor* _EnemyActor, Actor* _MyActor);

private:
	bool rotCheck;

protected:
	bool		isRun;
	bool		isJump;
	bool		isRotate;

	BoardIndex  m_Index;
	Actor*		pAttTarget;
	Vector4		attDestPos;
	BoardIndex	attDestIdx;
	int attCnt;

	Actor*		pMoveTarget;
	Vector4		moveDestPos;
	BoardIndex	moveDestIdx;



	//
#pragma region MOVE
	Vector4 j_destPos;
	Vector4 j_StartPos;

	float vX; // x������Ǽӵ�
	float vY; // y������Ǽӵ�
	float vZ; // z������Ǽӵ�
	float g; // y������� �߷°��ӵ�
	float endTime;// ������ ���޽ð�
	float maxHeight; //�ְ��� ����
	float height; // �ְ��� - ������(����)
	float endHeight;//������ ����
	float time; //����ð�
	float maxTime; //�ְ��� ���޽ð�
#pragma endregion

	float deadTime;

	float degree;

	static float rotDegree;

public:
	void SetDegree(float _Degree)
	{
		degree = _Degree;
	}

public:
	Actor* FindNextTarget();


public:

	void	ParabolaCalculate(float _MaxTime, float _MaxHeight);


	Vector4 JumpCalculate();
	Vector4 Rotate(BoardIndex	_DestIdx, float _Degree);

	void Jump();

public:
	void Init() override;
	void Update() override;

public:
	FireMagicionSkill();
	~FireMagicionSkill();
};

