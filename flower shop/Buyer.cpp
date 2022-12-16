#include "Buyer.h"
#include "Order.h"
#include "search.cpp"

bool compName(FlowerAdmin a, FlowerAdmin b)
{
				return a.name < b.name;
}

bool compPrice(FlowerAdmin a, FlowerAdmin b)
{
		if (a.price != b.price)
				return a.price < b.price;
		else
				return a.name < b.name;
}

bool compSale(FlowerAdmin a, FlowerAdmin b)
{
		if (a.sale != b.sale)
				return a.sale < b.sale;
		else if (a.price != b.price)
				return a.price < b.price;
		else
				return a.name < b.name;
}

void myOrders(User& user);

void menu_buyer(User& user, map <string, FlowerAdmin>& flowers, map <string, User>& users)
{
		vector <string> menu = { "���� ����������",
														 "1 - ������ ���������� ������",
														 "2 - ��� ������",
														 "3 - �������",
														 "4 - ��������� �������",
														 "5 - �������� �������",
														 "6 - �����" };

		while (true)
		{
				int choice = menu_helper(menu);

				switch (choice)
				{
				case 1:
				{
						viewFlowersWithSort(flowers);
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
						workCart(user.returnCart(), user.returnID());
						updateFileUsers(users);
						system("pause");
						break;
				}

				case 4:
				{
						topUpShoppingCart(flowers, user);
						updateFileUsers(users);
						system("pause");
						break;
				}

				case 5:
				{
						deleteCart(user);
						system("pause");
						break;
				}

				case 6:
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
						checkOut(checks[i], i + 1);
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

void viewVector(vector <FlowerAdmin> flowers)
{
		if (flowers.size() == 0)
		{
				cout << endl << "�� ������ ������� ������ �� �������." << endl << endl;
				return;
		}

		int nameSize = 8;
		for (int i = 0; i < flowers.size(); i++)
		{
				nameSize = max(nameSize, flowers[i].name.size());
		}

		cout << "|----|-" << setfill('-') << setw(nameSize) << "" << "-|-----------|-----------|--------|--------------|" << endl << setfill(' ');
		cout << "|    | " << setw(nameSize) << "��������" << " | �� ������ | ��������� | ������ | ���� ������� |" << endl;
		cout << "|----|-" << setfill('-') << setw(nameSize) << "" << "-|-----------|-----------|--------|--------------|" << endl << setfill(' ');

		int k = 1;
		for (int i = 0; i < flowers.size(); i++)
		{
				cout << "| " << k++ << ". | " << setw(nameSize) << left << flowers[i].name << " | " << setw(9) << flowers[i].count << " | " << setw(9) << right << fixed << setprecision(2) << flowers[i].price << " | " << setw(5) << (int)(flowers[i].sale * 100) << "% |  " << setfill('0') << setw(2) << right << flowers[i].deliveryDay << '.' << setw(2) << flowers[i].deliveryMonth << '.' << setw(4) << flowers[i].deliveryYear << "  |" << setfill(' ') << left << endl;
				cout << "|----|-" << setfill('-') << setw(nameSize) << "" << "-|-----------|-----------|--------|--------------|" << setfill(' ') << endl;
		}
		return;
}

void viewFlowersWithSort(map <string, FlowerAdmin> fl)
{
		vector <FlowerAdmin> flowers;
		for (map <string, FlowerAdmin>::iterator it = fl.begin(); it != fl.end(); ++it)
		{
				flowers.push_back(it->second);
		}

		vector <string> menu = { "���� ���������",
														 "1 - ���",
														 "2 - ����������",
														 "3 - �����",
														 "4 - ������"};

		while (true)
		{
				int choice = menu_helper(menu);

				switch (choice)
				{
				case 1:
						viewFlowers(fl);
						system("pause");
						break;

				case 2:
				{
						vector <string> menuSort = { "���� ����������",
														 "1 - �� ��������",
														 "2 - �� ����",
														 "3 - �� ������" };
						bool fl = true;
						while (fl)
						{
								fl = true;
								int ch = menu_helper(menuSort);

								switch (ch)
								{
								case 1:
										sort(flowers.begin(), flowers.end(), compName);
										viewVector(flowers);
										system("pause");
										break;

								case 2:
										sort(flowers.begin(), flowers.end(), compPrice);
										viewVector(flowers);
										system("pause");
										break;
								case 3:
										sort(flowers.begin(), flowers.end(), compSale);
										viewVector(flowers);
										system("pause");
										break;
								default:
										fl = false;
								}
						}
						break;
				}

				case 3:
				{
						vector <string> menuSearch = { "���� ������",
														 "1 - �� ��������",
														 "2 - �� ����" };

						vector <FlowerAdmin> flowerSearch;
						string s;

						bool flag = true;
						while (flag)
						{
								int chh = menu_helper(menuSearch);

								switch (chh)
								{
								case 1:
								{
										while (true)
										{
												cout << "������� ������� �������� - ";
												getline(cin, s);
												if (s.size() == 0)
												{
														cout << "�������� �� ����� ���� ������." << endl << endl;
														continue;
												}
												break;
										}

										s = Search::search <string>::toLower(s);
										for (int i = 0; i < flowers.size(); i++)
										{
												string name = Search::search <string> ::toLower(flowers[i].name);
												if (name.find(s) != string::npos)
														flowerSearch.push_back(flowers[i]);
										}

										viewVector(flowerSearch);
										flowerSearch.clear();
										system("pause");
										break;
								}
								
								case 2:
								{
										string time;
										int day, month, year;

										while (true)
										{
												time = "";
												cout << "������� ���� � ������� ��.��.���� - ";

												char c;
												while (true)
												{
														c = _getch();
														if (c == 8)
														{
																if (time.size() == 0)
																		continue;
																if (time.size() == 2 || time.size() == 4)
																{
																		cout << "\b \b";
																		cout << "\b \b";
																		time.erase(time.size() - 1, 1);
																		continue;
																}
																cout << "\b \b";
																time.erase(time.size() - 1, 1);
																continue;
														}
														if (c == '\r')
																if (time.size() == 8)
																		break;
														if (c < '0' || c > '9')
																continue;
														if (time.size() == 8)
																continue;
														time += c;
														cout << c;
														if (time.size() == 2 || time.size() == 4)
																cout << '.';
												}

												day = (time[0] - '0') * 10 + (time[1] - '0');
												month = (time[2] - '0') * 10 + (time[3] - '0');
												year = (time[4] - '0') * 1000 + (time[5] - '0') * 100 + (time[6] - '0') * 10 + (time[7] - '0');
												if (day == 0 || day > 31 || month == 0 || month > 12 || year < 2022)
												{
														cout << endl << "������. ����������� ����. ���������� ��� ���." << endl << endl;
														continue;
												}

												if ((month == 2 || month == 4 || month == 6 || month == 9 || month == 11) && day == 31)
												{
														cout << endl << "������. ����������� ����. ���������� ��� ���." << endl << endl;
														continue;
												}

												if (month == 2 && day > 29)
												{
														cout << endl << "������. ����������� ����. ���������� ��� ���." << endl << endl;
														continue;
												}

												if (!(year % 4 == 0 && year % 400 == 0 && year % 100 != 0) && month == 2 && day == 29)
												{
														cout << endl << "������. ����������� ���� (29 ������� � ������������ ����). ���������� ��� ���." << endl << endl;
														continue;
												}

												cout << endl << endl;
												break;
										}

										for (int i = 0; i < flowers.size(); i++)
										{
												if(flowers[i].deliveryDay == day && flowers[i].deliveryMonth == month && flowers[i].deliveryYear == year)
														flowerSearch.push_back(flowers[i]);
										}

										viewVector(flowerSearch);
										flowerSearch.clear();
										system("pause");
										break;
								}

								default:
										flag = false;
								}
						}

						break;
				}

				case 4:
				{
						vector <string> menuFiltr = { "���� ����������",
														 "1 - ���� �� - ��",
														 "2 - ������ �� �������",
														 "3 - ��� ������",
														 "4 - �� ������"};
						vector <FlowerAdmin> flowerSearch;
						bool fl = true;
						while (fl)
						{
								int ch = menu_helper(menuFiltr);

								switch (ch)
								{
								case 1:
								{
										int c1, c2;
										while (true)
										{
												cout << "������� ����������� ���� - ";
												c1 = input();
												if (c1 < 0)
												{
														cout << "���� �� ����� ���� �������������. ����������, ��������� �������" << endl << endl;
														continue;
												}
												break;
										}
										while (true)
										{
												cout << "������� ������������ ���� - ";
												c2 = input();
												if (c2 < 0)
												{
														cout << "���� �� ����� ���� �������������. ����������, ��������� �������" << endl << endl;
														continue;
												}
												break;
										}

										for (int i = 0; i < flowers.size(); i++)
										{
												if (flowers[i].price >= c1 && flowers[i].price <= c2)
														flowerSearch.push_back(flowers[i]);
										}
										viewVector(flowerSearch);
										flowerSearch.clear();
										system("pause");
										break;
								}

								case 2:
								{
										for (int i = 0; i < flowers.size(); i++)
										{
												if (flowers[i].sale > 0)
														flowerSearch.push_back(flowers[i]);
										}
										viewVector(flowerSearch);
										flowerSearch.clear();
										system("pause");
										break;
								}

								case 3:
								{
										for (int i = 0; i < flowers.size(); i++)
										{
												if (flowers[i].sale == 0)
														flowerSearch.push_back(flowers[i]);
										}
										viewVector(flowerSearch);
										flowerSearch.clear();
										system("pause");
										break;
								}

								case 4:
								{
										vector <FlowerAdmin> flowerSearch;
										string s;
										while (true)
										{
												cout << "������� ������� ����� ������ - ";
												getline(cin, s);
												if (s.size() == 0)
												{
														cout << "�������� �� ����� ���� ������." << endl << endl;
														continue;
												}
												break;
										}

										s = Search::search <string>::toLower(s);
										for (int i = 0; i < flowers.size(); i++)
										{
												string name = Search::search <string> ::toLower(flowers[i].name);
												if (name.find(s) != string::npos)
														flowerSearch.push_back(flowers[i]);
										}

										viewVector(flowerSearch);
										system("pause");
										break;
								}

								default:
										fl = false;
								}
						}


						
						break;
				}

				default:
						return;
				}
		}
}