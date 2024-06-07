#pragma once

#include "struct.h"

class Snake
{
public:
	Snake();
	~Snake();

public:
	int GetLength();
	void SetLength(int length);

	Vec2 Move();

private:
	int m_length = 3;
	int posX = 10;
	int posY = 10;

	int m_dirIndex = 0;
	int m_dirX[4] = { 0, 0, -1, 1 };
	int m_dirY[4] = { -1, 1, 0, 0 };
};

