#ifndef _STOCK_H_
#define _STOCK_H_

#include <iostream>
#include <vector>
#include "Candle.h"
#include <algorithm>

using namespace std;

class Stock {

	string name;
	long startPeriod, endPeriod;
public:vector<Candle> candles;

public:

	Stock(string n, long sp, long ep) : name(n), startPeriod(sp), endPeriod(ep) {}


	friend ostream& operator<<(ostream& os, Stock stock);

};

#endif