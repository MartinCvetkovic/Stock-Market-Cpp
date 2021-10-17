#include "Transaction.h"

double Transaction::getCurrentCost(){
	time_t timer = time(NULL);
	Crawler crawler;
	Parser* parser = new JSONParser();
	crawler.setCrawler(stockSymbol, timer - 1, timer);
	crawler.collectData();
	currentCost = parser->parseCurrentPrice();
	delete parser;
	return currentCost;
}

double Transaction::absoluteDifference(){
	return currentCost - buyingCost;
}

double Transaction::relativeDifference(){
	return 100. * (currentCost - buyingCost) / buyingCost;
}

void Transaction::sell(double amount){
	if (this->getAmount() < amount || amount <= 0) throw ERRInvalidValue();
	this->amount -= amount;
}

void Transaction::buy(double amount, double currCost){
	if (amount <= 0) throw ERRInvalidValue();
	this->amount += amount;
	this->buyingCost = currCost;
}
