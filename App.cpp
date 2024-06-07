#include "Windows.h"
#include <iostream>
#include <random>
#include <vector>

#include "struct.h"

#include "App.h"

App::App()
{
	// stage �����ڸ� �� �����
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
	// stage �迭�� player ����
	// �迭�� ���ԵǴ� value�� player�� length��ŭ�� "�ð�"�̴�.
	// �� count ����� ������ �迭�� ���� �ϳ��� �پ���
	// �̵��ϴ� ��ó�� ���̰� ������ ���̹Ƿ�
	// CountTime()���� ó���ص� ������ ���̴�.
	for (int i = 1; i <= m_stageHeight; i++)
		for (int j = 1; j <= m_stageWidth; j++)
		{
			// star ȹ�� �� ���� �پ���� �����Ƿ�
			// ���̰� �ϳ� �þ�� ��ó�� ���̵��� ����
			if (m_stage[i][j] > 0 && m_starFlag == false)
					m_stage[i][j]--;					
		}
	
	// �迭�� ���ԵǴ� value�� player�� length��ŭ�� "�ð�"�̴�.
	m_stage[pos.y][pos.x] = player.GetLength();
	m_starFlag = false;

	// stage �迭�� star ����
	if (m_starTimer == 0)
	{
		m_starTimer = 10;

		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> dis(1, 20);

		while (true)
		{
			// ������ ��ġ�� star ����
			int x = dis(gen);
			int y = dis(gen);

			// void space���� star ����
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
		// star�� �浹���� ��
		int length = player.GetLength();
		player.SetLength(length + 1);
		m_score++;
		m_starFlag = true;
	}
	else if (collideTo)
	{ 
		// void space�� �ƴ� �� ���� �͵�� �浹
		// wall, player �ڽ�
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
	// stage �迭�� ���� ���� Ÿ�� ���
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

	// ���� ��Ȳ�� ���
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
		
		// player�� �浹 ����
		DetectCollision(position);

		// stage �迭 value ����
		SetStageArray(position);

		// ���� �ð� count
		CountTime();

		// stage�� ȭ�鿡 ���
		DrawAll();

		// ���� ���� ���� �Ǵ�
		if (!DetectGameState())
			break;

		Sleep(250);
	}

	return true;
}

