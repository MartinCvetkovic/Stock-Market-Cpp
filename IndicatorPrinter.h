#ifndef _INDICATORPRINTER_H_
#define _INDICATORPRINTER_H_

#include "MAIndicator.h"
#include "EMAIndicator.h"

class IndicatorPrinter {

	bool ma = false, ema = false;

	static IndicatorPrinter* instance;

	IndicatorPrinter() {}

public:

	static IndicatorPrinter& getInstance() {
		if (instance == nullptr) {
			instance = new IndicatorPrinter();
		}
		return *instance;
	}

	static void deleteInstance() {
		delete IndicatorPrinter::instance;
		instance = nullptr;
	}

	void input();

	void output(Stock stock);

};

#endif
