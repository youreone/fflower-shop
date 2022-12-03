#pragma once
#include <map>
#include <string>
#include "Account.h"
#include "Administrator.h"
#include "Seller.h"
#include "Buyer.h"
#include "menu_helper.h"

using namespace std;

void authentification(map <string, Account>& accounts, map <string, User>& users);  //вход в систему
void user_registration(map <string, User>& users);      //регистрация
