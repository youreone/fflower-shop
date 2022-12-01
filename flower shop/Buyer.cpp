#include "Buyer.h"

void menu_buyer()
{
		vector <string> menu = { "МЕНЮ ПОКУПАТЕЛЯ",
														 "1 - Просмотр всех цветов",
														 "2 - Оформить заказ",
														 "3 - Выход" };

		int choice = menu_helper(menu);

		switch (choice)
		{
		case 1:
				break;
		default:
				return;
		}
}
