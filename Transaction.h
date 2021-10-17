#ifndef _TRANSACTION_H_
#define _TRANSACTION_H_

#include "Stock.h"
#include "JSONParser.h"
#include "Crawler.h"
#include <ctime>

class Transaction {

	int ID;
	string stockSymbol;
	double amount, buyingCost, currentCost = 0;

public:

	Transaction(int i, string sym, double a, double buy) : ID(i), stockSymbol(sym), amount(a), buyingCost(buy) {}

	int getID() {
		return ID;
	}
	string getSymbol() {
		return stockSymbol;
	}
	double getAmount() {
		return amount;
	}
	double getBuyCost() {
		return buyingCost;
	}

	double getCurrentCost();

	double absoluteDifference();
	double relativeDifference();

	void sell(double amount);
	void buy(double amount, double currCost);

};

#endif
