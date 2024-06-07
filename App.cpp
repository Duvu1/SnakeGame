#include "Windows.h"
#include <iostream>
#include <random>
#include <vector>

#include "struct.h"

#include "App.h"

App::App()
{
	// stage 가장자리 벽 만들기
	for (int i = 0; i <= m_stageWidth + 1; i++)
	{
		m_stage[0][i] = -1;
		m_stage[m_stageHeight + 1][i] = -1;
	}

	for (int i = 1; i <= m_stageHeight; i++)
	{
		m_stage[i][0] = -1;
		m_stage[i][m_stageWidth + 1] = -1;
	}
}

App::~App()
{
}

void App::EnterGame()
{
	system("cls");
	cout << "                      " << endl
		<< "                      " << endl
		<< "       33333333       " << endl
		<< "    33333333333333    " << endl
		<< "   33333      33333   " << endl
		<< "   3333       33333   " << endl
		<< "             33333    " << endl
		<< "           33333      " << endl
		<< "             33333    " << endl
		<< "   33333      33333   " << endl
		<< "   33333      33333   " << endl
		<< "    33333333333333    " << endl
		<< "      3333333333      " << endl
		<< "                      " << endl
		<< "                      " << endl;
	Sleep(1000);

	system("cls");
	cout << "                      " << endl
		<< "                      " << endl
		<< "       22222222       " << endl
		<< "    22222222222222    " << endl
		<< "   22222      22222   " << endl
		<< "   2222       22222   " << endl
		<< "             22222    " << endl
		<< "           22222      " << endl
		<< "         22222        " << endl
		<< "       22222          " << endl
		<< "     222222           " << endl
		<< "   22222222222222222  " << endl
		<< "   22222222222222222  " << endl
		<< "                      " << endl
		<< "                      " << endl;
	Sleep(1000);

	system("cls");
	cout << "                      " << endl
		<< "                      " << endl
		<< "         11111        " << endl
		<< "      11111111        " << endl
		<< "      11111111        " << endl
		<< "         11111        " << endl
		<< "         11111        " << endl
		<< "         11111        " << endl
		<< "         11111        " << endl
		<< "         11111        " << endl
		<< "         11111        " << endl
		<< "     1111111111111    " << endl
		<< "     1111111111111    " << endl
		<< "                      " << endl
		<< "                      " << endl;
	Sleep(1000);
}

void App::SetStageArray(Vec2 pos)
{
	// stage 배열에 player 세팅
	// 배열에 대입되는 value는 player의 length만큼의 "시간"이다.
	// 한 count 진행될 때마다 배열의 값이 하나씩 줄어들어
	// 이동하는 것처럼 보이게 구현한 것이므로
	// CountTime()에서 처리해도 무방할 것이다.
	for (int i = 1; i <= m_stageHeight; i++)
		for (int j = 1; j <= m_stageWidth; j++)
		{
			// star 획득 시 값이 줄어들지 않으므로
			// 길이가 하나 늘어나는 것처럼 보이도록 구현
			if (m_stage[i][j] > 0 && m_starFlag == false)
					m_stage[i][j]--;					
		}
	
	// 배열에 대입되는 value는 player의 length만큼의 "시간"이다.
	m_stage[pos.y][pos.x] = player.GetLength();
	m_starFlag = false;

	// stage 배열에 star 세팅
	if (m_starTimer == 0)
	{
		m_starTimer = 10;

		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> dis(1, 20);

		while (true)
		{
			// 무작위 위치에 star 생성
			int x = dis(gen);
			int y = dis(gen);

			// void space여야 star 세팅
			if (m_stage[y][x] == 0)
			{
				m_stage[y][x] = -2;
				break;
			}
		}
	}
}

void App::DetectCollision(Vec2 pos)
{
	int collideTo = m_stage[pos.y][pos.x];

	if (collideTo == -2)
	{
		// star와 충돌했을 때
		int length = player.GetLength();
		player.SetLength(length + 1);
		m_score++;
		m_starFlag = true;
	}
	else if (collideTo)
	{ 
		// void space가 아닌 그 외의 것들과 충돌
		// wall, player 자신
		m_gameState = -1;
	}
}

void App::CountTime()
{
	m_starTimer--;
	m_leftTimeCount--;

	if (m_leftTimeCount <= 0)
		m_gameState = -1;
}

bool App::DetectGameState()
{
	if (m_score >= m_goal)
		m_gameState = 1;

	switch (m_gameState)
	{
	case 1:
		cout << "!!!!!!!!!GAME CLEAR!!!!!!!!!" << endl;
		return false;
	case -1:
		cout << "!!!!!!!!!GAME OVER!!!!!!!!!" << endl;
		return false;
	default:
		return true;
	}

	return true;
}

void App::DrawAll()
{
	// stage 배열의 값에 따라 타일 출력
	for (int i = 0; i <= m_stageHeight + 1; i++)
	{
		for (int j = 0; j <= m_stageWidth + 1; j++)
		{
			char value = m_stage[i][j];

			if (value > 0)
				cout << '@';	// player
			else if (value == 0)
				cout << ' ';	// void space
			else if (value == -1)
				cout << '#';	// wall
			else if (value == -2)
				cout << '*';	// star

		}

		cout << endl;
	}

	// 게임 상황판 출력
	cout << "Score:\t\t" << m_score << " / " << m_goal << endl;
	cout << "Count Left:\t" << m_leftTimeCount << endl;
}

bool App::Run()
{
	EnterGame();

	while (true)
	{
		system("cls");

		Vec2 position = player.Move();
		
		// player의 충돌 감지
		DetectCollision(position);

		// stage 배열 value 설정
		SetStageArray(position);

		// 남은 시간 count
		CountTime();

		// stage를 화면에 출력
		DrawAll();

		// 게임 진행 여부 판단
		if (!DetectGameState())
			break;

		Sleep(250);
	}

	return true;
}

