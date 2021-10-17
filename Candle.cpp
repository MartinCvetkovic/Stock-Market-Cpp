#include "Candle.h"

ostream& operator<<(ostream& os, Candle candle) {
	if (candle.open < candle.close) os << "\033[0;32m";
	else os << "\033[0;31m";
	os << setw(20) << candle.timestamp << setw(20) << fixed << setprecision(5) << candle.open <<
		setw(20) << candle.close << setw(20) << candle.high << setw(20) << candle.low;
	os << "\033[0m";
	return os;
}
