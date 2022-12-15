#include "Administrator.h"

void Stat();

class Flow
{
public:
		string name;
		float expenses, parishes;
		Flow(string name)
		{
				this->name = name;
				this->expenses = 0;
				this->parishes = 0;
		}
		void setExp(float expenses)
		{
				this->expenses += expenses;
		}
		void setPar(float parishes)
		{
				this->parishes += parishes;
		}
};

void menu_admin(map <string, Account>& accounts, map <string, User>& users, map <string, FlowerAdmin>& flowers, string login)
{
		vector <string> menu = { "���� ��������������", 
														 "1 - ���������� �������� ��������", 
														 "2 - ���������� �������� �������� �������������", 
														 "3 - ���������� �������", 
														 "4 - ���������� ������",
														 "5 - �����"};

		while (true)
		{
				int choice = menu_helper(menu);
				switch (choice)
				{
				case 1:
						menu_accountsManagement(accounts, login);
						break;
				case 2:
						menu_usersManagement(users);
						break;
				case 3:
						menu_flowerManagement(flowers);
						break;
				case 4:
						Stat();
						system("pause");
						break;
				case 5:
						return;
						break;
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

void menu_accountsManagement(map<string, Account>& accounts, string login)
{
		vector <string> menu = { "���������� �������� ��������",
														 "1 - ��������",
														 "2 - ����������",
														 "3 - ��������������",
														 "4 - ��������"};

		while (true)
		{
				int choice = menu_helper(menu);
				switch (choice)
				{
				case 1:
				{
						vector <string> choiceView = { "���� ��������� ������� �������",
																 "1 - ���",
																 "2 - ��������������",
																 "3 - ���������� ��������"};
						
						while (true)
						{
								choice = menu_helper(choiceView);
								if (choice == 4)
										break;
								viewAccounts(accounts, choice, login);
								system("pause");
						}
						break;
				}
				case 2:
				{
						string name, login, password;
						bool role = false;
						while (true)
						{
								system("cls");
								cout << "���� ���������� ������ ���������" << endl << endl;

								while (true)
								{
										name = "";
										cout << "������� ��� (�� ����� 50 ��������) - ";
										getline(cin, name);
										if (name.size() == 0)
										{
												cout << "��� �� ����� ���� ������. ��������� �������" << endl;
												continue;
										}
										if (name.size() > 50)
										{
												cout << "��� ��������� ������� �������. ����������, ����������� �� ����� 50 ��������." << endl;
												continue;
										}
										else
												break;
								}

								while (true)
								{
										login = "";
										cout << "������� ����� (�� ����� 20 ��������) - ";
										getline(cin, login);
										if (login.size() == 0)
										{
												cout << "����� �� ����� ���� ������. ��������� �������" << endl;
												continue;
										}
										map <string, Account> ::iterator it;
										it = accounts.find(login);
										if (it != accounts.end())
										{
												cout << "������������ � ����� ������� ��� ����������. ���������� ��� ���." << endl;
												continue;
										} if (login.size() > 20)
										{
												cout << "����� ������� �������. ����������, ����������� �� ����� 20 ��������." << endl;
										}
										else
												break;
								}

								while (true)
								{
										password = "";
										cout << "������� ������ (������� 5 ��������) - ";
										getline(cin, password);
										if (password.size() == 0)
										{
												cout << "������ �� ����� ���� ������. ��������� �������" << endl;
												continue;
										}
										if (password.size() < 5)
										{
												cout << "��� ������ ������� ��������. ���������� ��� ���, ��������� ������� 5 ��������." << endl;
												continue;
										}
										else
												break;
								}

								while (true)
								{
										string passwordCheck = "";
										cout << "��������� ������ - ";
										getline(cin, passwordCheck);
										if (passwordCheck != password)
										{
												cout << "������ �� ���������. ���������� ��� ���." << endl;
												continue;
										}
										else
												break;
								}

								while (true)
								{
										int i;
										cout << "������� ���� (����� - 1, �������� - 2) - ";
										
										i = input();
										if (i < 1  ||  i > 2)
										{
												cout << "������� ����� 1 ��� 2. ���������� ��� ���." << endl;
												continue;
										}
										else
										{
												if (i == 1)
														role = true;
												else
														role = false;
												break;
										}
								}

								Account acc(name, login, password, role);
								ofstream out("accounts", ios::binary | ios::app);
								out << acc;
								out.close();
								accounts.insert(make_pair(login, acc));

								cout <<  endl << acc << endl;
								cout << "������������ ������� ��������.\n������ �� ����� ����� � ���� ������� ������." << endl << endl;
								system("pause");
								break;
						}
						break;
				}
				case 3:
				{
						viewAccounts(accounts, 1, "");
						
						while (true)
						{
								cout << endl << "������� ����� �������� ��� �������������� - ";
								int i = input();
								if (i < 1 || i > accounts.size())
								{
										cout << "���������� ��� ���." << endl;
										continue;
								}
								i--;
								map <string, Account> ::iterator it = accounts.begin();
								advance(it, i);
								string newLogin = it->second.Edit(accounts);
								if (it->first != newLogin)
								{
										Account acc;
										acc = it->second;
										accounts.erase(it);
										accounts.insert(make_pair(newLogin, acc));
										break;
								}
								else
										break;
						}

						updateFileAccounts(accounts);
						break;
				}
				case 4:
				{
						viewAccounts(accounts, 1, login);

						while (true)
						{
								cout << endl << "������� ����� �������� ��� �������� - ";
								int i = input();
								if (i < 1 || i > accounts.size())
								{
										cout << "���������� ��� ���." << endl;
										continue;
								}
								i--;
								map <string, Account> ::iterator it = accounts.begin();
								advance(it, i);

								if (it->second.returnLogin() == login)
								{
										cout << endl << "��������. �� �� ������ ������� ���� �������." << endl << endl;
										system("pause");
										break;
								}

								accounts.erase(it);
								break;
						}
						updateFileAccounts(accounts);
						cout << endl << "������� ������� ������." << endl << endl;
						system("pause");
						break;
				}
				default:
						return;
				}
		}
}

void menu_usersManagement(map<string, User>& users)
{
		vector <string> menu = { "���������� �������� ��������",
														 "1 - ��������",
														 "2 - ��������" };

		while (true)
		{
				int choice = menu_helper(menu);

				switch (choice)
				{
				case 1:
				{
						viewUsers(users);
						system("pause");
						break;
				}
				case 2:
				{
						viewUsers(users);

						while (true)
						{
								cout << endl << "������� ����� �������� ��� �������� - ";
								int i = input();
								if (i < 1 || i > users.size())
								{
										cout << "���������� ��� ���." << endl;
										continue;
								}
								i--;
								map <string, User> ::iterator it = users.begin();
								advance(it, i);

								users.erase(it);
								break;
						}
						updateFileUsers(users);
						cout << endl << "������� ������� ������." << endl << endl;
						system("pause");
						break;
				}
				default:
						return;
				}
		}
}

void menu_flowerManagement(map<string, FlowerAdmin>& flowers)
{
		vector <string> menu = { "���������� ��������� ���������",
														 "1 - ��������",
														 "2 - ����������",
														 "3 - ��������������",
														 "4 - ��������"};

		while (true)
		{
				int choice = menu_helper(menu);

				switch (choice)
				{
				case 1:
				{
						viewFlowers(flowers);
						system("pause");
						break;
				}
				case 2:
				{
						addFlower(flowers);
						break;
				}

				case 3:
				{
						viewFlowers(flowers);
						cout << endl;

						int i;
						while (true)
						{
								cout << "������� ����� ������ ��� �������������� - ";
								i = input();

								if (i < 1 || i > flowers.size())
								{
										cout << "������. ������� �������������� ����� ��������� ������." << endl;
										continue;
								}
								else
								{
										i--;
										break;
								}
						}

						map <string, FlowerAdmin> ::iterator it = flowers.begin();
						advance(it, i);
						string newName;
						newName = Editflower(flowers, it);
						if (it->first != newName)
						{
								FlowerAdmin flower;
								flower = it->second;
								flowers.erase(it);
								flowers.insert(make_pair(flower.returnName(), flower));
						}

						updateFileFlowers(flowers);
						break;
				}

				case 4:
				{
						viewFlowers(flowers);
						cout << endl;

						int i;
						while (true)
						{
								cout << "������� ����� ������ ��� �������� - ";
								i = input();

								if (i < 1 || i > flowers.size())
								{
										cout << "������. ������� �������������� ����� ��������� ������." << endl;
										continue;
								}
								else
								{
										i--;
										break;
								}
						}

						map <string, FlowerAdmin> ::iterator it = flowers.begin();
						advance(it, i);
						flowers.erase(it);
						updateFileFlowers(flowers);
						cout << endl << "����� ������� ������" << endl << endl;
						system("pause");
						break;
				}

				default:
						return;
				}
		}
}

void viewAccounts(map<string, Account>& accounts, int choice, string login)
{
		if (choice == 1)
				cout << endl << "���" << endl;
		if (choice == 2)
				cout << endl <<"��������������" << endl;
		if (choice == 3)
				cout << endl << "���������� ��������" << endl;

		int loginSize = 1;
		int nameSize = 1;
		for (map <string, Account> ::iterator it = accounts.begin(); it != accounts.end(); ++it)
		{
				if (choice == 2  &&  !it->second.role)
						continue;
				if (choice == 3  &&  it->second.role)
						continue;
				loginSize = max(loginSize, it->second.login.size());
				nameSize = max(nameSize, it->second.name.size());
		}

		cout << "|----|----------------|-" << setfill('-') << setw(nameSize) << "" << "-|-" << setfill('-') << setw(loginSize) << "" << "-|" << endl;
		cout << "|#�/�|  ��� ��������  | " << setfill(' ') << setw(nameSize) << left << "���" << " | " << setfill(' ') << setw(loginSize) << "�����" << " |" << endl;
		cout << "|----|----------------|-" << setfill('-') << setw(nameSize) << "" << "-|-" << setfill('-') << setw(loginSize) << "" << "-|" << endl;

		int i = 1;
		for (map <string, Account> ::iterator it = accounts.begin(); it != accounts.end(); it++)
		{
				if (choice == 2 && !it->second.role)
						continue;
				if (choice == 3 && it->second.role)
						continue;
				cout << "| " << i++ << ". | " << setfill(' ') << (it->second.role ? "������������� " : "��������� ���.") << " | " << setw(nameSize) << left << it->second.name << " | " << setw(loginSize) << it->second.login << " |";
				if (it->second.login == login)
						cout << " << ��� �������";
				cout << endl;
				cout << "|----|----------------|-" << setfill('-') << setw(nameSize) << "" << "-|-" << setfill('-') << setw(loginSize) << "" << "-|" << endl;
				cout << setfill(' ');
		}
		return;
}

void viewUsers(map<string, User>& users)
{
		if (users.size() == 0)
		{
				cout << endl << "������� ������������� ����������� � �������." << endl << endl;
				return;
		}

		int loginSize = 6;
		int nameSize = 5;
		for (map <string, User> ::iterator it = users.begin(); it != users.end(); ++it)
		{
				loginSize = max(loginSize, it->second.login.size());
				nameSize = max(nameSize, it->second.name.size());
		}

		cout << "|----|----------------|-" << setfill('-') << setw(nameSize) << "" << "-|-" << setfill('-') << setw(loginSize) << "" << "-|" << endl;
		cout << "|#�/�|  ��� ��������  | " << setfill(' ') << setw(nameSize) << left << "���" << " | " << setfill(' ') << setw(loginSize) << "�����" << " |" << endl;
		cout << "|----|----------------|-" << setfill('-') << setw(nameSize) << "" << "-|-" << setfill('-') << setw(loginSize) << "" << "-|" << endl;

		int i = 1;
		for (map <string, User> ::iterator it = users.begin(); it != users.end(); it++)
		{
				cout << "| " << i++ << ". | " << setfill(' ') << " ������������  | " << setw(nameSize) << left << it->second.name << " | " << setw(loginSize) << it->second.login << " |" << endl;
				cout << "|----|----------------|-" << setfill('-') << setw(nameSize) << "" << "-|-" << setfill('-') << setw(loginSize) << "" << "-|" << endl;
				cout << setfill(' ');
		}
		cout << endl;
		return;
}

void viewFlowers(map<string, FlowerAdmin>& flowers)
{
		if (flowers.size() == 0)
		{
				cout << endl << "������ � ������� ����������� � �������." << endl << endl;
				return;
		}

		int nameSize = 8;
		for (map <string, FlowerAdmin>::iterator it = flowers.begin(); it != flowers.end(); it++)
		{
				nameSize = max(nameSize, it->second.name.size());
		}

		cout << "|----|-" << setfill('-') << setw(nameSize) << "" << "-|-----------|-----------|--------|--------------|" << endl << setfill(' ');
		cout << "|    | " << setw(nameSize) << "��������" <<         " | �� ������ | ��������� | ������ | ���� ������� |" << endl;
		cout << "|----|-" << setfill('-') << setw(nameSize) << "" << "-|-----------|-----------|--------|--------------|" << endl << setfill(' ');

		int i = 1;
		for (map <string, FlowerAdmin>::iterator it = flowers.begin(); it != flowers.end(); it++)
		{
				cout << "| " << i++ << ". | " << setw(nameSize) << left << it->second.name << " | " << setw(9) << it->second.count << " | " << setw(9) << right << fixed << setprecision(2) << it->second.price << " | " << setw(5) << (int)(it->second.sale * 100) << "% |  " << setfill('0') << setw(2) << right << it->second.deliveryDay << '.' << setw(2) << it->second.deliveryMonth << '.' << setw(4) << it->second.deliveryYear << "  |" << setfill(' ') << left << endl;
				cout << "|----|-" << setfill('-') << setw(nameSize) << "" << "-|-----------|-----------|--------|--------------|" << setfill(' ') << endl;
		}
		return;
}

string Editflower(map<string, FlowerAdmin>& flowers, map<string, FlowerAdmin>::iterator flowerIt)
{
		vector <string> menu = { "��� �� ������ ���������������?",
														 "1 - ��������",
														 "2 - ����",
														 "3 - ������" };

		while (true)
		{
				int choice = menu_helper(menu);
				cout << "�� ������������ ���� �����: " << endl << endl << flowerIt->second << endl;

				switch (choice)
				{
				case 1:
				{
						while (true)
						{
								string name;
								while(true)
								{
										cout << "������� ����� �������� - ";
										getline(cin, name);
										if (name.size() == 0)
										{
												cout << "�������� �� ����� ���� ������. ��������� �������" << endl;
												continue;
										}
										if (name.size() == 0)
										{
												cout << "�������� �� ����� ���� ������. ��������� �������" << endl;
												continue;
										}
										break;
								}

								map <string, FlowerAdmin>::iterator it = flowers.find(name);
								if (it != flowers.end())
								{
										cout << "����� �������� ��� ����. ���������� ��� ���" << endl;
										continue;
								}
								flowerIt->second.name = name;
								break;
						}
						cout << endl << "������ ���� ����� �������� ���: " << endl << endl << flowerIt->second << endl;
						cout << "������� �� ���� �������������� ��� ���������� ���������" << endl << endl;
						system("pause");
						break;
				}

				case 2:
				{
						while (true)
						{
								float price;
								cout << "������� ����� ���� - ";
								price = floatInput();
								if (price <= 0)
								{
										cout << "������. ������� ����� ������������� �����" << endl << endl;
										continue;
								}
								if (price >= 1000000)
								{
										cout << "������. ������� ������� ���� (�������� - 999999.99)" << endl << endl;
										continue;
								}
								flowerIt->second.price = price;
								break;
						}
						cout << endl << "������ ���� ����� �������� ���: " << endl << endl << flowerIt->second << endl;
						cout << "������� �� ���� �������������� ��� ���������� ���������" << endl << endl;
						system("pause");
						break;
				}

				case 3:
				{
						while (true)
						{
								cout << "����� ������ �� ������ ��������� �� �����? - ";
								int s = input();
								if (s < 0 || s > 100)
								{
										cout << "������. ������ ����� ���� �� 0 �� 100%" << endl << endl;
										continue;
								}

								flowerIt->second.sale = s / 100.f;
								break;
						}
						cout << endl << "������ ���� ����� �������� ���: " << endl << endl << flowerIt->second << endl;
						cout << "������� �� ���� �������������� ��� ���������� ���������" << endl << endl;
						system("pause");
						break;
				}

				default:
						return flowerIt->second.name;
				}
		}
}

void addFlower(map<string, FlowerAdmin>& flowers)
{
		vector <string> menu = { "���������� ������",
														 "1 - ����� ��� ������������� ������",
														 "2 - ����� ������ ������" };
		bool flag = true;

		while (true)
		{
				int choice = menu_helper(menu);

				switch (choice)
				{
				case 1:
				{
						viewFlowers(flowers);

						cout << endl;

						int i;
						while (true)
						{
								cout << "������� ����� ������ ��� ���������� - ";
								i = input();

								if (i < 1 || i > flowers.size())
								{
										cout << "������. ������� �������������� ����� ��������� ������." << endl;
										continue;
								}
								else
								{
										i--;
										break;
								}
						}

						map <string, FlowerAdmin> ::iterator it = flowers.begin();
						advance(it, i);
						system("cls");
						cout << "�� ���������� ���� �����:" << endl << endl << it->second << endl;

						int count;
						while (true)
						{
								cout << "������� ������ �� ������ ��������? - ";
								count = input();
								if (count <= 0)
								{
										cout << "������. ������� ����� �������������� ����� ������� �� ������ ��������." << endl << endl;
										continue;
								}
								
								break;
						}

						while (true)
						{
								cout << "�� ����� ���� �� ��������? - ";
								float price = floatInput();
								if (price <= 0)
								{
										cout << "������. ������� ����� ������������� �����" << endl << endl;
										continue;
								}
								if (price >= 1000000)
								{
										cout << "������. ������� ������� ���� (�������� - 999999.99)" << endl << endl;
										continue;
								}

								int day, month, year;
								returnTime(day, month, year);
								it->second.request(count, day, month, year);
								updateFileFlowers(flowers);
								cout << endl << it->second << endl << "���������� ������ ������� ���������." << endl << endl;
								it->second.updateExpensesFile(count, price);
								system("pause");
								break;
						}

						break;
				}
				
				case 2:
				{
						string name;
						while(true)
						{
								cout << endl << "������� �������� ������ - ";
								getline(cin, name);
								if (name.size() == 0)
								{
										cout << "�������� �� ����� ���� ������. ��������� �������" << endl;
										continue;
								}
								break;
						}
						if (name[0] >= 'a' && name[0] <= 'z')
								name[0] = name[0] + ('Z' - 'z');
						if (name[0] >= '�' && name[0] <= '�')
								name[0] = name[0] + ('�' - '�');

						map <string, FlowerAdmin>::iterator it = flowers.find(name);
						if (it != flowers.end())
						{
								cout << endl << "����� ����� ������������ � �������. ����������, ����������� ���� ������ ��� ������������ �������" << endl << endl;
								system("pause");
								break;
						}

						int count;
						while (true)
						{
								cout << "������� ������ �� ������ ��������? - ";
								count = input();
								if (count <= 0)
								{
										cout << "������. ������� ����� �������������� ����� ������� �� ������ ��������." << endl << endl;
										continue;
								}

								break;
						}

						float price;
						while (true)
						{
								cout << "�� ����� ���� �� ��������? - ";
								price = floatInput();
								if (price <= 0)
								{
										cout << "������. ������� ����� ������������� �����" << endl << endl;
										continue;
								}
								if (price >= 1000000)
								{
										cout << "������. ������� ������� ���� (�������� - 999999.99)" << endl << endl;
										continue;
								}
								break;
						}

						float sale;
						while (true)
						{
								cout << "����� ������ �� ������ ��������� �� �����? - ";
								int s = input();
								if (s < 0 ||  s > 100)
								{
										cout << "������. ������ ����� ���� �� 0 �� 100%" << endl << endl;
										continue;
								}

								sale = s / 100.f;
								break;
						}

						int day, month, year;
						returnTime(day, month, year);
						FlowerAdmin flower(name, count, price + price * 0.4, sale, day, month, year);
						flowers.insert(make_pair(name, flower));
						ofstream out("flowers", ios::binary | ios::app);
						out << flower;
						out.close();
						flower.updateExpensesFile(count, price);
						cout << "����� ������� ��������" << endl << endl << flower << endl;
						system("pause");
						break;
				}

				default:
						return;
				}
		}

}

void Stat()
{
		vector <Check> checks;
		map <string, Flow> flowers;
		ifstream in("checks", ios::binary);
		if (!in.is_open())
		{
				in.close();
				ofstream out("checks", ios::binary | ios::app);
				out.close();
				ifstream in("checks", ios::binary);
		}

		while (true)
		{
				Check check;
				in >> check;
				if (in.eof())
						break;
				if (check.returnPurchase())
						checks.push_back(check);
		}
		in.close();

		for (int i = 0; i < checks.size(); i++)
		{
				for (int j = 0; j < checks[i].cart.size(); j++)
				{
						if (flowers.find(checks[i].cart[j].name) == flowers.end())
						{
								Flow flow(checks[i].cart[j].name);
								flowers.insert(make_pair(checks[i].cart[j].name, flow));
						}
						flowers.find(checks[i].cart[j].name)->second.setPar(checks[i].cart[j].price * checks[i].cart[j].count - checks[i].cart[j].price * checks[i].cart[j].count * checks[i].cart[j].sale);
				}
		}

		float price, Fullexpenses = 0, fullParishes = 0;
		int count;
		string name;
		in.open("expenses", ios::binary);
		while (true)
		{
				in.read((char*)&count, sizeof(count));
				if (in.eof())
						break;
				in.read((char*)&price, sizeof(price));

				size_t len;
				char* buf;

				in.read((char*)&len, sizeof(len));
				buf = new char[len];
				in.read(buf, len);
				name = buf;                              //���������� �����
				delete[] buf;

				if (flowers.find(name) == flowers.end())
				{
						Flow flow(name);
						flowers.insert(make_pair(name, flow));
				}

				flowers.find(name)->second.setExp(count * price);
		}

		in.close();

		int nameSize = 8;
		for (map <string, Flow>::iterator it = flowers.begin(); it != flowers.end(); ++it)
		{
				nameSize = max(nameSize, it->second.name.size());
		}

		cout << "|-" << setfill('-') << setw(nameSize) << "" << "-|------------|-------------|" << setfill(' ') << endl;
		cout << "| " << setw(nameSize) << "��������" <<         " |   ������   |   ������    |" << endl;
		cout << "|-" << setfill('-') << setw(nameSize) << "" << "-|------------|-------------|" << setfill(' ') << endl;


		for (map <string, Flow>::iterator it = flowers.begin(); it != flowers.end(); ++it)
		{
				Fullexpenses += it->second.expenses;
				fullParishes += it->second.parishes;

				cout << "| " << setw(nameSize) << it->second.name << " | " << fixed << setprecision(2) << setw(10) << it->second.expenses << " | " << fixed << setprecision(2) << setw(11) << it->second.parishes << " |" << endl;
				cout << "|-" << setfill('-') << setw(nameSize) << "" << " |------------|-------------|" << setfill(' ') << endl;
		}
		cout << endl << "�� ���������� " << fullParishes << "�." << endl;
		cout << "�� ��������� " << Fullexpenses << "�." << endl;
		if (fullParishes < Fullexpenses)
				cout << endl << "�� ������� � �����. ������ ������� �� �������������" << endl << endl;
		else
				cout << endl << "�� �������� � ����. ����������" << endl << endl;


		ofstream out ("statistic.txt", ios::trunc);
		for (map <string, Flow>::iterator it = flowers.begin(); it != flowers.end(); ++it)
		{
				out << "| " << setw(nameSize) << it->second.name << " | " << fixed << setprecision(2) << setw(10) << it->second.expenses << " | " << fixed << setprecision(2) << setw(11) << it->second.parishes << " |" << endl;
				out << "|-" << setfill('-') << setw(nameSize) << "" << "-|------------|-------------|" << setfill(' ') << endl;
		}
		out << endl << "�� ���������� " << fullParishes << "�." << endl;
		out << "�� ��������� " << Fullexpenses << "�." << endl;
		if (fullParishes < Fullexpenses)
				out << endl << "�� ������� � �����. ������ ������� �� �������������" << endl;
		else
				out << endl << "�� �������� � ����. ����������" << endl;

		out.close();
		return;
}
