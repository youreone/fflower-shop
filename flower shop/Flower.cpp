#include "Flower.h"

Flower::Flower()
{
}

FlowerOrder::FlowerOrder()
{
		this->name = "";
		this->count = 0;
		this->price = 0;
		this->sale = 0;
		this->flag = true;
}

string FlowerOrder::returnName()
{
		return this->name;
}

void FlowerOrder::setFlag(bool fl)
{
		this->flag = fl;
}

int FlowerOrder::returnCount()
{
		return this->count;
}

ofstream& operator<<(ofstream& out, const FlowerOrder& flower)
{
		out.write((char*)&flower.count, sizeof(flower.count));
		out.write((char*)&flower.price, sizeof(flower.price));
		out.write((char*)&flower.sale, sizeof(flower.sale));

		size_t len;

		len = flower.name.length() + 1;                            // запись имени
		out.write((char*)&len, sizeof(len));
		out.write((char*)flower.name.c_str(), len);

		return out;
}

ofstream& operator<<(ofstream& out, const FlowerAdmin& flower)
{
		out.write((char*)&flower.count, sizeof(flower.count));
		out.write((char*)&flower.price, sizeof(flower.price));
		out.write((char*)&flower.sale, sizeof(flower.sale));
		out.write((char*)&flower.deliveryDay, sizeof(flower.deliveryDay));
		out.write((char*)&flower.deliveryMonth, sizeof(flower.deliveryMonth));
		out.write((char*)&flower.deliveryYear, sizeof(flower.deliveryYear));

		size_t len;

		len = flower.name.length() + 1;                            // запись имени
		out.write((char*)&len, sizeof(len));
		out.write((char*)flower.name.c_str(), len);

		return out;
}

ifstream& operator>>(ifstream& in,FlowerOrder& flower)
{
		in.read((char*)&flower.count, sizeof(flower.count));     
		in.read((char*)&flower.price, sizeof(flower.price));
		in.read((char*)&flower.sale, sizeof(flower.sale));

		size_t len;
		char* buf;

		in.read((char*)&len, sizeof(len));
		buf = new char[len];
		in.read(buf, len);
		flower.name = buf;                              //считывание имени
		delete[] buf;

		return in;
}

ifstream& operator>>(ifstream& in, FlowerAdmin& flower)
{
		in.read((char*)&flower.count, sizeof(flower.count));
		if (in.eof())
				return in;
		in.read((char*)&flower.price, sizeof(flower.price));
		in.read((char*)&flower.sale, sizeof(flower.sale));
		in.read((char*)&flower.deliveryDay, sizeof(flower.deliveryDay));
		in.read((char*)&flower.deliveryMonth, sizeof(flower.deliveryMonth));
		in.read((char*)&flower.deliveryYear, sizeof(flower.deliveryYear));

		size_t len;
		char* buf;

		in.read((char*)&len, sizeof(len));
		buf = new char[len];
		in.read(buf, len);
		flower.name = buf;                              //считывание имени
		delete[] buf;

		return in;
}

ostream& operator<<(ostream& ostream, const FlowerAdmin& flower)
{
		ostream << "|-" << setfill('-') << setw(flower.name.size()) << "" << "-|-----------|-----------|--------|--------------|" << endl << setfill(' ');
		ostream << "| " << setw(flower.name.size()) << "Название" << " | На складе | Стоимость | Скидка | Дата привоза |" << endl;
		ostream << "|-" << setfill('-') << setw(flower.name.size()) << "" << "-|-----------|-----------|--------|--------------|" << endl << setfill(' ');

		ostream << "| " << setw(flower.name.size()) << left << flower.name << " | " << setw(9) << flower.count << " | " << setw(9) << right << fixed << setprecision(2) << flower.price << " | " << setw(5) << (int)(flower.sale * 100) << "% |  " << setfill('0') << setw(2) << right << flower.deliveryDay << '.' << setw(2) << flower.deliveryMonth << '.' << setw(4) << flower.deliveryYear << "  |" << setfill(' ') << left << endl;
		ostream << "|-" << setfill('-') << setw(flower.name.size()) << "" << "-|-----------|-----------|--------|--------------|" << endl << setfill(' ') << endl;
		
		return ostream;
}

