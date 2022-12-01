#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "Order.h"
using namespace std;

class Account
{
protected:
		string name, login, password;
		bool role;
public:
		Account();
		Account(string name, string login, string password, bool role);
		void Edit();
		virtual void writeToFile();
		bool returnPassword(string password);
		bool returnRole();
};

class User : protected Account
{
		Order cart;
public:
		User();
		friend void writeToFile();
};

string encryptionPassword(string password);