#pragma once
#include <map>
#include <string>
#include <vector>
#include <iomanip>
#include "Account.h"
#include "menu_helper.h"
using namespace std;

void menu_admin(map <string, Account>& accounts, map <string, User>& users, string login);
void menu_accountsManagement(map <string, Account>& accounts, string login);
