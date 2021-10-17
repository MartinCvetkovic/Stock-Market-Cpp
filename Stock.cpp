#include "Stock.h"

ostream& operator<<(ostream& os, Stock stock){
	os << endl << setw(20) << left << "Timestamp" << setw(20) << left << "Open" << setw(20) << left << "Close"
		<< setw(20) << left << "High" << setw(20) << left << "Low" << endl;
	
	for_each(stock.candles.begin(), stock.candles.end(), [&os](Candle candle) { os << candle << endl; });
	return os;
}
