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

string FlowerAdmin::returnName()
{
		return this->name;
}
