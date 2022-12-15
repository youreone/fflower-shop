#include "Buyer.h"
#include "Order.h"

void myOrders(User& user);

void menu_buyer(User& user, map <string, FlowerAdmin>& flowers, map <string, User>& users)
{
		vector <string> menu = { "���� ����������",
														 "1 - �������",
														 "2 - ��� ������",
														 "3 - ��������� �������",
														 "4 - �������� �������",
														 "5 - �����" };

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
								cout << "���� ����� ��� � ���������: " << endl;
						}
						checkOut(checks[i]);
						flag = true;
						cout << endl;
				}
		}

		if (!flag)
		{
				cout << endl << "�� ��� ������ �� ���������� � ����� ��������.�� �� ������ ������ ��� ������� � ��������������� ����" << endl << endl;
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
						cout << "������� ����� ������������ ������ - ";
						choice = input();
						if (choice < 1 || choice > flowers.size())
						{
								cout << "������. ���������� ������� ����� ������������� ������" << endl << endl;
								continue;
						}
						break;
				}
				choice--;
				map <string, FlowerAdmin>::iterator it = flowers.begin();
				advance(it, choice);
				cout << endl << "�� ������� ���� �����:" << endl << endl << it->second << endl << endl;

				int count;
				while (true)
				{
						cout << "������� ���������� ������������ ������ - ";
						count = input();
						if (count < 1)
						{
								cout << "������. ���������� ������� ������������� ����� �������" << endl << endl;
								continue;
						}
						bool flag = true;
						if (count > it->second.count)
						{
								cout << endl << "�� ������ �������� ������ ������, ��� ���� �� ������." << endl << "��� �������� ��������� �������� � �������, ����� �� ���� �������� ��� �����." << endl << "�������� ��� ����� ����� �������. �������, ��� ������ ����������? (1 - ��, 2 - ���) -";
								while (flag)
								{
										int ch = input();
										if (ch < 1 || ch > 2)
										{
												cout << "�� �������, ��� ������ ���������� �����? (1 - ��, 2 - ���) - ";
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
				cout << endl << "����� ������� �����������.\n�� �������� " << count << " ������� �� ����� " << fixed << setprecision(2) << (it->second.price * count) - (it->second.price * count * it->second.sale) << "�." << endl << endl;
				user.cart.summaFull += (it->second.price * count) - (it->second.price * count * it->second.sale);
				user.cart.saleFull += it->second.price * count * it->second.sale;

				int ch;
				while (true)
				{
						cout << "������ �������� ��� �������? (1 - ��, 2 - ���) - ";
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
		cout << endl << "���� ������� �������" << endl << endl;
		return;
}