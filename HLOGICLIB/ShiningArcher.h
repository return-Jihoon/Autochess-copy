#pragma once
#include "PieceLogic.h"


class ShiningArcher :
	public PieceLogic
{
private:
	HPTR<Actor> skillActor;
	HPTR<SpriteRender> skillSprite;

public:
	void Update() override;

public:
	void MakeProjecTile() override;
	void Skill() override;

public:
	ShiningArcher();
	~ShiningArcher();
};

