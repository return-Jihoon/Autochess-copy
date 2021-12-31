#pragma once
#include "PieceLogic.h"
class ThunderSpirit :
	public PieceLogic
{

public:
	void Update() override;

public:
	void MakeProjecTile() override;
	void Skill() override;

	bool skillOn;


public:
	ThunderSpirit();
	~ThunderSpirit();
};

