#include "Indicator.h"

int Indicator::interval = 0;

void Indicator::input(){
	cout << "Input number of candles that are taken for the interval: ";
	int n;
	cin >> n;
	if (n < 2) throw  ERRInvalidValue();
	interval = n;
}
