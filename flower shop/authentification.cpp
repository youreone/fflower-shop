#include "authentification.h"

int input()
{
		int n;
		while (!(cin >> n) || (cin.peek() != '\n'))
		{
				cin.clear();
				while (cin.get() != '\n');
				cout << "Ошибка. Пожалуйста, используйте числовой ввод." << endl;
		}

		cin.ignore();
		return n;
}

void authentification(map <string, Account>& accounts)
{
		string login, password;

		cout << "Введите логин - ";
		getline(cin, login);
		cout << "Введите пароль - ";
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
				cout << "Аккаунта с таким логином нет. Желаете зарегистрироваться?" << endl;
				int answer;
				while (true)
				{
						cout << "1 - да, 2 - нет : ";
						answer = input();
						if (answer < 1 || answer > 2)
						{
								cout << "Ошибка, попробуйте еще раз." << endl << "Желаете зарегистрироваться?" << endl;
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
						cout << "Неверный логин и/или пароль. Попробуйте еще раз." << endl << endl;
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

				cout << "------Добро пожаловать в меню регистрации------" << endl << endl;

				cout << "Как вас зовут? - ";
				getline(cin, name);

				while (true)
				{
						login = "";
						cout << "Придумайте логин - ";
						getline(cin, login);
						map <string, Account> ::iterator it;
						it = accounts.find(login);
						if (it != accounts.end())
						{
								cout << "Пользователь с таким логином уже существует. Попробуйте еще раз." << endl;
								continue;
						}
						else
								break;
				}

				while (true)
				{
						password = "";
						cout << "Придумайте пароль (минимум 5 символов) - ";
						getline(cin, password);
						if (password.size() < 5)
						{
								cout << "Ваш пароль слишком короткий. \nПожалуйста, используйте не менее 5 символов." << endl;
								continue;
						}
						else
								break;
				}

				cout << "Регистрация прошла успешно.\nТеперь вы можете войти в свою учетную запись" << endl;
				system("pause");
				return;
		}
}
