#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <map>
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
		int deliveryDay, deliveryMonth, deliveryYear, count;
		float price, sale;
public:
		FlowerAdmin();
		friend ofstream& operator<<(ofstream& out, const FlowerAdmin& flower);
		friend ifstream& operator>>(ifstream& in, FlowerAdmin& flower);
		string returnName();
		friend void updateFileFlowers(map <string, FlowerAdmin>& flowers);
};

class FlowerOrder : protected Flower
{
		bool flag;
		int count;
		float price, sale;
public:
		FlowerOrder();
		friend ofstream& operator<<(ofstream& out, const FlowerOrder& flower);
		friend ifstream& operator>>(ifstream& in, FlowerOrder& flower);
};

