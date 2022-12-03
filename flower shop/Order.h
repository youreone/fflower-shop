#pragma once
#include <vector>
#include <fstream>
#include "Flower.h"
using namespace std;

class Order
{
protected:
		vector <FlowerOrder> cart;
		float summaFull, saleFull;
		int ID;
public:
		Order();
		friend ofstream& operator<<(ofstream& out, const Order& order);
		friend ifstream& operator>>(ifstream& in, Order& order);
};

