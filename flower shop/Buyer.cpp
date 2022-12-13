#include "Buyer.h"

void menu_buyer(User user)
{
		vector <string> menu = { "МЕНЮ ПОКУПАТЕЛЯ",
														 "1 - Корзина",
														 "2 - Мои заказы",
														 "3 - Пополнить корзину",
														 "4 - Выход" };

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
						vector <string> menuExit = { "Вы точно хотите выйти из учетной записи?",
														 "1 - Да, выйти",
														 "2 - Нет, продолжить работу" };
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
