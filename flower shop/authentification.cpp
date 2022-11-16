#include "authentification.h"

int input()
{
		int n;
		while (!(cin >> n) || (cin.peek() != '\n'))
		{
				cin.clear();
				while (cin.get() != '\n');
				cout << "������. ����������, ����������� �������� ����." << endl;
		}

		cin.ignore();
		return n;
}

void authentification(map <string, Account>& accounts)
{
		string login, password;

		cout << "������� ����� - ";
		getline(cin, login);
		cout << "������� ������ - ";
		char c;
		while (true)
		{
				c = _getch();
				if (c == '\r')
						break;
				password += c;
				cout << '*';
		}
		cout << endl;

		map <string, Account> ::iterator it;
		it = accounts.find(login);

		if (it == accounts.end())
		{
				cout << "�������� � ����� ������� ���. ������� ������������������?" << endl;
				int answer;
				while (true)
				{
						cout << "1 - ��, 2 - ��� : ";
						answer = input();
						if (answer < 1 || answer > 2)
						{
								cout << "������, ���������� ��� ���." << endl << "������� ������������������?" << endl;
								continue;
						}
						else
								break;
				}
				if (answer == 1)
				{
						user_registration(accounts);
				}
				else
						return;
		}
		else
		{
				if (it->second.returnPassword(password))
				{
						if (it->second.returnAccess())
						{
								switch (it->second.returnRole())
								{
								case 0:
										menu_admin(accounts);
										return;
								case 1:
										menu_seller();
										return;
								case 2:
										menu_buyer();
										return;
								default:
										return;
								}
						}
						else
						{
								cout << "��� ������� �� �����������.\n����������, ���������� � ��������������" << endl;
								return;
						}
				}
				else
				{
						cout << "�������� ����� �/��� ������. ���������� ��� ���." << endl << endl;
						system("pause");
						return;
				}
		}
}

void user_registration(map <string, Account>& accounts)
{

}
