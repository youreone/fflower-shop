#include "Administrator.h"

void menu_admin(map <string, Account>& accounts)
{
		vector <string> menu = { "���� ��������������", 
														 "1 - �������� ������� �������", 
														 "2 - �������������� ������� ������", 
														 "3 - ���������� ������� ������", 
														 "4 - �������� ������� ������",
														 "5 - �������� ���� ������",
														 "6 - �������������� ������",
														 "7 - ������ �� ������� ������",
														 "8 - �������� ������",
														 "9 - ���������� ������",
														 "10 - �����"};

		int choice = menu_helper(menu);

		switch (choice)
		{
		case 1:
				break;
		default:
				return;
		}
}
