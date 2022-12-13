#include "Buyer.h"

void menu_buyer(User user)
{
		vector <string> menu = { "���� ����������",
														 "1 - �������",
														 "2 - ��� ������",
														 "3 - ��������� �������",
														 "4 - �����" };

		while (true)
		{
				int choice = menu_helper(menu);

				switch (choice)
				{
				case 1:
				{
						workCart(user.returnCart());
						break;
				}

				case 2:
				{
						myOrders(user.returnCart());
						break;
				}

				case 4:
						return;
				default:
				{
						vector <string> menuExit = { "�� ����� ������ ����� �� ������� ������?",
														 "1 - ��, �����",
														 "2 - ���, ���������� ������" };
						choice = menu_helper(menuExit);
						switch (choice)
						{
						case 1:
								return;
						case 2:
								continue;
						}
				}
				}
		}
}
