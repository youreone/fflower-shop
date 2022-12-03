#include "Order.h"

Order::Order()
{
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
