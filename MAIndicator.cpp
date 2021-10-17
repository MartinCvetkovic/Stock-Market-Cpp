#include "MAIndicator.h"

void MAIndicator::calculateIndicator(Stock stock) {
	if (interval > stock.candles.size()) throw ERRInvalidValue();
	int n = interval;
	reverse(stock.candles.begin(), stock.candles.end());
	for (int i = 0; i < stock.candles.size(); i++) {
		double sum = 0;
		if (i + n > stock.candles.size()) n--;
		for (int j = i; j < i + n; j++) {
			sum += stock.candles[j].getClose();
		}
		sum /= n;
		result.push_back(sum);
	}
	reverse(result.begin(), result.end());
}
