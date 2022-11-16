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
								cout << "Ваш аккаунт не подтвержден.\nПожалуйста, обратитесь к администратору" << endl;
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

}
