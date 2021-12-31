#pragma once
#include <Logic.h>
#include <map>
#include <list>

//

#include <FbxAnimation.h>


class StatusLogic;
class PieceLogic : public Logic
{
protected:
	StatusLogic* statusLogic;
	Scene* myScene;

private:
	class PieceNode
	{
	public:
		BoardIndex pos;
		int startCost;  //������������� ������ġ������ ��� ���μ��δ� 10 , �밢�� 14
		int sumCost;	//start + dest ����� �� ���� ��ã���ҋ� �̿��Ѵ�
		int destCost;	//���������κ��� ������ġ������ ��� (���� �����Ѵ�.)
		bool iSWall;

	public:
		PieceNode() : startCost(0), sumCost(0), destCost(0), iSWall(false)
		{
			
		}
	};

private:
	static std::vector<std::vector<bool>> m_MapStaticInfo;
	static std::vector<std::vector<bool>> m_MapStaticMonster;

	

public:
	static void InitMapStaticInfo()
	{
		m_MapStaticInfo.resize(8);	//�˳��ϰ� 50���� �����д�
		for (int z = 0; z < 8; ++z)
		{
			m_MapStaticInfo[z].resize(8);
		}

		for (int z = 0; z < 8; ++z)
		{
			for (int x = 0; x < 8; ++x)
			{
				m_MapStaticInfo[z][x] = false;
			}
		}

		m_MapStaticMonster.resize(8);	//�˳��ϰ� 50���� �����д�
		for (int z = 0; z < 8; ++z)
		{
			m_MapStaticMonster[z].resize(8);
		}

		for (int z = 0; z < 8; ++z)
		{
			for (int x = 0; x < 8; ++x)
			{
				m_MapStaticMonster[z][x] = false;
			}
		}
	}

	static void ResetMapStaticInfo();
		
	static void PushPieceInfo(Vector4 _Pos);
	static void PushMonsterInfo(Vector4 _Pos);

	void ResetMyPath();

protected:
	std::vector<std::vector<PieceNode>> m_MapInfo;
	std::multimap<int /*sumCost*/, PieceNode> m_OpenList;	
	std::list<PieceNode> m_CloseList;

	Actor* myActor;

public:
	std::list<PieceNode> FindPath(const BoardIndex _DestPos);
	void OverlapPathCheck();
	void CurPosIdxCheck();

	Actor* FindAttackTarget();
	Actor* FindEnemyTarget();


public:

	enum PIECESTATE
	{
		BORN,
		IDLE,
		FINDATTACKTARGET,
		ATTACK,
		FINDMOVETARGET,
		RUN,
		JUMP,
		SKILL,
		DIE,		//�ױ���
		DEAD,		//������ ������
		VICTORY,
		STAY,
	};

protected:
	//Actor* pActor;
	FbxAnimation* pFbxAnimation;
	std::list<PieceNode> path;

	std::wstring m_CharName;
	PIECESTATE m_State;
	BoardIndex m_Index;
	BoardIndex m_StartIndex;
	//PIECETYPE m_Type;

private:
	bool	isEnemyFind;
	bool	isAttackFind;
	int		m_Range;

	bool isStay;
	bool isDie;


	bool realDead;

protected:
	bool isPassive;

protected:
	bool isMonster;

public:
	void SetRange(int _Range)
	{
		m_Range = _Range;
	}

public:
	BoardIndex	CalculateIndex(Vector4 _Pos);
	void		SetName(const wchar_t* _CharName)
	{
		m_CharName = _CharName;
	}

public:
	void Init() override;
	void Update() override;

public:
	void Born();
	void Idle();
	void FindAttTarget();
	void Attack();

	

	void FindTransTarget();
	void Run();
	void Jump();
	void Die();
	void Dead();
	virtual void Victory();
	void Stay();
	
	virtual void MakeProjecTile() {} ;
	virtual void Skill() {};
	virtual void Passive() {};
	
	void SkillCheck();


private:
	bool makeProjectTile;
protected:
	Actor*		pAttTarget;

private:
	bool		isRun;
	bool		isJump;
	bool		isRotate;

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


public:
	void	ParabolaCalculate(float _MaxTime, float _MaxHeight);
	Vector4 JumpCalculate();
	Vector4 Rotate(BoardIndex	_DestIdx);


//private:
//	int hp;
//	int mp;
//	int att;
//
//	//��ų ��Ÿ�� ����Ÿ��, �ִ�Ÿ��
//	float curTime;
//	float maxTime;

public:
	PieceLogic();
	~PieceLogic();
};

