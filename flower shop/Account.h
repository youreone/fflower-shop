#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

class Account
{
protected:
		string name, login, password;
		int role;
		bool access;
public:
		Account();
		Account(string name, string login, string password, int role, bool access);
		void Edit();
		virtual void writeToFile();
		bool returnPassword(string password);
		int returnRole();
		bool returnAccess();
};

class User : protected Account
{
		int orderNumber;
public:
		User();
		friend void writeToFile();
};

string encryptionPassword(string password);