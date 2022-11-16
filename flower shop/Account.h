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
		void writeToFile();
		bool returnPassword(string password);
		int returnRole();
		bool returnAccess();
};

string encryptionPassword(string password);