void updateFileFlowers(map<string, FlowerAdmin>& flowers)
{
		ofstream out("flowers", ios::binary | ios::trunc);

		for (map <string, FlowerAdmin> ::iterator it = flowers.begin(); it != flowers.end(); it++)
		{
				out << it->second;
		}

		out.close();
		return;
}

FlowerAdmin::FlowerAdmin()
{
		this->name = "";
		this->count = 0;
		this->price = 0;
		this->sale = 0;
		this->deliveryDay = 1;
		this->deliveryMonth = 1;
		this->deliveryYear = 1970;
}

FlowerAdmin::FlowerAdmin(string name, int count, float price, float sale, int day, int month, int year)
{
		this->name = name;
		this->count = count;
		this->price = price;
		this->sale = sale;
		this->deliveryDay = day;
		this->deliveryMonth = month;
		this->deliveryYear = year;
}

FlowerAdmin FlowerAdmin::operator=(FlowerAdmin flower)
{
		string name = flower.name;
		int count = flower.count;
		float price = flower.price;
		float sale = flower.sale;
		int day = flower.deliveryDay;
		int month = flower.deliveryMonth;
		int year = flower.deliveryYear;

		return FlowerAdmin(name, count, price, sale, day, month, year);
}

string FlowerAdmin::returnName()
{
		return this->name;
}

int FlowerAdmin::returnCount()
{
	return this->count;
}

void FlowerAdmin::request(int count, int day, int month, int year)
{
		this->count += count;
		this->deliveryDay = day;
		this->deliveryMonth = month;
		this->deliveryYear = year;
}

void FlowerAdmin::updateExpensesFile(int count, float price)
{
		ofstream out("expenses", ios::binary | ios::app);

		out.write((char*)&count, sizeof(count));
		out.write((char*)&price, sizeof(price));

		size_t len;

		len = this->name.length() + 1;                            // запись имени
		out.write((char*)&len, sizeof(len));
		out.write((char*)this->name.c_str(), len);

		out.close();
}

string FlowerAdmin::Edit(map<string, FlowerAdmin>& flowers)
{
		vector <string> menu = { "Что вы хотите отредактировать?",
														 "1 - Название",
														 "2 - Цену",
														 "3 - Скидку"};

		while (true)
		{
				int choice = menu_helper(menu);
				cout << "Вы редактируете этот товар: " << endl << endl << *this << endl;

				switch (choice)
				{
				case 1:
				{
						while (true)
						{
								string name;
								cout << "Введите новое название - ";
								getline(cin, name);

								map <string, FlowerAdmin>::iterator it = flowers.find(name);
								if (it != flowers.end())
								{
										cout << "Такое название уже есть. Попробуйте еще раз" << endl;
										continue;
								}
								this->name = name;
								break;
						}
						break;
				}

				case 2:
				{
						while (true)
						{
								float price;
								cout << "Введите новую цену - ";
								price = floatInput();
								if (price <= 0)
								{
										cout << "ОШИБКА. Введите целое положительное число" << endl << endl;
										continue;
								}
								if (price >= 1000000)
								{
										cout << "ОШИБКА. Слишком большая цена (максимум - 999999.99" << endl << endl;
										continue;
								}
								this->price = price;
								break;
						}
						break;
				}

				case 3:
				{
						while (true)
						{
								cout << "Какую скидку вы хотите выставить на товар? - ";
								int s = input();
								if (s < 0 || s > 100)
								{
										cout << "ОШИБКА. Скидка может быть от 0 до 100%" << endl << endl;
										continue;
								}

								this->sale = s / 100.f;
								break;
						}
						break;
				}

				default:
						return this->name;
				}
		}
}
