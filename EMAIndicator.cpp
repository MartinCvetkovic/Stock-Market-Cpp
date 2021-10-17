#include "EMAIndicator.h"

double EMA(vector<Candle> candles, int n) {
	double sum = 0;
	if(n == 1) return candles[n - 1].getClose();
	sum += candles[n - 1].getClose() * 2. / (n + 1.) + EMA(candles, n - 1) * (1. - 2. / (n + 1.));
	return sum;
}

void EMAIndicator::calculateIndicator(Stock stock){
	if (interval > stock.candles.size()) throw ERRInvalidValue();
	int n = interval;
	double sum;
	vector<Candle> candles;
	reverse(stock.candles.begin(), stock.candles.end());
	for (int i = 0; i < stock.candles.size(); i++) {
		if (i + n > stock.candles.size()) n--;
		for (int j = i; j < i + n; j++) {
			candles.push_back(stock.candles[j]);
		}
		sum = EMA(candles, n);
		result.push_back(sum);
		candles.clear();
	}
	reverse(result.begin(), result.end());
}
