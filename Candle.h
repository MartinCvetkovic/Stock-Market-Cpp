#ifndef _CANDLE_H_
#define _CANDLE_H_

#include <iostream>
#include <iomanip>

using namespace std;

class Candle {

	double open, close, high, low;
	long timestamp;

public:

	Candle(long t, double o, double c, double h, double l) : open(o), close(c), high(h), low(l), timestamp(t) {}

	double getOpen() {
		return open;
	}
	double getClose() {
		return close;
	}
	double getHigh() {
		return high;
	}
	double getLow() {
		return low;
	}
	long getTimestamp() {
		return timestamp;
	}

	friend std::ostream& operator<<(std::ostream& os, Candle candle);

};

#endif