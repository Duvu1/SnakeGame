#pragma once

#include "Snake.h"

using namespace std;

class App
{
public:
	App();
	~App();

public:
	void EnterGame();
	void SetStageArray(Vec2 pos);
	void DetectCollision(Vec2 pos);
	void CountTime();
	bool DetectGameState();

	bool Run();
	void DrawAll();

public:
	int		m_stageWidth = 20;
	int		m_stageHeight = 20;

private:
	// game over: -1, game clear 1, continue 0
	int		m_gameState = 0;

	// star: -2, wall: -1, void space: 0, player > 0
	char	m_stage[22][22] = { 0 };

	int		m_score = 0;
	int		m_goal = 5;
	int		m_leftTimeCount = 100;

	Snake	player;

	int		m_starTimer = 0;	// star Àç»ý¼º ºóµµ
	bool	m_starFlag = false;	// star ¸Ô¾ú´Â°¡?
};

