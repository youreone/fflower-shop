#pragma once
#include <map>
#include <string>
#include "Account.h"
#include "Administrator.h"
#include "Seller.h"
#include "Buyer.h"

using namespace std;

void authentification(map <string, Account>& accounts);  //���� � �������
void user_registration(map <string, Account>& accounts);      //�����������
