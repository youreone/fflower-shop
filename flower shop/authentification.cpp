#include "authentification.h"


void authentification(map <string, Account>& accounts, map <string, User>& users, map <string, FlowerAdmin>& flowers)
{
		string login, password;


		while (true)
		{
				cout << "������� ����� - ";
				getline(cin, login);
				try
				{
						if (login.size() == 0)
								throw exception("����� �� ����� ���� ������");
						break;
				}
				catch (const exception& ex)
				{
						cout << ex.what() << endl;
						continue;
				}
		}
		
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
				map <string, User> ::iterator userIt;
				userIt = users.find(login);
				if (userIt == users.end())
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
								user_registration(users);
								return;
						}
						else
								return;
				}
				else
				{
						menu_buyer(userIt->second, flowers, users);
				}
		}
		else
		{
				if (it->second.returnPassword(password))
				{
						if (it->second.returnRole())
						{
								menu_admin(accounts, users, flowers, login);
						}
						else
						{
								menu_seller(flowers);
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

void user_registration(map <string, User>& users)
{
		string login, password, passwordCheck, name;

		while (true)
		{
				system("cls");
				login = "";
				password = "";
				name = "";
				passwordCheck = "";

				cout << "------����� ���������� � ���� �����������------" << endl << endl;

				while(true)
				{
						cout << "��� ��� �����? - ";
						getline(cin, name);
						if (name.size() == 0)
						{
								cout << "��� �� ����� ���� ������. ��������� �������" << endl;
								continue;
						}
						break;
				}

				while (true)
				{
						login = "";
						cout << "���������� ����� - ";
						getline(cin, login);
						if (login.size() == 0)
						{
								cout << "����� �� ����� ���� ������. ��������� �������" << endl;
								continue;
						}
						map <string, User> ::iterator it;
						it = users.find(login);
						if (it != users.end())
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
						if (password.size() == 0)
						{
								cout << "������ �� ����� ���� ������. ��������� �������" << endl;
								continue;
						}
						if (password.size() < 5)
						{
								cout << "��� ������ ������� ��������. ���������� ��� ���, ��������� ������� 5 ��������." << endl;
								continue;
						}
						else
								break;
				}

				while (true)
				{
						passwordCheck = "";
						cout << "��������� ������ - ";
						getline(cin, passwordCheck);
						if (passwordCheck != password)
						{
								cout << "������ �� ���������. ���������� ��� ���." << endl;
								continue;
						}
						else
								break;
				}

				Order cart;
				User user(name, login, password, users.size(), cart);
				ofstream out("users", ios::binary | ios::app);
				out << user;
				out.close();
				users.insert(make_pair(login, user));
				cout << "����������� ������ �������.\n������ �� ������ ����� � ���� ������� ������" << endl << endl;
				system("pause");
				return;
		}
}
