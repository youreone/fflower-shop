#include "Buyer.h"
#include "Order.h"

void myOrders(User& user);

void menu_buyer(User user, map <string, FlowerAdmin>& flowers)
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
						system("pause");
						break;
				}

				case 2:
				{
						myOrders(user);
						system("pause");
						break;
				}

				case 3:
				{

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

void myOrders(User& user)
{
		vector <Check> checks;

		ifstream in("checks", ios::binary);
		if (!in.is_open())
		{
				in.close();
				ofstream out("cheks", ios::binary);
				out.close();
				ifstream in("checks", ios::binary);
		}
		else
		while (true)
		{
				Check check;
				in >> check;
				if (in.eof())
						break;
				checks.push_back(check);
		}
		in.close();

		bool flag = false;
		for (int i = 0; i < checks.size(); i++)
		{
				if (user.ID == checks[i].returnID())
				{
						cout << endl;
						checkOut(checks[i]);
						flag = true;
						cout << endl;
				}
		}

		if (!flag)
		{
				cout << endl << "У вас пока нет заказанных товаров. Но вы всегда можете это сделать в соответствующем меню" << endl << endl;
				return;
		}

		return;
}
