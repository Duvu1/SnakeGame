#include "conio.h"

#include "Snake.h"

using namespace std;

Snake::Snake()
{
}

Snake::~Snake()
{
}

Vec2 Snake::Move()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w': m_dirIndex = 0; break;
		case 's': m_dirIndex = 1; break;
		case 'a': m_dirIndex = 2; break;
		case 'd': m_dirIndex = 3; break;
		}
	}

	posX += m_dirX[m_dirIndex];
	posY += m_dirY[m_dirIndex];

	return { posX, posY };
}

int Snake::GetLength()
{
	return m_length;
}

void Snake::SetLength(int length)
{
	m_length = length;
}
