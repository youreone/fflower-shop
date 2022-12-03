#include "Flower.h"

Flower::Flower()
{
}

FlowerOrder::FlowerOrder()
{
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
