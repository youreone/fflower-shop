#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <map>
#include "Order.h"
#include "menu_helper.h"
using namespace std;

class Account
{
private:
		string name, login, password;
		bool role;
public:
		Account();
		Account(string name, string login, string password, bool role);
		string Edit(map <string, Account>& accounts);
		friend ofstream& operator<<(ofstream& out, Account& acc);
		friend ostream& operator<<(ostream& ostream, Account& acc);
		Account operator=(Account acc);
		bool returnPassword(string password);
		bool returnRole();
		string returnLogin();
		friend void viewAccounts(map <string, Account>& accounts, int choice, string login);
		friend void updateFileAccounts(map <string, Account>& accounts);
};

class User
{
		string name, login, password;
		Order cart;
		int ID;
public:
		User(string FIO, string login, string password, int ID);
		friend ofstream& operator<<(ofstream& out, User& user);
		friend void viewUsers(map<string, User>& users);
		friend void updateFileUsers(map <string, User>& users);
		friend void updateUserCart(map<string, User>& users, map <string, FlowerAdmin>& flowers);
		Order& returnCart();
};

string encryptionPassword(string password);