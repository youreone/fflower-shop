#include "Seller.h"

void menu_seller()
{
		vector <string> menu = { "���� ��������",
														 "1 - �������� ���� ������",
														 "2 - �������� ��������� ������",
														 "3 - ������ ������",
														 "4 - �����" };

		int choice = menu_helper(menu);

		switch (choice)
		{
		case 1:
				break;
		default:
				return;
		}
}
