#include "menu_helper.h"

int menu_helper(vector <string> menu)
{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		int choice = 1;
		while (true)
		{
				system("cls");
				cout << menu[0] << endl << endl;
				for (int i = 1; i < menu.size(); i++)
				{
						if (i == choice)
						{
								SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
								cout << menu[i] << endl;
								SetConsoleTextAttribute(hConsole, 15);
								continue;
						}
						cout << menu[i] << endl;
				}

				char c = _getch();
				if (c == 72)
				{
						if (choice == 1)
								continue;
						choice--;
						continue;
				}
				if (c == 80)
				{
						if (choice == menu.size() - 1)
								continue;
						choice++;
						continue;
				}
				if (c == 13)
				{
						return choice;
				}
		}
}