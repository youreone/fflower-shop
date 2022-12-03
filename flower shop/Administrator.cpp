#include "Administrator.h"

void menu_admin(map <string, Account>& accounts, map <string, User>& users, string login)
{
		vector <string> menu = { "���� ��������������", 
														 "1 - ���������� �������� ��������", 
														 "2 - ���������� �������� �������� �������������", 
														 "3 - ���������� �������", 
														 "4 - ���������� ������",
														 "5 - �����"};

		while (true)
		{
				int choice = menu_helper(menu);
				switch (choice)
				{
				case 1:
						menu_accountsManagement(accounts, login);
						break;
				case 2:
						break;
				case 3:
						break;
				case 4:
						break;
				case 5:
						return;
						break;
				default:
				{
						vector <string> menuExit = { "�� ����� ������ ����� �� ������� ������?",
														 "1 - ��, �����",
														 "2 - ���, ���������� ������" };
						choice = menu_helper(menuExit);
						switch (choice)
						{
						case 1:
								return;
						case 2:
								continue;
						}
				}
				}
		}
}

void menu_accountsManagement(map<string, Account>& accounts, string login)
{
		vector <string> menu = { "���������� �������� ��������",
														 "1 - ��������",
														 "2 - ����������",
														 "3 - ��������������",
														 "4 - ��������"};

		while (true)
		{
				int choice = menu_helper(menu);
				switch (choice)
				{
				case 1:
				{
						vector <string> choiceView = { "���� ��������� ������� �������",
																 "1 - ���",
																 "2 - ��������������",
																 "3 - ���������� ��������"};
						
						while (true)
						{
								choice = menu_helper(choiceView);
								if (choice == 4)
										break;
								viewAccounts(accounts, choice, login);
								system("pause");
						}
						break;
				}
				case 2:
				{
						string name, login, password;
						bool role = false;
						while (true)
						{
								system("cls");
								cout << "���� ���������� ������ ���������" << endl << endl;

								while (true)
								{
										name = "";
										cout << "������� ��� (�� ����� 50 ��������) - ";
										getline(cin, name);

										if (name.size() > 50)
										{
												cout << "��� ��������� ������� �������. ����������, ����������� �� ����� 50 ��������." << endl;
												continue;
										}
										else
												break;
								}

								while (true)
								{
										login = "";
										cout << "������� ����� (�� ����� 20 ��������) - ";
										getline(cin, login);

										map <string, Account> ::iterator it;
										it = accounts.find(login);
										if (it != accounts.end())
										{
												cout << "������������ � ����� ������� ��� ����������. ���������� ��� ���." << endl;
												continue;
										} if (login.size() > 20)
										{
												cout << "����� ������� �������. ����������, ����������� �� ����� 20 ��������." << endl;
										}
										else
												break;
								}

								while (true)
								{
										password = "";
										cout << "������� ������ (������� 5 ��������) - ";
										getline(cin, password);
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
										string passwordCheck = "";
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

								while (true)
								{
										int i;
										cout << "������� ���� (����� - 1, �������� - 2) - ";
										
										i = input();
										if (i < 1  ||  i > 2)
										{
												cout << "������� ����� 1 ��� 2. ���������� ��� ���." << endl;
												continue;
										}
										else
										{
												if (i == 1)
														role = true;
												else
														role = false;
												break;
										}
								}

								Account acc(name, login, password, role);
								ofstream out("accounts", ios::binary | ios::app);
								out << acc;
								out.close();
								accounts.insert(make_pair(login, acc));

								cout <<  endl << acc << endl;
								cout << "������������ ������� ��������.\n������ �� ����� ����� � ���� ������� ������." << endl << endl;
								system("pause");
								break;
						}
						break;
				}
				case 3:
				{
						viewAccounts(accounts, 1, "");
						
						while (true)
						{
								cout << endl << "������� ����� �������� ��� �������������� - ";
								int i = input();
								if (i < 1 || i > accounts.size())
								{
										cout << "���������� ��� ���." << endl;
										continue;
								}
								i--;
								map <string, Account> ::iterator it = accounts.begin();
								advance(it, i);
								string newLogin = it->second.Edit(accounts);
								if (it->first != newLogin)
								{
										Account acc;
										acc = it->second;
										accounts.erase(it);
										accounts.insert(make_pair(newLogin, acc));
										break;
								}
								else
										break;
						}

						updateFile(accounts);
						break;
				}
				case 4:
				{
						viewAccounts(accounts, 1, login);

						while (true)
						{
								cout << endl << "������� ����� �������� ��� �������� - ";
								int i = input();
								if (i < 1 || i > accounts.size())
								{
										cout << "���������� ��� ���." << endl;
										continue;
								}
								i--;
								map <string, Account> ::iterator it = accounts.begin();
								advance(it, i);

								if (it->second.returnLogin() == login)
								{
										cout << endl << "��������. �� �� ������ ������� ���� �������." << endl << endl;
										system("pause");
										break;
								}

								accounts.erase(it);
								break;
						}
						updateFile(accounts);
						cout << endl << "������� ������� ������." << endl << endl;
						system("pause");
						break;
				}
				default:
						return;
				}
		}
}

void viewAccounts(map<string, Account>& accounts, int choice, string login)
{
		if (choice == 1)
				cout << endl << "���" << endl;
		if (choice == 2)
				cout << endl <<"��������������" << endl;
		if (choice == 3)
				cout << endl << "���������� ��������" << endl;

		int loginSize = 1;
		int nameSize = 1;
		for (map <string, Account> ::iterator it = accounts.begin(); it != accounts.end(); ++it)
		{
				if (choice == 2  &&  !it->second.role)
						continue;
				if (choice == 3  &&  it->second.role)
						continue;
				loginSize = max(loginSize, it->second.login.size());
				nameSize = max(nameSize, it->second.name.size());
		}

		cout << "|----|----------------|-" << setfill('-') << setw(nameSize) << "" << "-|-" << setfill('-') << setw(loginSize) << "" << "-|" << endl;
		cout << "|#�/�|  ��� ��������  | " << setfill(' ') << setw(nameSize) << left << "���" << " | " << setfill(' ') << setw(loginSize) << "�����" << " |" << endl;
		cout << "|----|----------------|-" << setfill('-') << setw(nameSize) << "" << "-|-" << setfill('-') << setw(loginSize) << "" << "-|" << endl;

		int i = 1;
		for (map <string, Account> ::iterator it = accounts.begin(); it != accounts.end(); it++)
		{
				if (choice == 2 && !it->second.role)
						continue;
				if (choice == 3 && it->second.role)
						continue;
				cout << "| " << i++ << ". | " << setfill(' ') << (it->second.role ? "������������� " : "��������� ���.") << " | " << setw(nameSize) << left << it->second.name << " | " << setw(loginSize) << it->second.login << " |";
				if (it->second.login == login)
						cout << " << ��� �������";
				cout << endl;
				cout << "|----|----------------|-" << setfill('-') << setw(nameSize) << "" << "-|-" << setfill('-') << setw(loginSize) << "" << "-|" << endl;
				cout << setfill(' ');
		}
		return;
}


