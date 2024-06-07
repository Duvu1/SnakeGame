#include <iostream>

#include "App.h"

int main()
{
	char command;

	cout << "Play Snake Game? y / n : ";

	while (true)
	{
		cin >> command;

		if (command != 'y')
		{
			cout << "OK, Bye!" << endl;
			break;
		}

		App game;
		game.Run();

		cout << "Try again? y / n : ";
	}

	return 0;
}