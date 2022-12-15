#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <iomanip>
using namespace std;

class User;
class Order;
class Check;
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
		FlowerAdmin(string name, int count, float price, float sale, int day, int month, int year);
		friend ofstream& operator<<(ofstream& out, const FlowerAdmin& flower);
		friend ifstream& operator>>(ifstream& in, FlowerAdmin& flower);
		friend ostream& operator<<(ostream& ostream, const FlowerAdmin& flower);
		string returnName();
		friend void updateFileFlowers(map <string, FlowerAdmin>& flowers);
		friend void viewFlowers(map <string, FlowerAdmin>& flowers);
		int returnCount();
		void request(int count, int day, int month, int year);
		void updateExpensesFile(int count, float price);
		friend string Editflower(map <string, FlowerAdmin>& flowers, map <string, FlowerAdmin>::iterator flowerIt);
		friend void topUpShoppingCart(map <string, FlowerAdmin>& flowers, User& user);
};

class FlowerOrder : protected Flower
{
		bool flag;
		int count;
		float price, sale;
public:
		FlowerOrder();
		FlowerOrder(string name, bool flag, int count, float price, float sale);
		friend ofstream& operator<<(ofstream& out, const FlowerOrder& flower);
		friend ifstream& operator>>(ifstream& in, FlowerOrder& flower);
		string returnName();
		void setFlag(bool fl);
		int returnCount();
		friend void workCart(Order& cart, int ID);
		friend void myOrders(User& user);
		friend void checkOut(Check& check);
};

