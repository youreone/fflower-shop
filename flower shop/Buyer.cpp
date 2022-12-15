#include "Buyer.h"
#include "Order.h"

void myOrders(User& user);

void menu_buyer(User& user, map <string, FlowerAdmin>& flowers, map <string, User>& users)
{
		vector <string> menu = { "МЕНЮ ПОКУПАТЕЛЯ",
														 "1 - Корзина",
														 "2 - Мои заказы",
														 "3 - Пополнить корзину",
														 "4 - Очистить корзину",
														 "5 - Выход" };

		while (true)
		{
				int choice = menu_helper(menu);

				switch (choice)
				{
				case 1:
				{
						workCart(user.returnCart(), user.returnID());
						updateFileUsers(users);
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
						topUpShoppingCart(flowers, user);
						updateFileUsers(users);
						system("pause");
						break;
				}

				case 4:
				{
						deleteCart(user);
						system("pause");
						break;
				}

				case 5:
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
				ofstream out("checks", ios::binary);
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
						if (!checks[i].returnPurchase())
						{
								cout << "Этот заказ еще в обработке: " << endl;
						}
						checkOut(checks[i]);
						flag = true;
						cout << endl;
				}
		}

		if (!flag)
		{
				cout << endl << "Вы еще ничего не заказывали в нашем магазине.Но вы всегда можете это сделать в соответствующем меню" << endl << endl;
				return;
		}

		return;
}

void topUpShoppingCart(map <string, FlowerAdmin>& flowers, User& user)
{
		while (true)
		{
				viewFlowers(flowers);

				int choice;
				while (true)
				{
						cout << "Введите номер добавляемого товара - ";
						choice = input();
						if (choice < 1 || choice > flowers.size())
						{
								cout << "Ошибка. Пожалуйста введите номер существующего товара" << endl << endl;
								continue;
						}
						break;
				}
				choice--;
				map <string, FlowerAdmin>::iterator it = flowers.begin();
				advance(it, choice);
				cout << endl << "Вы выбрали этот товар:" << endl << endl << it->second << endl << endl;

				int count;
				while (true)
				{
						cout << "Введите Количество добавляемого товара - ";
						count = input();
						if (count < 1)
						{
								cout << "Ошибка. Пожалуйста введите положительное число товаров" << endl << endl;
								continue;
						}
						bool flag = true;
						if (count > it->second.count)
						{
								cout << endl << "Вы хотите заказать товара больше, чем есть на складе." << endl << "Вам позвонит сотрудник компании и уточнит, может ли быть оформлен ваш заказ." << endl << "Возможно ваш заказ будет отменен. Уверены, что хотите продолжить? (1 - да, 2 - нет) -";
								while (flag)
								{
										int ch = input();
										if (ch < 1 || ch > 2)
										{
												cout << "Вы уверены, что хотите продолжить заказ? (1 - да, 2 - нет) - ";
												continue;
										}
										if (ch == 1)
												break;
										else
												flag = false;
								}
						}
						if (flag)
								break;
						else
								continue;
				}

				FlowerOrder flower(it->second.name, true, count, it->second.price, it->second.sale);
				user.cart.cart.push_back(flower);
				cout << endl << "Заказ успешно сформирован.\nВы добавили " << count << " товаров на сумму " << fixed << setprecision(2) << (it->second.price * count) - (it->second.price * count * it->second.sale) << "р." << endl << endl;
				user.cart.summaFull += (it->second.price * count) - (it->second.price * count * it->second.sale);
				user.cart.saleFull += it->second.price * count * it->second.sale;

				int ch;
				while (true)
				{
						cout << "Хотите добавить еще товаров? (1 - да, 2 - нет) - ";
						ch = input();
						if (ch < 1 || ch > 2)
						{
								continue;
						}
						break;
				}
				if (ch == 1)
						continue;
				else
						break;
		}
}

void deleteCart(User& user)
{
		user.cart.cart.clear();
		cout << endl << "Ваша корзина очищена" << endl << endl;
		return;
}