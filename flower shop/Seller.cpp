#include "Seller.h"

void menu_seller()
{
		vector <string> menu = { "МЕНЮ ПРОДАВЦА",
														 "1 - Просмотр всех цветов",
														 "2 - Внесение проданных цветов",
														 "3 - Сборка заказа",
														 "4 - Выход" };

		int choice = menu_helper(menu);

		switch (choice)
		{
		case 1:
				break;
		default:
				return;
		}
}
