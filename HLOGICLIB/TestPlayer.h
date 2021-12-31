#pragma once
#include <Logic.h>
#include <Terrain.h>

class TestPlayer : public Logic
{
public:
	HPTR<Terrain> m_Map;

public:
	void Init() override;
	void Update() override;
public:
	TestPlayer();
	~TestPlayer();
};

