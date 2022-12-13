#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
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
		void updateFlag(map <string, FlowerAdmin>& flowers);
		friend void workCart(Order& cart);
		friend void myOrders(Order& cart);
};

class Check : public Order
{
		int day, month, year;
		bool purchase;
public:
		Check();
		Check(vector <FlowerOrder> cart, float summaFull, float saleFull, int ID, bool purchase);
		friend ofstream& operator<<(ofstream& out, const Check& check);
		friend ifstream& operator>>(ifstream& in, Check& check);
};

