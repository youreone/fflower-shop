#pragma once
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Flower
{
protected:
		string name;
public:
		Flower();  
};

class FlowerAdmin : protected Flower
{
		int deliveryDay, deliveryMonth, deliveryYear, life, pastLife, count;
		float price, sale;
};

class FlowerOrder : protected Flower
{
		int count;
		float price, sale;
public:
		FlowerOrder();
		friend ofstream& operator<<(ofstream& out, const FlowerOrder& flower);
		friend ifstream& operator>>(ifstream& in, FlowerOrder& flower);
};

