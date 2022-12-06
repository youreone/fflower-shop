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
		this->role = role;           //����� = true, �������� ������ = false
}

string Account::Edit(map <string, Account>& accounts)
{
		
		vector <string> menu = { "��� �� ������ ���������������?",
														 "1 - ���",
														 "2 - �����"};

		while (true)
		{
				int choice = menu_helper(menu);
				cout << endl << "������ ���� ������� �������� ���: " << endl << *this << endl;

				switch (choice)
				{
				case 1:
				{
						string name;
						while (true)
						{
								name = "";
								cout << "������� ��� (�� ����� 50 ��������) - ";
								getline(cin, name);

								if (name.size() > 50)
								{
										cout << "��� ������� �������. ����������, ����������� �� ����� 50 ��������." << endl;
										continue;
								}
								else
										break;
						}

						this->name = name;
						cout << endl << "������ ���� ������� �������� ���: " << endl << *this << endl;
						system("pause");
						break;
				}
				case 2:
				{
						string login;
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

						this->login = login;
						cout << endl << "������ ���� ������� �������� ���: " << endl << *this << endl;
						system("pause");
						break;
				}
				default:
						return this->login;
				}
		}
}

ofstream& operator<<(ofstream& out, Account& acc)
{
		acc.password = encryptionPassword(acc.password);

		//ofstream out("accounts", ios::binary | ios::app);
		out.write((char*)&acc.role, sizeof(acc.role));        // ������ ����

		size_t len;

		len = acc.name.length() + 1;                            // ������ �����
		out.write((char*)&len, sizeof(len));
		out.write((char*)acc.name.c_str(), len);

		len = acc.login.length() + 1;                           // ������ ������
		out.write((char*)&len, sizeof(len));
		out.write((char*)acc.login.c_str(), len);

		len = acc.password.length() + 1;                        // ������ ������
		out.write((char*)&len, sizeof(len));
		out.write((char*)acc.password.c_str(), len);

		//out.close();
		return out;
}

ostream& operator<<(ostream& ostream, Account& acc)
{
		ostream << "|----------------|-" << setfill('-') << setw(acc.name.size()) << "" << "-|-" << setfill('-') << setw(acc.login.size()) << "" << "-|" << endl;
		ostream << "| " << (acc.role ? "������������� " : "��������� ���.") << " | " << setw(acc.name.size()) << left << acc.name << " | " << setw(acc.login.size()) << acc.login << " |" << endl;
		ostream << "|----------------|-" << setfill('-') << setw(acc.name.size()) << "" << "-|-" << setfill('-') << setw(acc.login.size()) << "" << "-|" << endl;
		ostream << setfill(' ');
		return ostream;
}

Account Account::operator=(Account acc)
{
		string name = acc.name;
		string login = acc.login;
		string password = acc.password;
		bool role = acc.role;
		return Account(name, login, password, role);
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

string Account::returnLogin()
{
		return this->login;
}

ofstream& operator<<(ofstream& out, User& user)
{
		user.password = encryptionPassword(user.password);

		out.write((char*)&user.ID, sizeof(user.ID));

		size_t len;

		len = user.name.length() + 1;                            // ������ �����
		out.write((char*)&len, sizeof(len));
		out.write((char*)user.name.c_str(), len);

		len = user.login.length() + 1;                           // ������ ������
		out.write((char*)&len, sizeof(len));
		out.write((char*)user.login.c_str(), len);

		len = user.password.length() + 1;                        // ������ ������
		out.write((char*)&len, sizeof(len));
		out.write((char*)user.password.c_str(), len);

		out << user.cart;

		return out;
}

string encryptionPassword(string password)
{
		string encryptedPassword = "";

		for (int i = 0; i < password.size(); i++)
				encryptedPassword += password[i] ^ i;

		return encryptedPassword;
}

void updateFileAccounts(map<string, Account>& accounts)
{
		ofstream out("accounts", ios::binary | ios::trunc);
		
		for (map <string, Account> ::iterator it = accounts.begin(); it != accounts.end(); it++)
		{
				it->second.password = encryptionPassword(it->second.password);
				out << it->second;
		}

		out.close();
		return;
}

User::User(string FIO, string login, string password, int ID)
{
		this->name = FIO;
		this->login = login;
		this->password = password;
		this->ID = ID;
}

void updateFileUsers(map<string, User>& users)
{
		ofstream out("users", ios::binary | ios::trunc);

		for (map <string, User> ::iterator it = users.begin(); it != users.end(); it++)
		{
				it->second.password = encryptionPassword(it->second.password);
				out << it->second;
		}

		out.close();
		return;
}

void updateUserCart(map<string, User>& users, map<string, FlowerAdmin>& flowers)
{
		for (map <string, User>::iterator it = users.begin(); it != users.end(); it++)
		{
				it->second.cart.updateFlag(flowers);
		}
}
