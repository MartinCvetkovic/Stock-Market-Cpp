#include "IndicatorPrinter.h"

IndicatorPrinter* IndicatorPrinter::instance = nullptr;

void IndicatorPrinter::input(){
    cout << "Do you wish to calculate Moving Average?(y/n)" << endl;
    string confirmation;
    cin >> confirmation;
    if (confirmation == "Y" || confirmation == "y")
        ma = true;
    else
        ma = false;
    cout << "Do you wish to calculate Estimated Moving Average?(y/n)" << endl;
    cin >> confirmation;
    if (confirmation == "Y" || confirmation == "y")
        ema = true;
    else
        ema = false;
}

void IndicatorPrinter::output(Stock stock){
    if (!(ma || ema)) return;
    Indicator* mai = nullptr;
    Indicator* emai = nullptr;
    if (ma) {
        mai = new MAIndicator();
        mai->calculateIndicator(stock);
    }
    if (ema) {
        emai = new EMAIndicator();
        emai->calculateIndicator(stock);
    }
    cout << setw(20) << left << "Timestamps";
    if (ma) cout << setw(20) << left << "MA";
    if (ema) cout << setw(20) << left << "EMA";
    cout << endl;
    for (int i = 0; i < stock.candles.size(); i++) {
        cout << setw(20) << stock.candles[i].getTimestamp();
        if (ma) cout << setw(20) << fixed << setprecision(5) << mai->getResult()[i];
        if (ema) cout << setw(20) << fixed << setprecision(5) << emai->getResult()[i];
        cout << endl;
    }

    if (ma) delete mai;
    if (ema) delete emai;
}