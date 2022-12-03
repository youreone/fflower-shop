#include "Administrator.h"

void menu_admin(map <string, Account>& accounts, map <string, User>& users, string login)
{
		vector <string> menu = { "МЕНЮ АДМИНИСТРАТОРА", 
														 "1 - Управление учетными записями", 
														 "2 - Управление учетными записями пользователей", 
														 "3 - Управление товаром", 
														 "4 - Статистика дохода",
														 "5 - Выход"};

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
						vector <string> menuExit = { "Вы точно хотите выйти из учетной записи?",
														 "1 - Да, выйти",
														 "2 - Нет, продолжить работу" };
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
		vector <string> menu = { "УПРАВЛЕНИЕ УЧЕТНЫМИ ЗАПИСЯМИ",
														 "1 - Просмотр",
														 "2 - Добавление",
														 "3 - Редактирование",
														 "4 - Удаление"};

		while (true)
		{
				int choice = menu_helper(menu);
				switch (choice)
				{
				case 1:
				{
						vector <string> choiceView = { "МЕНЮ ПРОСМОТРА УЧЕТНЫХ ЗАПИСЕЙ",
																 "1 - Все",
																 "2 - Администраторы",
																 "3 - Сотрудники магазина"};
						
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
								cout << "МЕНЮ ДОБАВЛЕНИЯ НОВОГО РАБОТНИКА" << endl << endl;

								while (true)
								{
										name = "";
										cout << "Введите ФИО (не более 50 символов) - ";
										getline(cin, name);

										if (name.size() > 50)
										{
												cout << "Имя работника слишком длинное. Пожалуйста, используйте не более 50 символов." << endl;
												continue;
										}
										else
												break;
								}

								while (true)
								{
										login = "";
										cout << "Введите логин (не более 20 символов) - ";
										getline(cin, login);

										map <string, Account> ::iterator it;
										it = accounts.find(login);
										if (it != accounts.end())
										{
												cout << "Пользователь с таким логином уже существует. Попробуйте еще раз." << endl;
												continue;
										} if (login.size() > 20)
										{
												cout << "Логин слишком длинный. Пожалуйста, используйте не более 20 символов." << endl;
										}
										else
												break;
								}

								while (true)
								{
										password = "";
										cout << "Введите пароль (минимум 5 символов) - ";
										getline(cin, password);
										if (password.size() < 5)
										{
												cout << "Ваш пароль слишком короткий. Попробуйте еще раз, используя минимум 5 символов." << endl;
												continue;
										}
										else
												break;
								}

								while (true)
								{
										string passwordCheck = "";
										cout << "Повторите пароль - ";
										getline(cin, passwordCheck);
										if (passwordCheck != password)
										{
												cout << "Пароли не совпадают. Попробуйте еще раз." << endl;
												continue;
										}
										else
												break;
								}

								while (true)
								{
										int i;
										cout << "Введите роль (Админ - 1, Продавец - 2) - ";
										
										i = input();
										if (i < 1  ||  i > 2)
										{
												cout << "Введите цифры 1 или 2. Попробуйте еще раз." << endl;
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
								cout << "Пользователь успешно добавлен.\nТеперь он может войти в свою учетную запись." << endl << endl;
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
								cout << endl << "Введите номер аккаунта для редактирования - ";
								int i = input();
								if (i < 1 || i > accounts.size())
								{
										cout << "Попробуйте еще раз." << endl;
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
								cout << endl << "Введите номер аккаунта для удаления - ";
								int i = input();
								if (i < 1 || i > accounts.size())
								{
										cout << "Попробуйте еще раз." << endl;
										continue;
								}
								i--;
								map <string, Account> ::iterator it = accounts.begin();
								advance(it, i);

								if (it->second.returnLogin() == login)
								{
										cout << endl << "ВНИМАНИЕ. Вы не можете удалить свой аккаунт." << endl << endl;
										system("pause");
										break;
								}

								accounts.erase(it);
								break;
						}
						updateFile(accounts);
						cout << endl << "Аккаунт успешно удален." << endl << endl;
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
				cout << endl << "ВСЕ" << endl;
		if (choice == 2)
				cout << endl <<"АДМИНИСТРАТОРЫ" << endl;
		if (choice == 3)
				cout << endl << "СОТРУДНИКИ МАГАЗИНА" << endl;

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
		cout << "|#п/п|  Тип аккаунта  | " << setfill(' ') << setw(nameSize) << left << "Имя" << " | " << setfill(' ') << setw(loginSize) << "Логин" << " |" << endl;
		cout << "|----|----------------|-" << setfill('-') << setw(nameSize) << "" << "-|-" << setfill('-') << setw(loginSize) << "" << "-|" << endl;

		int i = 1;
		for (map <string, Account> ::iterator it = accounts.begin(); it != accounts.end(); it++)
		{
				if (choice == 2 && !it->second.role)
						continue;
				if (choice == 3 && it->second.role)
						continue;
				cout << "| " << i++ << ". | " << setfill(' ') << (it->second.role ? "Администратор " : "Сотрудник маг.") << " | " << setw(nameSize) << left << it->second.name << " | " << setw(loginSize) << it->second.login << " |";
				if (it->second.login == login)
						cout << " << Ваш аккаунт";
				cout << endl;
				cout << "|----|----------------|-" << setfill('-') << setw(nameSize) << "" << "-|-" << setfill('-') << setw(loginSize) << "" << "-|" << endl;
				cout << setfill(' ');
		}
		return;
}


