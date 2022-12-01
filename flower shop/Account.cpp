#include "Account.h"

Account::Account()
{
		this->name = "";
		this->login = "";
		this->password = "";
		this->role = false;
}

Account::Account(string name, string login, string password, bool role)
{
		this->name = name;
		this->login = login;
		this->password = password;
		this->role = role;           //админ = true, работник склада = false
}

void Account::Edit()
{
}

void Account::writeToFile()
{
		this->password = encryptionPassword(this->password);

		ofstream out("accounts", ios::binary | ios::app);
		out.write((char*)&this->role, sizeof(this->role));        // запись роли

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

		out.close();
		return;
}

bool Account::returnPassword(string password)
{
		password = encryptionPassword(password);
		
		if (this->password == password)
				return true;
		return false;
}

bool Account::returnRole()
{
		return this->role;
}

string encryptionPassword(string password)
{
		string encryptedPassword = "";

		for (int i = 0; i < password.size(); i++)
				encryptedPassword += password[i] ^ i;

		return encryptedPassword;
}

User::User()
{
		
}

void writeToFile()
{
}
