#include "Account.h"

Account::Account()
{
		this->name = "";
		this->login = "";
		this->password = "";
		this->role = 0;
		this->access = false;
}

Account::Account(string name, string login, string password, int role, bool access)
{
		this->name = name;
		this->login = login;
		this->password = password;
		this->role = role;           //админ = 0, продавец = 1
		this->access = access;       //false - запрещено, true - разрешено
}

void Account::Edit()
{
}

void Account::writeToFile()
{
		ofstream out("accounts", ios::binary | ios::app);
		out.write((char*)&this->role, sizeof(this->role));        // запись роли
		out.write((char*)&this->access, sizeof(this->access));    // запись уровня доступа

		size_t len;

		len = this->name.length() + 1;                            // запись имени
		out.write((char*)&len, sizeof(len));
		out.write((char*)this->name.c_str(), len);

		len = this->login.length() + 1;                           // запись логина
		out.write((char*)&len, sizeof(len));
		out.write((char*)this->login.c_str(), len);

		len = this->password.length() + 1;                        // запись пароля
		out.write((char*)&len, sizeof(len));
		out.write((char*)this->password.c_str(), len);

		return;
}

bool Account::returnPassword(string password)
{
		password = encryptionPassword(password);
		
		if (this->password == password)
				return true;
		return false;
}

int Account::returnRole()
{
		return this->role;
}

bool Account::returnAccess()
{
		return this->access;
}

string encryptionPassword(string password)
{
		string encryptedPassword = "";

		for (int i = 0; i < password.size(); i++)
				encryptedPassword += password[i] ^ i;

		return encryptedPassword;
}
