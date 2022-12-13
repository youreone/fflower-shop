#define _CRT_SECURE_NO_WARNINGS
#include "Order.h"
void returnTime(int& day, int& month, int& year);
int input();
//void ReturnTime(int& day, int& month, int& year)
//{
//		time_t now = time(0);
//		tm* ltm = localtime(&now);
//
//		year = 1900 + ltm->tm_year;
//		month = 1 + ltm->tm_mon;
//		day = ltm->tm_mday;
//}

Order::Order()
{
		this->saleFull = 0;
		this->ID = 0;
		this->summaFull = 0;
		this->cart = {};
}

void Order::updateFlag(map <string, FlowerAdmin>& flowers)
{
		map <string, FlowerAdmin>::iterator it;

		for (int i = 0; i < cart.size(); i++)
		{
				it = flowers.find(cart[i].returnName());
				if (it == flowers.end())
				{
						cart[i].setFlag(false);
				}
				else if (it->second.returnCount() < cart[i].returnCount())
						cart[i].setFlag(false);
		}
}

ofstream& operator<<(ofstream& out, const Order& order)
{
		out.write((char*)&order.ID, sizeof(order.ID));
		out.write((char*)&order.summaFull, sizeof(order.summaFull));
		out.write((char*)&order.saleFull, sizeof(order.saleFull));

		int size = order.cart.size();
		out.write((char*)&size, sizeof(size));

		for (int i = 0; i < size; i++)
		{
				out << order.cart[i];
		}

		return out;
}

ifstream& operator>>(ifstream& in, Order& order)
{
		in.read((char*)&order.ID, sizeof(order.ID));
		in.read((char*)&order.summaFull, sizeof(order.summaFull));
		in.read((char*)&order.saleFull, sizeof(order.saleFull));
		
		int size;
		in.read((char*)&size, sizeof(size));

		FlowerOrder buf;
		for (int i = 0; i < size; i++)
		{
				in >> buf;
				order.cart.push_back(buf);
		}

		return in;
}

void workCart(Order& Cart)
{
		if (Cart.cart.size() == 0)
		{
				cout << endl << "������� ���� �����. �� �� ������ �������� ������ � ��������������� ����." << endl << endl;
				system("pause");
				return;
		}
		int nameSize = 8;
		Cart.summaFull = 0;
		Cart.saleFull = 0;
		for (int i = 0; i < Cart.cart.size(); i++)
		{
				nameSize = max(nameSize, (int)(Cart.cart[i].name.size()));
				Cart.summaFull += Cart.cart[i].price * Cart.cart[i].count;
				Cart.saleFull += Cart.cart[i].price * Cart.cart[i].count * Cart.cart[i].sale;
		}

		cout << "|----|-" << setfill('-') << setw(nameSize) << "" << "-|-----------|------------|---------------|-----------------|" << setfill(' ');
		cout << "|    | " << setw(nameSize) << "��������" <<         " | ��������� | ���������� | ������ (���.) | ���� �� ������� |";
		cout << "|----|-" << setfill('-') << setw(nameSize) << "" << "-|-----------|------------|---------------|-----------------|" << setfill(' ');

		for (int i = 0; i < Cart.cart.size(); i++)
		{
				cout << "| " << i + 1 << ". | " << setfill('-') << setw(nameSize) << Cart.cart[i].name << " | "
						<< fixed << setprecision(2) << setw(6) << Cart.cart[i].price << " | "
						<< setw(10) << Cart.cart[i].count << " | "
						<< fixed << setprecision(2) << setw(13) << Cart.cart[i].price * Cart.cart[i].count * Cart.cart[i].sale << " | "
						<< fixed << setprecision(2) << setw(15) << Cart.cart[i].price * Cart.cart[i].count - Cart.cart[i].price * Cart.cart[i].count * Cart.cart[i].sale << " |";
				cout << "|----|-" << setfill('-') << setw(nameSize) << "" << "-|-----------|------------|---------------|-----------------|" << setfill(' ');
		}

		cout << endl;
		cout << "| �������";
		cout.setf(ios::right);
		cout.width(67 + nameSize);
		cout << Cart.cart.size() << " |";
		cout.unsetf(ios::right);

		cout << "| ������";
		cout.setf(ios::right);
		cout.width(68 + nameSize);
		cout << Cart.saleFull << " |";
		cout.unsetf(ios::right);

		cout << "| ����� � ������";
		cout.setf(ios::right);
		cout.width(60 + nameSize);
		cout << Cart.summaFull << " |";
		cout.unsetf(ios::right);

		cout << endl << endl;
		while (true)
		{
				cout << "�� ������ �������� ����� ��� ���������� �������? (1 - ��������, 2 - ����������) - ";
				int choice = input();
				if (choice < 1 || choice > 2)
				{
						cout << "������� 1 ��� 2" << endl << endl;
						continue;
				}
				switch (choice)
				{
				case 1:
				{
						Check check;
						ofstream out("check", ios::binary | ios::app);
						out << check;
						out.close();
						cout << endl << "����� ������� ��������!" << endl << endl;
						system("pause");
						break;
				}
				default:
						return;
				}
		}
}

void myOrders(Order& Cart)
{


}

ofstream& operator<<(ofstream& out, const Check& check)
{
		out.write((char*)&check.ID, sizeof(check.ID));
		out.write((char*)&check.summaFull, sizeof(check.summaFull));
		out.write((char*)&check.saleFull, sizeof(check.saleFull));
		out.write((char*)&check.day, sizeof(check.day));
		out.write((char*)&check.month, sizeof(check.month));
		out.write((char*)&check.year, sizeof(check.year));
		out.write((char*)&check.purchase, sizeof(check.purchase));

		int size = check.cart.size();
		out.write((char*)&size, sizeof(size));

		for (int i = 0; i < size; i++)
		{
				out << check.cart[i];
		}

		return out;
}

ifstream& operator>>(ifstream& in, Check& check)
{
		in.read((char*)&check.ID, sizeof(check.ID));
		in.read((char*)&check.summaFull, sizeof(check.summaFull));
		in.read((char*)&check.saleFull, sizeof(check.saleFull));
		in.read((char*)&check.day, sizeof(check.day));
		in.read((char*)&check.month, sizeof(check.month));
		in.read((char*)&check.year, sizeof(check.year));
		in.read((char*)&check.purchase, sizeof(check.purchase));

		int size;
		in.read((char*)&size, sizeof(size));

		FlowerOrder buf;
		for (int i = 0; i < size; i++)
		{
				in >> buf;
				check.cart.push_back(buf);
		}

		return in;
}

Check::Check()
{
		returnTime(this->day, this->month, this->year);
		this->purchase = false;
}

Check::Check(vector<FlowerOrder> cart, float summaFull, float saleFull, int ID, bool purchase)
{
		this->cart = cart;
		this->summaFull = summaFull;
		this->saleFull = saleFull;
		this->ID = ID;
		returnTime(this->day, this->month, this->year);
		this->purchase = purchase;
}
