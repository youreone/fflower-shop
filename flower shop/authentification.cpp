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
				if (c == 8)
				{
						if (password.size() == 0)
								continue;
						cout << "\b \b";
						password.erase(password.size() - 1, 1);
						continue;
				}
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
						return;
				}
				else
						return;
		}
		else
		{
				if (it->second.returnPassword(password))
				{
						if (it->second.returnRole())
						{
								menu_admin(accounts);
						}
						else
						{
								menu_seller();
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
		string login, password, name;

		while (true)
		{
				system("cls");
				login = "";
				password = "";
				name = "";

				cout << "------����� ���������� � ���� �����������------" << endl << endl;

				cout << "��� ��� �����? - ";
				getline(cin, name);

				while (true)
				{
						login = "";
						cout << "���������� ����� - ";
						getline(cin, login);
						map <string, Account> ::iterator it;
						it = accounts.find(login);
						if (it != accounts.end())
						{
								cout << "������������ � ����� ������� ��� ����������. ���������� ��� ���." << endl;
								continue;
						}
						else
								break;
				}

				while (true)
				{
						password = "";
						cout << "���������� ������ (������� 5 ��������) - ";
						getline(cin, password);
						if (password.size() < 5)
						{
								cout << "��� ������ ������� ��������. \n����������, ����������� �� ����� 5 ��������." << endl;
								continue;
						}
						else
								break;
				}

				cout << "����������� ������ �������.\n������ �� ������ ����� � ���� ������� ������" << endl;
				system("pause");
				return;
		}
}
