#include "Buyer.h"

void menu_buyer()
{
		vector <string> menu = { "���� ����������",
														 "1 - �������� ���� ������",
														 "2 - �������� �����",
														 "3 - �����" };

		int choice = menu_helper(menu);

		switch (choice)
		{
		case 1:
				break;
		default:
				return;
		}
}
