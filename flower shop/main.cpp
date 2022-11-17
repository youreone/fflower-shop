// 
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <Windows.h>
#include <map>
#include <conio.h>
#include "Account.h"
#include "Administrator.h"
#include "Seller.h"
#include "authentification.h"
using namespace std;

map <string, Account> readAccounts();                     //считывает данные о всех аккаунтах
map <string, User> readUser();


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

		cout << "Меню предварительной загрузки" << endl << endl;
		map <string, Account> accounts = readAccounts();
		system("pause");
		system("cls");

		while (true)
		{
				cout << "Добро пожаловать в систему" << endl << endl << "(На этом шаге вы можете безопасно закрыть программу)" << endl << endl;
				authentification(accounts);
				system("cls");
		}

    return 0;
}

map <string, Account> readAccounts()  //считывает данные о всех аккаунтах
{
		string name, login, password;
		int role;
		bool access;
		map <string, Account> accounts;
		ifstream in("accounts", ios::binary | ios::in);
		if (!in.is_open())
		{
				cout << "Внимание! Файл аккаунтов не доступен или удален. Будет создан новый файл" << endl;
				in.close();
				ofstream out("accounts", ios::binary | ios::out);
				out.close();
				return accounts;
		}

		while (!in.eof())
		{
				in.read((char*)&role, sizeof(role));     //считывание роли
				if (in.eof())
						break;
				in.read((char*)&access, sizeof(access)); //считывание уровня доступа

				size_t len;
				char* buf;

				in.read((char*)&len, sizeof(len));
				buf = new char[len];
				in.read(buf, len);
				name = buf;                              //считывание имени
				delete[] buf;

				in.read((char*)&len, sizeof(len));
				buf = new char[len];
				in.read(buf, len);
				login = buf;                             //считывание логина
				delete[] buf;

				in.read((char*)&len, sizeof(len));
				buf = new char[len];
				in.read(buf, len);
				password = buf;                          //считывание пароля
				delete[] buf;

				Account acc(name, login, password, role, access);
				accounts.insert(make_pair(login, acc));
		}

		in.close();
		cout << "Считывание данных аккаунтов прошло успешно." << endl;
		return accounts;
}

map <string, User> readUser()
{
		map <string, User> users;
		return users;
}