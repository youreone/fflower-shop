#pragma once
#include <vector>
#include "Flower.h"
using namespace std;

class Order
{
		vector <FlowerOrder> flowers;
public:
		void writeToFile();
};

